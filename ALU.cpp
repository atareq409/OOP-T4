#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
// ALU class with operations and hexToInt method
class ALU {
public:
    void AddTwoComplement(int regR, int regS, int regT, int* registers) {
        int result = registers[regS] + registers[regT];  // Add as two's complement
        registers[regR] = result;
        cout << "Added R" << regS << " and R" << regT << " (Two's complement), result in R" << regR << ": " << result << endl;
    }

    void AddFloatingPoint(int regR, int regS, int regT, int* registers) {
        float result = static_cast<float>(registers[regS]) + static_cast<float>(registers[regT]);  // Add as floating point
        registers[regR] = static_cast<int>(result);
        cout << "Added R" << regS << " and R" << regT << " (Floating point), result in R" << regR << ": " << result << endl;
    }

    int hexToInt(const string &hexStr) {
        int value;
        stringstream ss;
        ss << hex << hexStr;
        ss >> value;
        return value;
    }
};
