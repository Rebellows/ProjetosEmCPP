#include "pcb.cpp"
#include <algorithm>

class Scheduler {
public:
    void addPCB(PCB* pcb) {
        pcb->state = READY;
        pcbs_ready.push_back(pcb);
    }

    PCB* getNextPCB() {
        if (pcbs_ready.empty()) return nullptr;

        // Ordena por deadline (menor primeiro)
        sort(pcbs_ready.begin(), pcbs_ready.end(), [](PCB* a, PCB* b) {
            return a->deadline < b->deadline;
        });

        PCB* selected = pcbs_ready.front();
        selected->state = RUNNING;
        pcbs_ready.erase(pcbs_ready.begin());
        cout << "Running " << selected->to_string() << endl;
        return selected;
    }

    void removePCB(PCB* pcb) {
        pcb->state = TERMINATED;
        pcbs_ready.erase(remove(pcbs_ready.begin(), pcbs_ready.end(), pcb), pcbs_ready.end());
        cout << "Terminated " << pcb->to_string() << endl;
    }

    void blockPCB(PCB* pcb, int syscallCode) {
        if (syscallCode == 2) { // ex: syscall 2 = input
            pcb->state = WAITING;
            pcb->blockedRemainingTime = 2; // tempo fictício para desbloquear
            pcbs_waiting.push_back(pcb);
        }
    }

    void tick() {
        // Atualiza processos bloqueados
        for (int i = 0; i < pcbs_waiting.size(); i++) {
            PCB* pcb = pcbs_waiting[i];
            pcb->blockedRemainingTime--;

            if (pcb->blockedRemainingTime <= 0) {
                pcb->state = READY;
                pcbs_ready.push_back(pcb);
                pcbs_waiting.erase(pcbs_waiting.begin() + i);
                i--;
            }
        }

        // Atualiza deadlines
        for (PCB* pcb : pcbs_ready) {
            pcb->deadline--;
        }
    }

    int getPCBCount() {
        return pcbs_ready.size() + pcbs_waiting.size();
    }

private:
    vector<PCB*> pcbs_ready;
    vector<PCB*> pcbs_waiting;
};