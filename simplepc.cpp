#include "simplepc.h"

int a[100];
int32_t reg;

int sc_memoryInit()
{
    for (int i = 0; i < 100; i++) {
        a[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address < 0 || address >= 100) {
        cout << "Error! Invalid address number\n";
        sc_regSet(M, 1);
        return 1;
    } else {
        a[address] = value;
        return 0;
    }
}

int sc_memoryGet(int address, int& value)
{
    if (address < 0 || address >= 100) {
        cout << "Error! Invalid address number:" << address << endl;
        sc_regSet(M, 1);
        return 1;
    } else {
        value = a[address];
        return 0;
    }
}

int sc_memorySave(string filename)
{
    ofstream out(filename, ios::binary);
    out.write((char*)a, sizeof(a));
    out.close();
    return 0;
}

int sc_memoryLoad(string filename)
{
    ifstream inp(filename, ios::binary);
    if (!inp.is_open()) {
        return 1;
    } else {
        inp.read((char*)a, sizeof(a));
        return 0;
    }
}

int sc_regInit()
{
    reg = 0;
    return 0;
}

int sc_regSet(int regist, int value)
{
    if (regist > 4 || regist <= 0) {
        cout << "Error! Invalid register number\n";
        return 1;
    }
    if (value != 1 && value != 0) {
        cout << "Error! Invalid value number\n";
        return 1;
    }
    if (value) {
        reg |= (1 << (regist - 1));
    } else {
        reg &= (~(1 << (regist - 1)));
    }
    return 0;
}

int sc_regGet(int regist, int& value)
{
    if ((regist > 4) || (regist <= 0)) {
        cout << "Error! Invalid register number\n";
        return 1;
    }
    value = ((reg >> (regist - 1)) & 0x1);
    return 0;
}

int sc_commandEncode(int command, int operand, int& value)
{
    if ((command == 10 || command == 11 || command == 20 || command == 21 || command > 29 && command < 34 || command > 39 && command < 44 || command > 50 && command < 77) && (operand == 10 || operand == 11 || operand == 20 || operand == 21 || operand > 29 && operand < 34 || operand > 39 && operand < 44 || operand > 50 && operand < 77)) {
        value = command * 128 + operand;
        return 0;
    }
    else {
        cout << "Error! Invalid command or operand number" << endl;
        return 1;
    }
}

int sc_commandDecode(int value, int& command, int& operand)
{
    int c = value / 128;
    int o = value % 128;
    if (!(value & (1 << 15)) && (c == 10 || c == 11 || c == 20 || c == 21 || c > 29 && c < 34 || c > 39 && c < 44 || c > 50 && c < 77) && (o == 10 || o == 11 || o == 20 || o == 21 || o > 29 && o < 34 || o > 39 && o < 44 || o > 50 && o < 77)) {
        command = c;
        operand = o;
        return 0;
    }
    else {
        cout << "Error! Decoding is not possible" << endl;
        sc_regSet(E, 1);
        return 1;
    }
}