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
            3,
            5, // WCET fictício
            parser.getInstructions(),
            parser.getData()
        );

        scheduler.addPCB(pcb);
    }

    cout << "PCBs carregados." << " Total de processos: " << scheduler.getPCBCount() << endl;

    // Loop principal do escalonador
    while (scheduler.getPCBCount() > 0) {
        scheduler.tick(tempoAtual);
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
            running->remainingTime--;

            // Salva contexto
            running->acc_pcb = running->interpreter.getACC();
            running->pc_pcb = running->interpreter.getPC();

            if (syscallCode == 1 || syscallCode == 2) {
                scheduler.blockPCB(running, syscallCode);
            } else if (running->remainingTime <= 0) {
                // Reage para o próximo período
                running->arrivalTime += running->period;
                running->deadline = running->arrivalTime + running->period;
                running->remainingTime = running->wcet;
                running->interpreter.setACC(0);
                running->interpreter.setPC(0);
                running->pc_pcb = 0;
                running->acc_pcb = 0;
                running->state = READY;
                scheduler.addPCB(running);
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
