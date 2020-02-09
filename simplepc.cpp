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
    if (address < 0 || address >= 101) {
        cout << "Error! Invalid address number\n";
        sc_regSet(2, 1);
        return 1;
    } else {
        a[address] = value;
        return 0;
    }
}

int sc_memoryGet(int address, int* value)
{
    if (address < 0 || address >= 101) {
        cout << "Error! Invalid address number:" << address << endl;
        return 1;
    } else {
        *value = a[address];
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
    if (regist > 4 || regist < 0) {
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

int sc_regGet(int regist, int* value)
{
    if ((regist > 4) || (regist < 0)) {
        cout << "Error! Invalid register number\n";
        return 1;
    }
    *value = (reg >> (regist - 1)) & 0x1;
    return 0;
}

int sc_commandEncode(int command, int operand, int* value)
{
    *value = command * 128 + operand;
    return 0;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    *command = value / 128;
    *operand = value % 128;
    return 0;
}