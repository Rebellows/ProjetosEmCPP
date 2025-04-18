#include "parser.cpp"
#include <stdexcept>

using namespace std;

class Interpreter {
private:    
    vector<Instruction> instructions;
    unordered_map<string, int> data;
    unordered_map<string, int> labels;
    int pc = 0, acc = 0;

    void mapLabels() {
        for (int i = 0; i < instructions.size(); i++) {
            if (!instructions[i].label.empty()) {
                labels[instructions[i].label] = i+1;
            }
        }
    }

    int getValue(const string &operand) {
        if (operand[0] == '#') {
            string aux = operand.substr(1);
            return stoi(aux);
        } else if (isdigit(operand[0])) {
            return stoi(operand);
        } else {
            return data[operand];
        }
    }

    void executeSyscall(int syscallNumber) {
        pc++;
        switch (syscallNumber) {
            case 0:
                // cout << "Program finished" << endl;
                // exit(0); // ainda entender se aqui eh exit mesmo
                break;                
            case 1:
                cout << acc << endl;
                break;
            case 2:
                cin >> acc;
                break;
            default:
                cerr << "Invalid syscall number: " << syscallNumber << "\n";
        }
    }

public:
    Interpreter(vector<Instruction> instr, unordered_map<string, int> d) {
        instructions = instr;
        data = d;
        pc = 0;
        mapLabels();
    }

    bool step() {
        // cout << "pc: " << pc << " acc: " << acc << " instr: "<< instructions.size()<< endl;
        if (pc >= instructions.size()) {
            return false;
        }


        const Instruction &instr = instructions[pc];
        const string op = instr.opcode;
        const string operand = instr.operand;

        // printf("%-8s %-10s\t", op.c_str(), operand.c_str());

        if (op == "ADD") {
            acc += getValue(operand);
        } else if (op == "SUB") {
            acc -= getValue(operand);
        } else if (op == "MULT") {
            acc *= getValue(operand);
        } else if (op == "DIV") {
            int divisor = getValue(operand);
            if (divisor == 0) throw runtime_error("Zero division");
            acc /= divisor;
        } else if (op == "LOAD") {
            acc = data[operand];
        } else if (op == "STORE") {
            data[operand] = acc;
        } else if (op == "BRANY") {
            cout << "-------------------label " << operand<< "   ";
            pc = labels.at(operand);
            return true;
        } else if (op == "BRPOS" && acc > 0) {
            cout << "-------------------label " << operand << "   ";
            pc = labels.at(operand);
            return true;
        } else if (op == "BRZERO" && acc == 0) {
            cout << "------------------label " << operand << "   " ;
            pc = labels.at(operand);
            return true;
        } else if (op == "BRNEG" && acc < 0) {
            cout << "-----------------label " << operand << "   ";
            pc = labels.at(operand);
            return true;
        } else if (op == "SYSCALL") {
            executeSyscall(getValue(operand));
            return true;
        } else  if (!op.empty()) {
            cerr << "Invalid instruction: " << op << "   ";
        }
        pc++;
        return true;
    }

    int getSyscallCode() { // para o escalonador fazer o block se for syscall
        if (pc >= instructions.size()) return -1;
    
        const Instruction &instr = instructions[pc];
        if (instr.opcode != "SYSCALL") return -1;
        
        return getValue(instr.operand); 
    }

    // pra salvar contexto
    int getACC() const { return acc; }
    int getPC() const { return pc; }

    void setACC(int value) { acc = value; }
    void setPC(int value) { pc = value; }
};
