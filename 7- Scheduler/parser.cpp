#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Instruction {
    string label;
    string opcode;
    string operand;
};

struct Data {
    string name;
    int value;
};

class Parser {
private:
    vector<Instruction> instructions;
    vector<Data> data;
public:
    void parse(string &filename) {
        ifstream file(filename);
        string line;
        bool isCode = false, isData = false;

        if (!file.is_open()) {
            cout << "Unable to open file";
            return;
        }

        while (getline(file, line)) {
            if (line.find_first_not_of(' \t\n\r') == string::npos) {
                continue;
            }

            if (line == ".code") {
                isCode = true;
                isData = false;
                continue;
            } else if (line == ".endcode") {
                isCode = false;
                continue;
            } else if (line == ".data") {
                isCode = false;
                isData = true;    
                continue;
            } else if (line == ".enddata") {
                isData = false;            
                continue;
            }

            if (isCode) {  
                parseCode(line);
            } else if (isData) {
                parseData(line);
            }
        }
        file.close();
    }

    void parseCode(string &line) {
        istringstream iss(line);
        string word;
        Instruction instr;

        if (line.find(':') != string::npos) {
            size_t pos = line.find(':');
            instr.label = line.substr(0, pos);
            string rest = line.substr(pos + 1);
            istringstream restStream(rest);
            restStream >> instr.opcode >> instr.operand;
        } else {
            iss >> instr.opcode >> instr.operand;
        }

        instructions.push_back(instr);
    }

    void parseData(string &line) {
        istringstream iss(line);
        Data d;
        iss >> d.name >> d.value;
        data.push_back(d);
    }

    vector<Instruction> getInstructions() const {
        return instructions;
    }

    vector<Data> getData() const {
        return data;
    }
};