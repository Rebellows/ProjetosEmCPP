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
    vector<string> arquivos = {"prog1.txt","prog2.txt"}; // Exemplo

    int entry_time = 0;
    int proximoPID = 1;

    Parser parser;

    parser.parse(arquivos[0]);
    PCB* pcb = new PCB(
        proximoPID++,
        entry_time,
        18,
        9, 
        parser.getInstructions(),
        parser.getData()
    );
    allProcesses.push_back(pcb);
    scheduler.addPCB(pcb);

    Parser parser2;
    parser2.parse(arquivos[1]);
    PCB* pcb2 = new PCB(
        proximoPID++,
        entry_time,
        96,
        48, 
        parser2.getInstructions(),
        parser2.getData()
    );
    allProcesses.push_back(pcb2);
    scheduler.addPCB(pcb2);
    
    
    bool flag_sys = false;
    int currentTime = 0;
    int init = 1;
    PCB* running = new PCB(0, 0, 0, 0, {}, {});
    while (true && currentTime < 1000) {
        currentTime++;
        cout << "[TEMPO ATUAL " << currentTime << "]" << endl;
            
            init = 0;
            if(flag_sys){
                scheduler.tick(currentTime, flag_sys, running);
                flag_sys = false;

            } else {

                for (PCB* pcb : allProcesses) {
                    if (pcb->arrivalTime == currentTime && pcb->state == NEW) {
                        scheduler.addPCB(pcb);
                    }
                }

                running = scheduler.getNextPCB();
                if (running && !(running->state == BLOCKED)) {
                    // cout << "PROCESS STATE: " << endl << running->to_string() << endl;


                    // Restaura contexto do processo antes de executar
                    running->interpreter.setPC(running->pc_pcb);
                    running->interpreter.setACC(running->acc_pcb);
                
                    bool keepRunning = running->interpreter.step();  // executa uma instrução
                
                    // Salva contexto após execução
                    running->pc_pcb = running->interpreter.getPC();
                    running->acc_pcb = running->interpreter.getACC();
                
                    if (!keepRunning) {
                        cout << "[FINISHED] PID " << "[PID " << running->pid << "]" << " completed the program." << endl;
                        scheduler.removePCB(running, currentTime);
                    } else if (running->interpreter.getSyscallCode() == 2) {
                        scheduler.blockPCB(running, 2);

                    }else if(running->interpreter.getSyscallCode() == 0){
                        cout<< "SYSCALL 0" << endl;
                        flag_sys = true;
                    
                    }
                }
                
                if(!flag_sys){
                    // 5. Avança um tick
                    scheduler.tick(currentTime, flag_sys, running);
            }
        }   
    }

    cout << "Simulação EDF finalizada no tempo t = " << currentTime << endl;
    return 0;
}
