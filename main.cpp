#include "simplepc.h"

extern int a[100];
extern int32_t reg;

int32_t main()
{
    cout << "Registre init:" << endl;
    sc_regInit();
    cout << reg << endl << endl;

    sc_memoryInit();
    cout << "Memory init:" << endl;
    for (int i = 0; i < 100; i++) {
        cout << a[i] << " ";
    }
    cout << endl << endl;

    sc_memorySet(1, 5);
    cout << "Memory set address - 1, value - 5:" << endl;
    for (int i = 0; i < 100; i++) {
        cout << a[i] << " ";
    }
    cout << endl << endl;

    int t;
    sc_memoryGet(1, t);
    cout << "Memory get address - 1, value - 5:" << endl;
    cout << t << endl << endl;

    cout << "Memory save and load:" << endl;
    sc_memorySave("sc.bin");
    sc_memoryLoad("sc.bin");
    for (int i = 0; i < 100; i++) {
        cout << a[i] << " ";
    }
    cout << endl << endl;

    cout << "Register set address - 2, value - 1:" << endl;
    sc_regSet(2, 1);
    cout << reg << endl << endl;

    int r;
    cout << "Register get address - 2, value - 1:" << endl;
    sc_regGet(2, r);
    cout << r << endl << endl;

    int value;
    cout << "Command encode command - 10, operand - 60" << endl;
    sc_commandEncode(10, 60, value);
    cout << value << endl << endl;

    int c, p;
    cout << "Command decode:" << endl;
    sc_commandDecode(value, c, p);
    cout << "Command - " << c << " Operand - " << p << endl << endl; 

    return 0;
}