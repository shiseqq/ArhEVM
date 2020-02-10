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
    if ((command == 0x10 || command == 0x11 || command == 0x20 || command == 0x21 || command > 0x29 && command < 0x34 || command > 0x39 && command < 0x44 || command > 0x50 && command < 0x77) && (operand == 0x10 || operand == 0x11 || operand == 0x20 || operand == 0x21 || operand > 0x29 && operand < 0x34 || operand > 0x39 && operand < 0x44 || operand > 0x50 && operand < 0x77)) {
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
    if (!(value & (1 << 15)) && (c == 0x10 || c == 0x11 || c == 0x20 || c == 0x21 || c > 0x29 && c < 0x34 || c > 0x39 && c < 0x44 || c > 0x50 && c < 0x77) && (o == 0x10 || o == 0x11 || o == 0x20 || o == 0x21 || o > 0x29 && o < 0x34 || o > 0x39 && o < 0x44 || o > 0x50 && o < 0x77)) {
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