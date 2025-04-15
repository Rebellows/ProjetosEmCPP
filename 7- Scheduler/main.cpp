#include "pcb.cpp"
#include <unistd.h>

int main()
{
    cout << "Starting Program..." << endl;
    while (true)
    {
        Parser parser;
        parser.parse("prog2.txt");
        cout << "Program Parsed" << endl;
        for (auto c : parser.getInstructions())
        {
            cout << c.to_string() << endl;
        }
        for(auto  c : parser.getData()){
            printf("%s %d\n", c.first.c_str(), c.second);
        }
        // Interpreter interpreter(parser.getInstructions(), parser.getData());
        // while (interpreter.step())
        // {
        //     cout << "pc: " << interpreter.getPC() << endl;
        //     cout << "acc: " <<interpreter.getACC() << endl;
        //     usleep(20000);
        // }
        
        return 0;
    }
}