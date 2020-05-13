#include "simplepc.h"

int a[100];
int32_t reg;
int insc = 0;
int accum = 0;

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
        sc_regSet(M, 1);
        return -1;
    } else {
        a[address] = value;
        return 0;
    }
}

int sc_memoryGet(int address, int& value)
{
    if (address < 0 || address >= 100) {
        sc_regSet(M, 1);
        return -1;
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
        return -1;
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
    if (regist > 5 || regist <= 0) {
        return -1;
    }
    if (value != 1 && value != 0) {
        return -1;
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
    if ((regist > 5) || (regist <= 0)) {
        return -1;
    }
    value = ((reg >> (regist - 1)) & 0x1);
    return 0;
}

int sc_commandEncode(int command, int operand, int& value)
{
    if ((command == 0 && operand == 0) || (command == 0x10 || command == 0x11 || command == 0x20 || command == 0x21 || command > 0x29 && command < 0x34 || command > 0x39 && command < 0x44 || command > 0x50 && command < 0x77) && (operand >= 0 && operand <= 99)) {
        value = command * 128 + operand; // (command << 7) + operand
        return 0;
    }
    else {
        return -1;
    }
}

int sc_commandDecode(int value, int& command, int& operand)
{
    int c = value >> 7; //value / 128; // value >> 7
    int o = (~(c << 7)) & value; //value % 128; // (~(c << 7)) & value
    if (!(value & (1 << 14)) && (c == 0x10 || c == 0x11 || c == 0x20 || c == 0x21 || c > 0x29 && c < 0x34 || c > 0x39 && c < 0x44 || c > 0x50 && c < 0x77) && (o >= 0 && o <= 99) || value == 0) {
        command = c;
        operand = o;
        return 0;
    }
    else {
        sc_regSet(E, 1);
        return -1;
    }
}