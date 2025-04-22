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

    string centerText(const std::string& text, size_t width) {
        if (text.length() >= width)
            return text;
        size_t leftPadding = (width - text.length()) / 2;
        size_t rightPadding = width - text.length() - leftPadding;
        return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
    }

    string to_string() {
        stringstream ss;
        string stateStr = (state == NEW ? "NEW" : state == READY ? "READY" : state == BLOCKED ? "BLOCKED" : state == RUNNING ? "RUNNING" : "TERMINATED");
        ss << "| PID |   STATE   | ARRIVAL TIME | PERIOD | DEADLINE | WCET | REMAINING TIME |" << endl;
        ss << "| " << centerText(std::to_string(pid), 3) << " |" 
        << " " << centerText(stateStr, 9) << " |"
        << " " << centerText(std::to_string(arrivalTime), 13) << "|"
        << " " << centerText(std::to_string(period), 7) << "|"
        << " " << centerText(std::to_string(deadline), 9) << "|"
        << " " << centerText(std::to_string(wcet), 5) << "|"
        << " " << centerText(std::to_string(remainingTime), 15) << "|" << endl;
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