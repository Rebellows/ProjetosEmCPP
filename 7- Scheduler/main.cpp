// #include "pcb.cpp"
// #include <unistd.h>

// int main()
// {
//     cout << "Starting Program..." << endl;
//     while (true)
//     {
//         Parser parser;
//         parser.parse("prog2.txt");
//         cout << "Program Parsed" << endl;
//         // for (auto c : parser.getInstructions())
//         // {
//         //     cout << c.to_string() << endl;
//         // }
//         // for(auto  c : parser.getData()){
//         //     printf("%s %d\n", c.first.c_str(), c.second);
//         // }
//         Interpreter interpreter(parser.getInstructions(), parser.getData());
//         while (interpreter.step())
//         {
//             // cout << "pc: " << interpreter.getPC() << " | " << "acc: " << interpreter.getACC() << endl;
//             printf("pc: %3d | acc: %3d\n", interpreter.getPC(), interpreter.getACC());   
//             usleep(20000);
//         }
        
//         return 0;
//     }
// }


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

    // Loop principal do escalonador
    while (scheduler.getPCBCount() > 0) {
        scheduler.tick();
        tempoAtual++;

        PCB* running = scheduler.getNextPCB();
        if (!running) {
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