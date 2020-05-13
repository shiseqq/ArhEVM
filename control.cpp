#include "control.h"
#include "myTerm.h"
#include "simplepc.h"

extern int a[100];
extern int32_t reg;
extern int insc;
extern int accum;

int kurx = 0, kury = 0;
bool timer = 0;
int prev_oper = -1, pos;
bool done = 0, mv;

int CU()
{
    int command, operand;

    if (sc_commandDecode(a[insc], command, operand) == -1) {
        sc_regSet(T, 1);
        sc_regSet(E, 1);
        signal(SIGALRM, SIG_IGN);
        return -1;
    }

    if (command >= 0x30 && command <= 0x33) {
        prev_oper = a[insc];
        return ALU(command, operand);
    }

    switch (command) {
    case 0x10: {
        stringstream ss;
        string num;
        mt_gotoXY(2, 26);
        cout << hex << insc << dec << " < ";
        cin >> num;

        for (auto& i : num) {
            if (i != '+' && i != '-' && (i < '0' || i > '9')) {
                mt_gotoXY(2, 26);
                cout << hex << insc << dec << " < ";
                mt_setfgcolor(colors::red);
                cout << "Error! No number entered! Press enter to continue.";
                mt_setfgcolor(colors::white);

                cin.get();
                cin.get();

                mt_gotoXY(2, 26);
                cout << hex << insc << dec << " < ";

                done = 0;
                return -1;
            }
        }

        int n;
        ss << num;
        ss >> n;

        if (n >= -8192 && n <= 8191) {
            if (n >= 0) {
                n |= 1 << 14;
                sc_memorySet(operand, n);
            } else {
                bitset<14> bt(n);
                int e = bt.to_ulong();
                e |= 1 << 14;

                sc_memorySet(operand, e);
            }

        } else {
            sc_regSet(M, 1);
            mt_gotoXY(2, 28);
            mt_setfgcolor(colors::red);
            cout << "Error! Out of memory! Press enter to continue.";
            mt_setfgcolor(colors::white);

            cin.get();
            cin.get();

            done = 0;
            return -1;
        }

        prev_oper = a[insc];
        done = 1;
        break;
    }
    case 0x11: {
        int vl;
        sc_memoryGet(operand, vl);

        if (vl & (1 << 14)) {
            vl &= ~(1 << 14);

            if (vl & (1 << 13)) {
                bitset<14> bt(vl - 1);
                bt.flip();

                mt_gotoXY(2, 27);
                cout << hex << insc << dec << " > -" << bt.to_ulong() << endl
                     << "Press enter to continue.";

                cin.get();
                cin.get();

            } else {
                mt_gotoXY(2, 27);
                cout << hex << insc << dec << " > " << vl << endl
                     << "Press enter to continue.";

                cin.get();
                cin.get();
            }
        } else {
            mt_gotoXY(2, 28);
            mt_setfgcolor(colors::red);
            cout << "Error! The command is stored in this memory location. "
                    "Press enter to "
                    "continue.";
            mt_setfgcolor(colors::white);

            cin.get();
            cin.get();

            done = 0;
            return -1;
        }

        prev_oper = a[insc];
        done = 1;
        break;
    }
    case 0x20: {
        int vl;
        sc_memoryGet(operand, vl);

        if (vl & (1 << 14)) {
            vl &= ~(1 << 14);
            accum = vl;
        } else {
            mt_gotoXY(2, 28);
            mt_setfgcolor(colors::red);
            cout << "Error! The command is stored in this memory location. "
                    "Press enter to "
                    "continue.";
            mt_setfgcolor(colors::white);

            cin.get();
            cin.get();

            done = 0;
            return -1;
        }

        prev_oper = a[insc];
        done = 1;
        break;
    }
    case 0x21: {
        int t = accum | (1 << 14);
        sc_memorySet(operand, t);

        prev_oper = a[insc];
        done = 1;
        break;
    }
    case 0x40: {
        mv = 1;
        prev_oper = a[insc];
        insc = operand;
        kurx = insc / 10;
        kury = insc - 10 * kurx;

        done = 1;
        break;
    }
    case 0x41: {
        prev_oper = a[insc];
        if (accum & (1 << 13)) {
            mv = 1;
            insc = operand;
            kurx = insc / 10;
            kury = insc - 10 * kurx;

        } else {
            mv = 0;
            pos = insc;
        }

        done = 1;
        break;
    }
    case 0x42: {
        prev_oper = a[insc];
        if (accum == 0) {
            mv = 1;
            insc = operand;
            kurx = insc / 10;
            kury = insc - 10 * kurx;
        } else {
            mv = 0;
            pos = insc;
        }

        done = 1;
        break;
    }
    case 0x43: {
        if (timer) {
            signal(SIGALRM, SIG_IGN);
            if (insc > 0) {
                insc--;
            } else {
                insc = 99;
            }
            kurx = insc / 10;
            kury = insc - 10 * kurx;
            timer = 0;
        }

        prev_oper = -1;
        done = 0;
        break;
    }
    case 0x59: {
        int t = a[insc];
        if (prev_oper != -1) {
            int c, o;
            sc_commandDecode(prev_oper, c, o);
            if (done
                && ((c >= 0x30 && c <= 0x33 && (accum & 1))
                    || (mv && (c >= 0x40 && c <= 0x42 && (o & 1)))
                    || (!mv && (c >= 0x40 && c <= 0x42 && (pos & 1)))
                    || (c >= 0x10 && c <= 0x11 && (a[o] & 1))
                    || (c >= 0x20 && c <= 0x21 && (a[o] & 1))
                    || (mv && c == 0x59 && (o & 1))
                    || (!mv && c == 0x59 && (pos & 1)))) {
                insc = operand;
                kurx = insc / 10;
                kury = insc - 10 * kurx;
                mv = 1;
            } else {
                pos = insc;
                mv = 0;
            }
        } else {
            pos = insc;
            mv = 0;
        }
        prev_oper = t;

        done = 1;
        break;
    }
    }

    return 0;
}

int ALU(int command, int operand)
{
    int x = accum, y, res;
    bitset<14>* bt;

    sc_memoryGet(operand, y);

    if (!(y & (1 << 14))) {
        mt_gotoXY(2, 28);
        mt_setfgcolor(colors::red);
        cout << "Error! The command is stored in this memory location. "
                "Press enter to "
                "continue.";
        mt_setfgcolor(colors::white);

        cin.get();
        cin.get();

        done = 0;
        return -1;
    }

    y &= ~(1 << 14);

    if (x & (1 << 13)) {
        bt = new bitset<14>(x - 1);
        bt->flip();
        x = -bt->to_ulong();
        delete bt;
    }

    if (y & (1 << 13)) {
        bt = new bitset<14>(y - 1);
        bt->flip();
        y = -bt->to_ulong();
        delete bt;
    }

    switch (command) {
    case 0x30: {
        res = x + y;

        break;
    }
    case 0x31: {
        res = x - y;

        break;
    }
    case 0x32: {
        if (y == 0) {
            sc_regSet(D, 1);

            mt_gotoXY(2, 28);
            mt_setfgcolor(colors::red);
            cout << "Error! Division by zero. Press enter to continue.";
            mt_setfgcolor(colors::white);

            cin.get();
            cin.get();

            done = 0;
            return -1;
        }

        res = x / y;

        break;
    }
    case 0x33: {
        res = x * y;

        break;
    }
    }

    if (res < -8192 || res > 8191) {
        sc_regSet(P, 1);
        mt_gotoXY(2, 28);
        mt_setfgcolor(colors::red);
        cout << "Error! Memory overflow during operation. Press enter to "
                "continue.";
        mt_setfgcolor(colors::white);

        cin.get();
        cin.get();

        done = 0;
        return -1;
    }

    if (res >= 0) {
        accum = res;
    } else {
        bt = new bitset<14>(res);
        accum = bt->to_ulong();
        delete bt;
    }

    done = 1;
    return 0;
}