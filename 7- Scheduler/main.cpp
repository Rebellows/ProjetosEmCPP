#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "scheduler.cpp"
#include <unistd.h>
#include <vector>
#include <iostream>


int main() {
    srand(time(NULL));  // para os SYSCALLs com bloqueio aleatório
    Scheduler scheduler;
    vector<PCB*> allProcesses;
    // 1. Parse dos programas (você pode ajustar para múltiplos arquivos)
    vector<string> arquivos = {"prog1.txt"}; // Exemplo

    int tempoAtual = 0;
    int proximoPID = 1;
    int aux = 5; 
    int wcet = 3; // Exemplo de WCET
    // Simula criação de processos
    /*
    for (const string& nomeArquivo : arquivos) {
        Parser parser;
        parser.parse(nomeArquivo);

        PCB* pcb = new PCB(
            proximoPID++,
            tempoAtual,
            aux,
            wcet, 
            parser.getInstructions(),
            parser.getData()
        );
        allProcesses.push_back(pcb);
        tempoAtual += 2;  
        aux += 3; 
        wcet+=1;
        scheduler.addPCB(pcb);
    }

*/
    Parser parser;
    parser.parse(arquivos[0]);
    PCB* pcb = new PCB(
    proximoPID++,
    tempoAtual,
    12,
    6, 
    parser.getInstructions(),
    parser.getData()
    );
    allProcesses.push_back(pcb);
    scheduler.addPCB(pcb);
    bool flag_sys = false;
    int currentTime = 0;
    while (true) {
        currentTime++;
        cout << "Tempo atual: " << currentTime << endl;
        
        if(flag_sys){
            scheduler.tick(currentTime, flag_sys);
            flag_sys = false;

        }else{
        for (PCB* pcb : allProcesses) {
            cout<<"oi"<<endl;
            if (pcb->arrivalTime == currentTime && pcb->state == NEW) {
                scheduler.addPCB(pcb);
            }
            cout<<"oi2"<<endl;
        }

        PCB* running = scheduler.getNextPCB();
        if (running) {
            cout << "Executando PID " << running->pid << endl;
            cout << "Instruções: " << running->instructions.size() << endl;
            cout << "Dados: " << running->data.size() << endl;
            cout << "Estado: " << running->state << endl;
            cout << "Tempo restante: " << running->remainingTime << endl;
            cout << "Deadline: " << running->deadline << endl;
            cout << "Tempo de chegada: " << running->arrivalTime << endl;
            cout << "PC: " << running->interpreter.getPC() << endl;
            cout << "ACC: " << running->interpreter.getACC() << endl;
            cout << "Estado do processo: " << running->to_string() << endl;
   

            // Restaura contexto do processo antes de executar
            running->interpreter.setPC(running->pc_pcb);
            running->interpreter.setACC(running->acc_pcb);
        
            bool keepRunning = running->interpreter.step();  // executa uma instrução
        
            // Salva contexto após execução
            running->pc_pcb = running->interpreter.getPC();
            running->acc_pcb = running->interpreter.getACC();
        
            if (!keepRunning) {
                cout << "[Finalizado] PID " << running->pid << " completou o programa." << endl;
                scheduler.removePCB(running);
            } else if (running->interpreter.getSyscallCode() == 2) {
                scheduler.blockPCB(running, 2);

            }else if(running->interpreter.getSyscallCode() == 0){
                cout<< "SYSCALL 0" << endl;
                flag_sys = true;
               
            }
        }
        
        if(!flag_sys){
        cout<<"DEBUG " <<running->remainingTime   <<endl;
        // 5. Avança um tick
        scheduler.tick(currentTime, flag_sys);
        cout<<"DEBUG2 " <<running->remainingTime   <<endl;
        }
        }   
        if (scheduler.getPCBCount() == 0) break;
    }

    cout << "Simulação EDF finalizada no tempo t=" << currentTime << endl;
    return 0;
}
