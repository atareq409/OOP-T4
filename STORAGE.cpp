#pragma once
#include <vector>
#include "ALU.cpp"

using namespace std;
// Memory class to handle memory operations
class Memory{
public:
    vector<int> memory;

    Memory() {
        memory.resize(256, 0); // Initialize all 256 memory cells to 0
    }

    int size() const {
        return memory.size();
    }

    int getCell(int address) {
        if (address >= 0 && address < size()) {
            return memory[address];
        } else {
            cerr << "Memory access out of bounds: " << address << endl;
            return 0;
        }
    }

    void setCell(int address, int value) {
        if (address >= 0 && address < size()) {
            memory[address] = value;
        } else {
            cerr << "Memory access out of bounds: " << address << endl;
        }
    }
};

// Register class to handle register operations
class Register{
public:
    int reg[16];

    Register() {
        reset();
    }

    void reset() {
        for (int i = 0; i < 16; ++i) {
            reg[i] = 0;
        }
    }

    int getCell(int index) {
        if (index >= 0 && index < 16) {
            return reg[index];
        } else {
            cerr << "Register access out of bounds: " << index << endl;
            return 0;
        }
    }

    void setCell(int index, int value) {
        if (index >= 0 && index < 16) {
            reg[index] = value;
        } else {
            cerr << "Register access out of bounds: " << index << endl;
        }
    }
};
