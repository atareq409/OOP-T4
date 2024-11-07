#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "CPU.cpp"
#include "STORAGE.cpp"
#include "ALU.cpp"
using namespace std;

// Machine class to handle user input and execute instructions
class Machine {
private:
    Memory memory;
    Register reg;
    CPU cpu;

public:
    Machine() : cpu(memory, reg) {}

    void menu() {
        int address = 0;
        cout << "Welcome to FCAI-CU CPU Simulator" << endl;
        cout << "Enter instructions in hexadecimal (e.g., 0x1234) or type q to execute:\n";

        while (true) {
            string hexInput;
            cout << "Instruction for address " << hex << address << ": ";
            cin >> hexInput;

            if (hexInput == "q") {
                break;
            }

            // Corrected call to hexToInt via the ALU instance of CPU
            int instruction = cpu.getALU().hexToInt(hexInput);
            memory.setCell(address++, instruction);
        }

        cpu.run();
        displayMemoryState();
    }

    void displayMemoryState() {
        cout << "Memory State:\n";
        for (int i = 0; i < 256; ++i) {
            cout << "Memory[" << i << "]: " << memory.getCell(i) << endl;
        }
    }
};

int main() {
    Machine m;
    m.menu();
    return 0;
}
