#include "scheduler.cpp"
#include <unistd.h>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    cout << "Starting Scheduler (EDF)..." << endl;

    Scheduler scheduler;

    // Carrega múltiplos programas (poderia ser de arquivos diferentes)
    vector<string> arquivos = {"prog1.txt", "prog2.txt"}; // Exemplo

    int tempoAtual = 0;
    int proximoPID = 1;

    // Simula criação de processos
    for (const string& nomeArquivo : arquivos) {
        Parser parser;
        parser.parse(nomeArquivo);

        PCB* pcb = new PCB(
            proximoPID++,
            tempoAtual,
            10 + rand() % 10, // período aleatório
            5, // WCET fictício
            parser.getInstructions(),
            parser.getData()
        );
        
        scheduler.addPCB(pcb);
    }

    cout << "PCBs carregados." << " Total de processos: " << scheduler.getPCBCount() << endl;

    // Loop principal do escalonador
    while (scheduler.getPCBCount() > 0) {
        scheduler.tick();
        tempoAtual++;

        PCB* running = scheduler.getNextPCB();
        if (!running) {
            cout << "Nenhum processo em execução." << endl;
            usleep(100000);
            continue;
        }

        // Restaura contexto
        running->interpreter.setACC(running->acc_pcb);
        running->interpreter.setPC(running->pc_pcb);

        // Executa uma instrução
        if (running->interpreter.step()) {
            int syscallCode = running->interpreter.getSyscallCode();

            // Salva contexto
            running->acc_pcb = running->interpreter.getACC();
            running->pc_pcb = running->interpreter.getPC();

            if (syscallCode == 2) {
                scheduler.blockPCB(running, syscallCode);
            } else {
                running->state = READY;
                scheduler.addPCB(running);
            }
        } else {
            scheduler.removePCB(running);
            cout << "Processo " << running->pid << " finalizado." << endl;
            delete running;
        }

        usleep(100000); // Espera 100ms
    }

    cout << "Todos os processos terminaram." << endl;
    return 0;
}