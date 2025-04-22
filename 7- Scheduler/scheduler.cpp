#include "pcb.cpp"
#include <algorithm>

class Scheduler {
public:
    Scheduler() : runningPCB(nullptr) {
        // Inicializa o scheduler
        
    }


    void addPCB(PCB* pcb) {
        pcb->state = READY;
        pcbs_ready.push_back(pcb);
        sortReadyQueue();
        checkPreemption();
    }

    PCB* getNextPCB() {
 
        if (pcbs_ready.empty()&& runningPCB == nullptr) {
            cout << "No process ready to run." << endl;
            return nullptr;

        }
        if(runningPCB!= nullptr)pcbs_ready.push_back(runningPCB);
        
        sortReadyQueue();
        runningPCB = pcbs_ready.front();
        pcbs_ready.erase(pcbs_ready.begin());
        if (runningPCB->state != BLOCKED) runningPCB->state = RUNNING;
        // cout << "Running " << runningPCB->to_string() << endl;
        return runningPCB;
    }

    void removePCB(PCB* pcb, int currentTime) {
        if (runningPCB == pcb) runningPCB = nullptr;
        pcb->state = NEW;
        pcb->remainingTime = pcb->wcet;
        pcb->arrivalTime =  currentTime + pcb->period;
        pcb->deadline = pcb->arrivalTime + pcb->period;
        pcb->interpreter.setPC(0);
        pcb->interpreter.setACC(0);
        pcb->pc_pcb = pcb->acc_pcb = 0;
        cout << "Terminated " << endl << pcb->to_string() << endl;
    }

    void blockPCB(PCB* pcb, int syscallCode) {
       
        
        pcb->state = BLOCKED;
        
        int blockDuration = 1 + rand() % 3;  // valor de 1 a 3
        pcb->blockedRemainingTime = blockDuration;
        
        cout << "Process " << pcb->pid << " blocked, CPU now idle." << endl;
        cout << "Process " << pcb->pid << " blocked for " << blockDuration << " ticks." << endl;
        
        
    }
    

    void tick(int currentTime, bool flag_sys, PCB* pcb) {
        
        // cout<< pcbs_ready.size() << " ready processes, " << endl;
         
        // 1) Atualiza bloqueados
        cout<<pcb->to_string()<<endl;
        if(pcb != nullptr && pcb->state == BLOCKED) {
            if (--pcb->blockedRemainingTime < 0) {
                cout<< "[UNLOCKED] [PID " << pcb->pid << "] on T = " << currentTime << endl;
                pcb->state = READY;
                pcbs_ready.push_back(pcb);
                
            }
        }
        
        
        // 2) Tratar deadlines perdidos
        for (PCB* p : pcbs_ready) {
            if (p->deadline < currentTime) {
                cout << "[LOST DEADLINE] [PID " << p->pid << "] on T = " << currentTime << endl;
                p->arrivalTime += p->period;
                p->deadline     = p->arrivalTime + p->period;
                p->remainingTime = p->wcet;
                p->interpreter.setACC(0);
                p->interpreter.setPC(0);
                p->pc_pcb = p->acc_pcb = 0;
            }
        }
       
        // 3) Preempção se necessário
        sortReadyQueue();
        checkPreemption();

        // 4) Executa “um tick” no runningPCB
        if (runningPCB) {
            if (--runningPCB->remainingTime <= 0) {
                // Termina aqui
                cout << "[COMPLETED] [PID " << runningPCB->pid << "] on T = " << currentTime << endl;
                removePCB(runningPCB, currentTime);
            }
        }
        cout<<runningPCB->to_string()<<endl;
        if (flag_sys) {
            cout << "Syscall 0 detected," << endl;
            cout << "[COMPLETED] [PID " << runningPCB->pid << "] on T = " << currentTime << endl;
            removePCB(runningPCB, currentTime);
            runningPCB = nullptr;
        }
    }



private:
    vector<PCB*> pcbs_ready;
    PCB* runningPCB;

    void sortReadyQueue() {
        sort(pcbs_ready.begin(), pcbs_ready.end(),
             [](PCB* a, PCB* b){
                 if (a->deadline != b->deadline)
                     return a->deadline < b->deadline;
                 return a->arrivalTime < b->arrivalTime;  
             });
    }

    void checkPreemption() {
        if (!runningPCB || pcbs_ready.empty()) return;
        PCB* next = pcbs_ready.front();
        if (next->deadline < runningPCB->deadline) {
            cout << "[PREEMPTION] " << runningPCB->pid
                 << " for [PID " << next->pid << "]" << endl;
            runningPCB->state = READY;
            pcbs_ready.push_back(runningPCB);
            sortReadyQueue();
            runningPCB = pcbs_ready.front();
            pcbs_ready.erase(pcbs_ready.begin());
            runningPCB->state = RUNNING;
            cout << "Running " << endl << runningPCB->to_string() << endl;
        }
    }
};
