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
            6,
            3, // WCET fictício
            parser.getInstructions(),
            parser.getData()
        );

        scheduler.addPCB(pcb);
    }
    srand(time(NULL));
    cout << "PCBs carregados. Total de processos: " << scheduler.getPCBCount() << endl;

    PCB* running = nullptr;

    while (scheduler.getPCBCount() > 0) {
        cout << "[t=" << tempoAtual << "] ";

        scheduler.tick(tempoAtual);
        tempoAtual++;

        if (!running) {
            running = scheduler.getNextPCB();
        }

        if (!running) {
            cout << "Nenhum processo em execução." << endl;
            usleep(100000);
            continue;
        }

        cout << "-> Executando PID " << running->pid << endl;

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
                running = nullptr; // foi bloqueado, próximo ciclo pega outro
            } else if (running->remainingTime <= 0) {
                // Reage para o próximo período
                running->arrivalTime += running->period;
                running->deadline    = running->arrivalTime + running->period;
                running->remainingTime = running->wcet;
                running->interpreter.setACC(0);
                running->interpreter.setPC(0);
                running->pc_pcb = 0;
                running->acc_pcb = 0;
                running->state    = READY;
                scheduler.addPCB(running);
                running = nullptr; // voltou para fila
            } else {
                running->state = READY;
                scheduler.addPCB(running);
                running = nullptr; // voltou para fila
            }
        } else {
            // Processo terminou de fato
            scheduler.removePCB(running);
            cout << "Processo " << running->pid << " finalizado." << endl;
            delete running;
            running = nullptr;
        }

        usleep(100000);
    }

    cout << "Todos os processos terminaram." << endl;
    return 0;
}
