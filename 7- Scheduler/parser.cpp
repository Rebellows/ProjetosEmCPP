#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

using namespace std;

struct Instruction
{
    string label;
    string opcode;
    string operand;
    string to_string()
    {
        stringstream ss;
        ss << label << " " << opcode << " " << operand;
        return ss.str();
    }
};

class Parser
{
private:
    vector<Instruction> instructions;
    unordered_map<string, int> data;
    // unordered_map<string, int> labels;

public:
    void parse(string filename)
    {
        ifstream file(filename);
        string line;
        bool isCode = false, isData = false;

        if (!file.is_open())
        {
            cout << "Unable to open file";
            return;
        }

        while (getline(file, line))
        {
            if (line.find_first_not_of(' \t\n\r') == string::npos)
            {
                continue;
            }

            if (line == ".code")
            {
                isCode = true;
                isData = false;
                continue;
            }
            else if (line == ".endcode")
            {
                isCode = false;
                continue;
            }
            else if (line == ".data")
            {
                isCode = false;
                isData = true;
                continue;
            }
            else if (line == ".enddata")
            {
                isData = false;
                continue;
            }

            if (isCode)
            {
                parseCode(line);
            }
            else if (isData)
            {
                parseData(line);
            }
        }
        file.close();
    }

    string to_upper_casae(string s)
    {
        for (auto &c : s)
        {
            c = toupper(c);
        }
        return s;
    }

    void parseCode(string &line)
    {
        stringstream iss(line);
        // string word;

        Instruction instr;

        if (line.find(':') != string::npos)
        {
            size_t pos = line.find(':');
            instr.label = line.substr(0, pos);
            string rest = line.substr(pos + 1);
            istringstream restStream(rest);
            string op;
            restStream >> op >> instr.operand;
            op = to_upper_casae(op);
            instr.opcode = op;
        }
        else
        {
            string op;
            iss >> op >> instr.operand;
            op = to_upper_casae(op);
            instr.opcode = op;
        }

        instructions.push_back(instr);
    }

    void parseData(string &line)
    {
        stringstream iss(line);
        string name;
        int value;
        iss >> name >> value;
        data[name] = value;
    }

    vector<Instruction> getInstructions() const
    {
        return instructions;
    }

    unordered_map<string, int> getData() const
    {
        return data;
    }
};
