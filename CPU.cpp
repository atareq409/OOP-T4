#pragma once

#include <iostream>
#include <iomanip>
#include "STORAGE.cpp"
#include "ALU.cpp"

//CPU class to handle CPU operations
class CPU {
public:
    int programCounter = 0;
    int instructionRegister = 0;
    Memory& memory;
    Register& reg;
    ALU alu;  // ALU object

    CPU(Memory& mem, Register& r) : memory(mem), reg(r) {}

    // Getter for ALU
    ALU& getALU() {
        return alu;
    }

    void run() {
        cout << "Running CPU...\n";
        while (true) {
            int instruction = fetch();
            if (decodeAndExecute(instruction)) break;
        }
    }

    int fetch() {
        int instruction = memory.getCell(programCounter);
        instructionRegister = instruction;
        cout << "Fetched instruction: " << hex << setw(4) << setfill('0') << instruction
             << " from address: " << programCounter << endl;
        programCounter++;
        return instruction;
    }

    bool decodeAndExecute(int instruction) {
        int opcode = (instruction & 0xF000) >> 12;
        int reg1 = (instruction & 0x0F00) >> 8;
        int reg2 = (instruction & 0x00F0) >> 4;
        int reg3 = instruction & 0x000F;

        switch (opcode) {
            case 0x1:
                loadRegisterFromMemory(reg1, reg3);
                break;
            case 0x2:
                loadImmediate(reg1, reg3);
                break;
            case 0x3: // STORE: Memory[address] <- R[reg1]
                store(reg1, reg3);
                break;
            case 0x4: // MOVE: R[reg1] <- R[reg3]
                move(reg1, reg3);
                break;
            case 0x5: // ADD Two's Complement: R[reg1] <- R[reg2] + R[reg3] (Two's complement)
                alu.AddTwoComplement(reg1, reg2, reg3, reg.reg);
                break;
            case 0x6: // ADD Floating Point: R[reg1] <- R[reg2] + R[reg3] (Floating point)
                alu.AddFloatingPoint(reg1, reg2, reg3, reg.reg);
                break;
            case 0xB: // JUMP
                if (jump(reg1, reg3)) {
                    return false;
                }
                break;
            case 0xC: // HALT
                halt();
                break;
            default:
                cout << "Invalid instruction: " << hex << instruction << endl;
                return true;
        }
        displayState();
        return false;
    }


    void loadRegisterFromMemory(int regIndex, int memAddress) {
        reg.setCell(regIndex, memory.getCell(memAddress));
        cout << "LOAD: R" << regIndex << " <- Memory[" << memAddress << "]" << endl;
    }

    void loadImmediate(int regIndex, int value) {
        reg.setCell(regIndex, value);
        cout << "LOAD: R" << regIndex << " <- Immediate " << value << endl;
    }


    void store(int regIdx, int address) {
        memory.setCell(address, reg.getCell(regIdx));
        cout << "Stored value " << reg.getCell(regIdx) << " from R" << regIdx << " into Memory[" << address << "]\n";
    }

    void move(int regIdx1, int regIdx2) {
        reg.setCell(regIdx2, reg.getCell(regIdx1));
        cout << "Moved value from R" << regIdx1 << " to R" << regIdx2 << endl;
    }

    bool jump(int regIdx, int address) {
        if (reg.getCell(regIdx) == 0) {
            programCounter = address;
            cout << "Jumped to address " << address << endl;
            return true;
        }
        return false;
    }

    void halt() {
        cout << "Program halted.\n";
        exit(0);
    }

    void displayState() {
        cout << "\nCPU State:\n";
        cout << "Program Counter: " << programCounter << endl;
        cout << "Instruction Register: " << hex << setw(4) << setfill('0') << instructionRegister << endl;
        cout << "Registers: ";
        for (int i = 0; i < 16; ++i) {
            cout << "R" << i << ": " << reg.getCell(i) << " ";
        }
        cout << "\n" << endl;
    }
};
