#include "control.h"
#include "draw.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "mySignal.h"
#include "simplepc.h"
#include <signal.h>
#include <sys/time.h>

extern int a[100];
extern int32_t reg;
extern int insc;
extern int accum;
extern int kurx, kury;
extern unsigned int** num;
extern bool timer;

extern void sing(int sn);

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

    struct itimerval nv, ov;

    nv.it_interval.tv_sec = 1;
    nv.it_interval.tv_usec = 500;
    nv.it_value.tv_sec = 1;
    nv.it_value.tv_usec = 500;

    ov.it_interval.tv_sec = 0;
    ov.it_interval.tv_usec = 0;
    ov.it_value.tv_sec = 0;
    ov.it_value.tv_usec = 0;

    while (!q) {
        draw();

        keys k;

        int ans = rk_readkey(k);
        int sgt;
        sc_regGet(T, sgt);

        if (!ans && k == keys::i) {
            raise(SIGUSR1);
        } else if (!ans && !sgt) {
            if (timer) {
                setitimer(ITIMER_REAL, &ov, NULL);
            }
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

                insc = kurx * 10 + kury;
                break;
            }
            case keys::arrD: {
                if (kurx == 9) {
                    kurx = 0;
                } else {
                    kurx++;
                }

                insc = kurx * 10 + kury;
                break;
            }
            case keys::arrL: {
                if (kury == 0) {
                    kury = 9;
                } else {
                    kury--;
                }

                insc = kurx * 10 + kury;
                break;
            }
            case keys::arrR: {
                if (kury == 9) {
                    kury = 0;
                } else {
                    kury++;
                }

                insc = kurx * 10 + kury;
                break;
            }
            case keys::c: {
                mt_clrscr();
                int c, p, value, x = kurx, y = kury;
                cout << "Enter command and operand: ";
                cin >> hex >> c >> dec >> p;

                if (!sc_commandEncode(c, p, value)) {
                    sc_memorySet(x * 10 + y, value);
                } else {
                    mt_setfgcolor(colors::red);
                    cout << "Error! Invalid command or operand number. Press "
                            "enter to continue.";
                    mt_setfgcolor(colors::white);

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
                    mt_setfgcolor(colors::red);
                    cout << "Error! Invalid file name. Press enter to "
                            "continue.";
                    mt_setfgcolor(colors::white);

                    cin.get();
                    cin.get();

                    break;
                }

                if (s.substr(s.size() - 4, s.size()) != ".bin") {
                    mt_setfgcolor(colors::red);
                    cout << "Error! Invalid file format. Supported only .bin "
                            "format. Press enter to continue.";
                    mt_setfgcolor(colors::white);

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

                if (s.find('.') == string::npos) {
                    mt_setfgcolor(colors::red);
                    cout << "Error! Invalid file name. Press enter to "
                            "continue.";
                    mt_setfgcolor(colors::white);

                    cin.get();
                    cin.get();

                    break;
                }

                if ((s.size() >= 5 && s.substr(s.size() - 4, 4) == ".bin")
                    || (s.size() >= 3 && s.substr(s.size() - 2, 2) == ".o")) {
                    if (sc_memoryLoad(s) == -1) {
                        mt_setfgcolor(colors::red);
                        cout << "Error! File with name " << s
                             << " contains an unsupported command or does not "
                                "exist. Press enter to continue.";
                        mt_setfgcolor(colors::white);

                        cin.get();
                        cin.get();

                        break;
                    }
                } else {
                    mt_setfgcolor(colors::red);
                    cout << "Error! Invalid file format. Supported only .bin "
                            "and .o "
                            "format. Press enter to continue.";
                    mt_setfgcolor(colors::white);

                    cin.get();
                    cin.get();

                    break;
                }

                kurx = kury = 0;
                sc_regInit();
                insc = 0;
                accum = 0;

                if (timer) {
                    signal(SIGALRM, SIG_IGN);
                    timer = 0;
                }

                break;
            }
            case keys::v: {
                mt_clrscr();
                int r, v;

                cout << "Enter register (1 - 5) number and value (0 or 1): ";

                cin >> r >> v;

                if (sc_regSet(r, v) == -1) {
                    mt_setfgcolor(colors::red);
                    cout << "Error! Invalid values. Press enter to continue.";
                    mt_setfgcolor(colors::white);

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
                    mt_setfgcolor(colors::red);
                    cout << "Error! Incorrect coordinate entered. Press "
                            "enter to continue.";
                    mt_setfgcolor(colors::white);

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
                    signal(SIGALRM, sing);
                    setitimer(ITIMER_REAL, &nv, NULL);

                    timer = 1;
                }

                break;
            }
            case keys::t: {
                if (!timer) {
                    CU();
                }

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
                    mt_setfgcolor(colors::red);
                    cout << "Error! A value has been entered that overflows "
                            "memory. Press enter to continue.";
                    mt_setfgcolor(colors::white);

                    cin.get();
                    cin.get();

                    break;
                }

                if (t >= 0) {
                    accum = t;
                } else {
                    bitset<14> e(t);
                    accum = e.to_ulong();
                }

                break;
            }
            }
            if (timer) {
                setitimer(ITIMER_REAL, &nv, NULL);
            }
        }
    }

    return 0;
}