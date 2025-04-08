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
                labels[instructions[i].label] = i;
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

public:
    Interpreter(const vector<Instruction> &instr, const unordered_map<string, int> &d) {
        instructions = instr;
        data = d;
        mapLabels();
    }

    void execute() {
        while (pc < instructions.size()) {
            const Instruction &instr = instructions[pc];
            const string &op = instr.opcode;
            const string &operand = instr.operand;

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
                acc = getValue(operand);
            } else if (op == "STORE") {
                data[operand] = acc;
            } else if (op == "BRANY") {
                pc = labels.at(operand);
                continue;
            } else if (op == "BRPOS" && acc > 0) {
                pc = labels.at(operand);
                continue;
            } else if (op == "BRZERO" && acc == 0) {
                pc = labels.at(operand);
                continue;
            } else if (op == "BRNEG" && acc < 0) {
                pc = labels.at(operand);
                continue;
            } else if (op == "SYSCALL") {
                switch (getValue(operand)) { // precisa implementar o bloqueio de 1 a 3 no syscall para caso 1 e 2
                    case 0:
                        exit(0); // ver se o exit nao vai sair de tudo
                        break;
                
                    case 1:
                        cout << acc << endl;
                        break;

                    case 2:
                        cin >> acc;
                        break;

                    default:
                        break;

                }
            } else if (!op.empty()) {
                cerr << "Invalid instruction: " << op << "\n";
            }
            pc++;
        }
    }
};