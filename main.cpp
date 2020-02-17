#include "simplepc.h"
#include "myTerm.h"

extern int a[100];
extern int32_t reg;

int32_t main()
{
    mt_setbgcolor(black);
    mt_clrscr();
    int x, y;
    mt_getscreensize(x, y);
    mt_gotoXY(x * 0.75 / 2 - 2, 1);
    cout << "Memory" << endl;
    for (int i = 0; i < 10; i++) {
        mt_gotoXY(x * 0.75 / 2 - 29, i + 2);
        for (int j = 0; j < 10; j++) {
                cout << "+0000" << " ";
        }
    }
    mt_gotoXY((x + x * 0.75) / 2 - 4, 1);
    cout << "accumulator";
    mt_gotoXY((x + x * 0.75) / 2 - 1, 2);
    cout << "+9999";
    mt_gotoXY((x + x * 0.75) / 2 - 7, 4);
    cout << "instructionCounter";
    mt_gotoXY((x + x * 0.75) / 2 - 1, 5);
    cout << "+0000";
    mt_gotoXY((x + x * 0.75) / 2 - 3, 7);
    cout << "Operarion";
    mt_gotoXY((x + x * 0.75) / 2 - 3, 8);
    cout << "+00 : 00";
    mt_gotoXY((x + x * 0.75) / 2 - 2, 10);
    cout << "Flags";
    mt_gotoXY((x + x * 0.75) / 2 - 3, 11);
    cout << "O E V M";
    mt_gotoXY((x * 0.6) - 1, 13);
    cout << "Keys:";
    mt_gotoXY((x * 0.6) - 2, 14);
    cout << "l - load";
    mt_gotoXY((x * 0.6) - 2, 15);
    cout << "s - save";
    mt_gotoXY((x * 0.6) - 2, 16);
    cout << "r - run";
    mt_gotoXY((x * 0.6) - 2, 17);
    cout << "t - step";
    mt_gotoXY((x * 0.6) - 2, 18);
    cout << "i - reset";
    mt_gotoXY((x * 0.6) - 2, 19);
    cout << "F5 - accumulator";
    mt_gotoXY((x * 0.6) - 2, 20);
    cout << "F6 - instructionCounter";
    mt_gotoXY(x - 1, y);

    mt_gotoXY(x * 0.75 / 2 - 29, 25);
    cout << "Input/Output:" << endl;
    mt_gotoXY(x * 0.75 / 2 - 29, 26);
    cout << "35< +1F1F" << endl;
    mt_gotoXY(x * 0.75 / 2 - 29, 27);
    cout << "35< +1F1F" << endl;

    return 0;
}