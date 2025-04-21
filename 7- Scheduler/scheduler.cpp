#include "pcb.cpp"
#include <algorithm>

class Scheduler {
public:
    Scheduler() : runningPCB(nullptr) {
        
    }


    void addPCB(PCB* pcb) {
        pcb->state = READY;
        pcbs_ready.push_back(pcb);
        sortReadyQueue();
        checkPreemption();
    }

    PCB* getNextPCB() {
        if (pcbs_ready.empty()) return nullptr;
        sortReadyQueue();
        runningPCB = pcbs_ready.front();
        pcbs_ready.erase(pcbs_ready.begin());
        runningPCB->state = RUNNING;
        cout << "Running " << runningPCB->to_string() << endl;
        return runningPCB;
    }

    void removePCB(PCB* pcb) {
        if (runningPCB == pcb) runningPCB = nullptr;
        pcb->state = TERMINATED;
        pcbs_ready.erase(remove(pcbs_ready.begin(), pcbs_ready.end(), pcb),
                         pcbs_ready.end());
        cout << "Terminated " << pcb->to_string() << endl;
    }

    void blockPCB(PCB* pcb, int syscallCode) {
       
        
        pcb->state = WAITING;
        
        int blockDuration = 1 + rand() % 3;  // valor de 1 a 3
        pcb->blockedRemainingTime = blockDuration;
        
        pcbs_waiting.push_back(pcb);
        
        cout << "Process " << pcb->pid << " blocked, CPU now idle." << endl;
        cout << "Process " << pcb->pid << " blocked for " << blockDuration << " ticks." << endl;
      
        
    }
    

    void tick(int currentTime) {
        cout<< pcbs_ready.size() << " processos prontos, "
            << pcbs_waiting.size() << " bloqueados, "
            << (runningPCB ? "1 em execução" : "nenhum em execução") << endl;
            for(PCB* p : pcbs_ready) {
                cout << p->to_string() << endl;
            }
            for(PCB* p : pcbs_waiting) {
                cout << p->to_string() << endl;
            }
        // 1) Atualiza bloqueados
        for (int i = 0; i < pcbs_waiting.size(); ++i) {
            PCB* p = pcbs_waiting[i];
            if (--p->blockedRemainingTime <= 0) {
                p->state = READY;
                pcbs_ready.push_back(p);
                pcbs_waiting.erase(pcbs_waiting.begin() + i--);
            }
        }

        // 2) Tratar deadlines perdidos
        for (PCB* p : pcbs_ready) {
            if (p->deadline < currentTime) {
                cout << "[Deadline Perdido] PID " << p->pid << " no t=" << currentTime << endl;
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
                cout << "[Concluído] PID " << runningPCB->pid << " no t=" << currentTime << endl;
                removePCB(runningPCB);
            }
        }
    }

    int getPCBCount() const {
        return pcbs_ready.size() + pcbs_waiting.size() + (runningPCB ? 1 : 0);
    }

private:
    vector<PCB*> pcbs_ready, pcbs_waiting;
    PCB* runningPCB;

    void sortReadyQueue() {
        sort(pcbs_ready.begin(), pcbs_ready.end(),
             [](PCB* a, PCB* b){
                 if (a->deadline != b->deadline)
                     return a->deadline < b->deadline;
                 return a->arrivalTime < b->arrivalTime;  // desempate
             });
    }

    void checkPreemption() {
        if (!runningPCB || pcbs_ready.empty()) return;
        PCB* next = pcbs_ready.front();
        if (next->deadline < runningPCB->deadline) {
            cout << "[Preempção] " << runningPCB->pid
                 << " por " << next->pid << endl;
            runningPCB->state = READY;
            pcbs_ready.push_back(runningPCB);
            sortReadyQueue();
            runningPCB = pcbs_ready.front();
            pcbs_ready.erase(pcbs_ready.begin());
            runningPCB->state = RUNNING;
            cout << "Running " << runningPCB->to_string() << endl;
        }
    }
};
