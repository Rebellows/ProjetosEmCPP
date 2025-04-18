#include "interpreter.cpp"

enum ProcessState {NEW, READY, WAITING, RUNNING, TERMINATED};

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
    string to_string() {
        stringstream ss;
        ss << "PID: " << pid << endl;
        ss << "Arrival Time: " << arrivalTime << endl;
        ss << "Period: " << period << endl;
        ss << "Deadline: " << deadline << endl;
        ss << "WCET: " << wcet << endl;
        ss << "Remaining Time: " << remainingTime << endl;
        ss << "State: " << (state == NEW ? "NEW" : state == READY ? "READY" : state == WAITING ? "WAITING" : state == RUNNING ? "RUNNING" : "TERMINATED") << endl;
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
        state = READY;
    }
};