#include "interpreter.cpp"

enum ProcessState {NEW, READY, BLOCKED, RUNNING, TERMINATED};

struct PCB {
    int pid;
    int arrivalTime;
    int period, deadline;
    int wcet;
    int remainingTime;
    int blockedRemainingTime = 0;
    ProcessState state = NEW;
    vector<Instruction> instructions;
    unordered_map<string, int> data;
    Interpreter interpreter;

    string getInstructions(){
        stringstream ss;
        for (Instruction instrucition : instructions) {
            ss << "  -" << instrucition.to_string() << endl;
        }
        return ss.str();
    }

    string to_string() {
        stringstream ss;
        ss << "[PID " << pid << "]" << endl;
        ss << " - STATE: " << (state == NEW ? "NEW" : state == READY ? "READY" : state == BLOCKED ? "BLOCKED" : state == RUNNING ? "RUNNING" : "TERMINATED") << endl;
        // ss << " - INTRUÇÕES: " << endl <<  getInstructions() << endl;
        ss << " - ARRIVAL TIME: " << arrivalTime << endl;
        ss << " - PERIOD: " << period << endl;
        ss << " - DEADLINE: " << deadline << endl;
        ss << " - WCET: " << wcet << endl;
        ss << " - REMAINING TIME: " << remainingTime << endl;
        return ss.str();
    }

    int pc_pcb = 0, acc_pcb = 0;

    PCB(int id, int a, int pi, int w, vector<Instruction> i, unordered_map<string, int> d): interpreter(i, d) {
        pid = id;
        arrivalTime = a;
        period = pi;
        deadline = a + pi;
        wcet = w;
        remainingTime = wcet;
        instructions = i;
        data = d;
        state = NEW;
    }
};