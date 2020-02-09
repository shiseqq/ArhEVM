#include  "simplepc.h"

int* a;
int32_t reg = 0;

int sc_memoryInit() {
    a = new int[100];
    for (int i = 0; i < 100; i++) {
        a[i] = 0;
    }
    return 0;
}

int sc_memorySet (int address, int value) {
    if (address < 0 || address > 99) {
        reg |= 1;
        return 1;
    }
    else {
        a[address] = value;
        return 0;
    }
}

int sc_memoryGet (int address, int& value) {
    if (address < 0 || address > 99) {
        reg |= 2;
        return 1;
    }
    else {
        value = a[address];
        return 0;
    }
}

int sc_memorySave (string filename) {
    ofstream out(filename, ios::binary);
    out.write((char*)a, sizeof(a));
    out.close();
    return 0;
}

int sc_memoryLoad (string filename) {
    ifstream inp(filename, ios::binary);
    if (!inp.is_open()) {
        return 1;
    }
    else {
        inp.read((char*)a, sizeof(a));
        return 0;
    }
}