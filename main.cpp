#include "myBigChars.h"
#include "myReadkey.h"
#include "simplepc.h"
#include "control.h"
#include <signal.h>
#include <sys/time.h>

extern int a[100];
extern int32_t reg;
extern int insc;
extern int accum;

extern int kurx, kury;
bool press = 0;
unsigned int** num = new unsigned int*[17];
extern bool timer;

void draw()
{
    mt_setbgcolor(black);
    mt_setfgcolor(white);
    mt_clrscr();
    mt_gotoXY(0, 0);
    int x, y;
    mt_getscreensize(x, y);
    bc_box(1, 1, 63, 12);
    mt_gotoXY(x * 0.75 / 2 - 4, 1);
    cout << "Memory" << endl;
    for (int i = 0; i < 10; i++) {
        mt_gotoXY(x * 0.75 / 2 - 29 - 1, i + 2);
        for (int j = 0; j < 10; j++) {
            int c, p;
            stringstream ss;
            string s;

            int vl;
            sc_memoryGet(i * 10 + j, vl);
            if (i == kurx && j == kury) {
                mt_setbgcolor(colors::red);
                mt_setfgcolor(colors::blue);
            }

            if (!(vl & (1 << 14))) {   
                sc_commandDecode(vl, c, p);
                cout << "+";

                ss << hex << c;
                ss >> s;

                if (s.size() == 1) {
                    cout << 0;
                }

                cout << hex << c;

                ss.clear();
                s.clear();

                ss << hex << p;
                ss >> s;

                if (s.size() == 1) {
                    cout << 0;
                }

                cout << hex << p;
            }
            else {
                vl &= ~(1 << 14);
                ss << hex << vl;
                ss >> s;

                cout << " ";
                for (int i = s.size(); i < 4; i++) {
                    cout << 0;
                }
                cout << s;
            }
            if (i == kurx && j == kury) {
                mt_setbgcolor(black);
                mt_setfgcolor(white);
            }
            cout << " ";
        }
    }
    stringstream sst;
    string st;

    bc_box((x + x * 0.75) / 2 - 9, 1, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 4, 1);
    cout << "accumulator";
    mt_gotoXY((x + x * 0.75) / 2 - 1, 2);

    sst << hex << accum;
    sst >> st;

    if (st.size() < 4) {
        reverse(st.begin(), st.end());
        while (st.size() < 4) {
            st.push_back('0');
        }
        reverse(st.begin(), st.end());
    }
    cout << st;
    st.clear();
    sst.clear();    


    bc_box((x + x * 0.75) / 2 - 9, 4, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 8, 4);
    cout << "instructionCounter";
    mt_gotoXY((x + x * 0.75) / 2 - 1, 5);


    sst << hex << insc;
    sst >> st;

    if (st.size() < 4) {
        reverse(st.begin(), st.end());
        while (st.size() < 4) {
            st.push_back('0');
        }
        reverse(st.begin(), st.end());
    }
    cout << st;

    bc_box((x + x * 0.75) / 2 - 9, 7, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 4, 7);
    cout << "Operarion";

    int vl;
    stringstream ss;
    sc_memoryGet(10 * kurx + kury, vl);
    bc_box(1, 13, (x * 0.6) - 4, 12);
    if (!(vl & (1 << 14))) {
        mt_gotoXY((x + x * 0.75) / 2 - 4, 8);
        int cm, op;
        string c, p;
        sc_commandDecode(vl, cm, op);

        ss << hex << cm;
        ss >> c;
        ss.clear();

        ss << hex << op;
        ss >> p;

        if (c.size() == 1) {
            c += '0';
            reverse(c.begin(), c.end());
        }

        if (p.size() == 1) {
            p += '0';
            reverse(p.begin(), p.end());
        }

        cout << '+' << c << " : " << p;

        bc_printbigchar(num[16], 2, 15, colors::white, colors::black);

        for (int i = 0, x = 11; i < 2; i++, x += 9) {
            bc_printbigchar(num[c[i] - '0'], x, 15, colors::white, colors::black);
        }

        for (int i = 0, x = 29; i < 2; i++, x += 9) {
            if (p[i] >= '0' && p[i] <= '9') {
                bc_printbigchar(num[p[i] - '0'], x, 15, colors::white, colors::black);
            }
            else {
                bc_printbigchar(num[p[i] - 'a' + 10], x, 15, colors::white, colors::black);
            }
        }
    }
    else {
        mt_gotoXY((x + x * 0.75) / 2 - 4, 8);
        cout << "+00 : 00";
        vl &= ~(1 << 14);
        
        string s;
        ss << hex << vl;
        ss >> s;

        reverse(s.begin(), s.end());
        for (int i = s.size(); i < 4; i++) {
            s.push_back('0');
        }
        reverse(s.begin(), s.end());

        for (int i = 0, x = 11; i < 4; i++, x += 9) {
            if (s[i] >= '0' && s[i] < '9') {
                bc_printbigchar(num[s[i] - '0'], x, 15, colors::white, colors::black);
            }
            else {
                bc_printbigchar(num[s[i] - 'a' + 10], x, 15, colors::white, colors::black);
            }
        }

    }

    bc_box((x + x * 0.75) / 2 - 9, 10, 20, 3);
    mt_gotoXY((x + x * 0.75) / 2 - 3, 10);
    cout << "Flags";
    mt_gotoXY((x + x * 0.75) / 2 - 5, 11);
    int val;
    sc_regGet(P, val);
    if (val) {
        mt_setfgcolor(colors::red);
        cout << "P ";
        mt_setfgcolor(colors::white);
    } else {
        cout << "P ";
    }

    sc_regGet(D, val);
    if (val) {
        mt_setfgcolor(colors::red);
        cout << "D ";
        mt_setfgcolor(colors::white);
    } else {
        cout << "D ";
    }

    sc_regGet(M, val);
    if (val) {
        mt_setfgcolor(colors::red);
        cout << "M ";
        mt_setfgcolor(colors::white);
    } else {
        cout << "M ";
    }

    sc_regGet(T, val);
    if (val) {
        mt_setfgcolor(colors::red);
        cout << "T ";
        mt_setfgcolor(colors::white);
    } else {
        cout << "T ";
    }

    sc_regGet(E, val);
    if (val) {
        mt_setfgcolor(colors::red);
        cout << "E ";
        mt_setfgcolor(colors::white);
    } else {
        cout << "E ";
    }

    bc_box((x * 0.6) - 3, 13, 38, 12);
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
    cout << "q - exit";
    mt_gotoXY((x * 0.6) - 2, 20);
    cout << "c - change memory value";
    mt_gotoXY((x * 0.6) - 2, 21);
    cout << "v - change register value";
    mt_gotoXY((x * 0.6) - 2, 22);
    cout << "F5 - accumulator";
    mt_gotoXY((x * 0.6) - 2, 23);
    cout << "F6 - instructionCounter";
    mt_gotoXY(x - 1, y);

    mt_gotoXY(2, 25);
    cout << "Input/Output:";
    mt_gotoXY(2, 26);
    cout << hex << insc << dec << " < " << endl;
    mt_gotoXY(2, 27);
    cout << hex << insc << dec << " > " << endl;
}

void sing(int sn)
{
    if (sn == SIGALRM) {
        int t;
        sc_regGet(T, t);

        if (!t) {
            if (kury < 9) {
                kury++;
            }
            else {
                kury = 0;
                if (kurx < 9) {
                    kurx++;
                }
                else {
                    kurx = 0;
                }
            }
            if (insc < 99) {
                insc++;
            }
            else {
                insc = 0;
            }
            if (!press) {
                draw();
            }
        }
    } else {
        signal(SIGALRM, SIG_IGN);
        timer = 0;
        kurx = kury = 0;
        sc_regInit();
        sc_memoryInit();
        insc = 0;
    }
}

int32_t main()
{
    // terminal size - 88x29
    printf("\e[8;%d;%d;t", 29, 88);

    for (int i = 0; i < 17; i++) {
        num[i] = new unsigned int[2];
    }

    int tmp;
    bc_bigcharread("bigchar.bin", num, 17, tmp);

    bool q = 0;

    sc_memoryInit();
    sc_regInit();

    signal(SIGUSR1, sing);

    while (!q) {
        draw();

        int sgt = 1;
        sc_regGet(T, sgt);

        keys k;

        int ans = rk_readkey(k);

        if (!ans && k == keys::i) {
            raise(SIGUSR1);
        } else if (!ans && !sgt) {
            press = 1;
            switch (k) {
            case keys::q: {
                q = 1;

                break;
            }
            case keys::arrU: {
                if (kurx == 0) {
                    kurx = 9;
                } else {
                    kurx--;
                }

                break;
            }
            case keys::arrD: {
                if (kurx == 9) {
                    kurx = 0;
                } else {
                    kurx++;
                }

                break;
            }
            case keys::arrL: {
                if (kury == 0) {
                    kury = 9;
                } else {
                    kury--;
                }

                break;
            }
            case keys::arrR: {
                if (kury == 9) {
                    kury = 0;
                } else {
                    kury++;
                }

                break;
            }
            case keys::c: {
                mt_clrscr();
                int c, p, value;
                cout << "Enter command and operand: ";
                cin >> hex >> c >> dec >> p;

                if (!sc_commandEncode(c, p, value)) {
                    sc_memorySet(kurx * 10 + kury, value);
                } else {
                    cout << "Error! Invalid command or operand number. Press "
                            "enter to continue.";

                    cin.get();
                    cin.get();
                }

                break;
            }
            case keys::s: {
                mt_clrscr();
                string s;

                cout << "Enter file name: ";
                cin >> s;

                if (s.size() < 5 || s.find('.') == string::npos) {
                    cout << "Error! Invalid file name. Press enter to "
                            "continue.";

                    cin.get();
                    cin.get();

                    break;
                }

                if (s.substr(s.size() - 4, s.size()) != ".bin") {
                    cout << "Error! Invalid file format. Supported only .bin "
                            "format. Press enter to continue.";

                    cin.get();
                    cin.get();

                    break;
                }

                sc_memorySave(s);

                break;
            }

            case keys::l: {
                mt_clrscr();
                string s;

                cout << "Enter file name: ";
                cin >> s;

                if (s.size() < 5 || s.find('.') == string::npos) {
                    cout << "Error! Invalid file name. Press enter to "
                            "continue.";

                    cin.get();
                    cin.get();

                    break;
                }

                if (s.substr(s.size() - 4, s.size()) != ".bin") {
                    cout << "Error! Invalid file format. Supported only .bin "
                            "format. Press enter to continue.";

                    cin.get();
                    cin.get();

                    break;
                }

                if (sc_memoryLoad(s) == -1) {
                    cout << "Error! File with name" << s
                         << "does not exist. Press enter to continue.";

                    cin.get();
                    cin.get();
                }

                break;
            }
            case keys::v: {
                mt_clrscr();
                int r, v;

                cout << "Enter register (1 - 5) number and value (0 or 1): ";

                cin >> r >> v;

                if (sc_regSet(r, v) == -1) {
                    cout << "Error! Invalid values. Press enter to continue.";

                    cin.get();
                    cin.get();
                }

                break;
            }
            case keys::F6: {
                mt_clrscr();

                int a;

                cout << "Enter the coordinate of the cursor (value: 0-99) ";
                cin >> a;

                if (a < 0 || a > 99) {
                    cout << "Error! Incorrect coordinate entered. Press "
                            "enter to continue.";

                    cin.get();
                    cin.get();

                    break;
                }

                insc = a;
                kurx = insc / 10;
                kury = insc - 10 * kurx;

                break;
            }
            case keys::r: {
                if (!timer) {
                    struct itimerval nv, ov;

                    signal(SIGALRM, sing);

                    nv.it_interval.tv_sec = 1;
                    nv.it_interval.tv_usec = 500;
                    nv.it_value.tv_sec = 1;
                    nv.it_value.tv_usec = 500;

                    setitimer(ITIMER_REAL, &nv, &ov);

                    timer = 1;
                }

                break;
            }
            case keys::t: {
                CU();

                break;
            }
            case keys::F5: {
                mt_clrscr();
                int t;
                cout << "Enter accumulator value (-8192 ";
                bc_printA('y');
                cout << " value ";
                bc_printA('y');
                cout << " 8191): "; 

                cin >> t;

                if (t < -8192 || t > 8191) {
                    cout << "Error! A value has been entered that overflows memory. Press enter to continue.";
                    
                    cin.get();
                    cin.get();

                    break;
                }
                
                if (t >= 0) {
                    accum = t;
                }
                else {
                    bitset<14> e(t);
                    accum = e.to_ulong();
                }

                break;
            }
            }
            press = 0;
            insc = kurx * 10 + kury;
        }
    }

    return 0;
}