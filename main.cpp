#include "simplepc.h"
#include "myBigChars.h"

extern int a[100];
extern int32_t reg;

int32_t main()
{
    mt_setbgcolor(black);
    mt_setfgcolor(white);
    mt_clrscr();
    int x, y;
    mt_getscreensize(x, y);
    bc_box(1, 1, 62, 12);
    mt_gotoXY(x * 0.75 / 2 - 4, 1);
    cout << "Memory" << endl;
    for (int i = 0; i < 10; i++) {
        mt_gotoXY(x * 0.75 / 2 - 29 - 1, i + 2);
        for (int j = 0; j < 10; j++) {
                if (i == 5 && j == 5) {
                    mt_setbgcolor(colors::red);
                    mt_setfgcolor(colors::blue);

                    cout << "+9999";

                    mt_setbgcolor(black);
                    mt_setfgcolor(white);

                    cout << " ";
                }
                else {
                    cout << "+0000" << " ";
                }
        }
    }
    bc_box((x + x * 0.75) / 2 - 9, 1, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 4, 1);
    cout << "accumulator";
    mt_gotoXY((x + x * 0.75) / 2 - 2, 2);
    cout << "+9999";
    bc_box((x + x * 0.75) / 2 - 9, 4, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 8, 4);
    cout << "instructionCounter";
    mt_gotoXY((x + x * 0.75) / 2 - 2, 5);
    cout << "+0000";
    bc_box((x + x * 0.75) / 2 - 9, 7, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 4, 7);
    cout << "Operarion";
    mt_gotoXY((x + x * 0.75) / 2 - 4, 8);
    cout << "+00 : 00";
    bc_box((x + x * 0.75) / 2 - 9, 10, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 3, 10);
    cout << "Flags";
    mt_gotoXY((x + x * 0.75) / 2 - 4, 11);
    cout << "O E V M";

    bc_box((x * 0.6) - 3, 13, 38, 10);
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

    bc_box(1, 13, (x * 0.6) - 4, 10);
    unsigned int a[2] = {4279769112, 404232447}, b[2] = {4286677503, 405823680};
    bc_printbigchar(a, 2, 14, colors::white, colors::black);
    for (int i = 0, x = 11; i < 4; i++, x += 9) {
        bc_printbigchar(b, x, 14, colors::white, colors::black); 
    }

    mt_gotoXY(x * 0.75 / 2 - 29, 25);
    cout << "Input/Output:" << endl;
    mt_gotoXY(x * 0.75 / 2 - 29, 26);
    cout << "35< +1F1F" << endl;
    mt_gotoXY(x * 0.75 / 2 - 29, 27);
    cout << "35< +1F1F" << endl;



    // unsigned int a[2] = {117637376, 4282326799};

    // bc_setbigcharpos(a, 7, 7, 1);

    // unsigned **a, **b;
    // b = new unsigned int *[2];
    // for (int i = 0; i < 2; i++) {
    //     b[i] = new unsigned int[2];
    // }
    // a = new unsigned int *[2];
    // for (int i = 0; i < 2; i++) {
    //     a[i] = new unsigned int[2];
    // }

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         a[i][j] = 1;
    //     }
    // }

    // int t;

    // bc_bigcharwrite("out.bin", a, 2);

    // bc_bigcharread("out.bin", b, 2, t);

    

    return 0;
}