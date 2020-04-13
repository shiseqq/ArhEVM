#include "simplepc.h"
#include "myBigChars.h"
#include "myReadkey.h"

extern int a[100];
extern int32_t reg;

int32_t main()
{
    bool q = 0;
    int kurx = 0, kury = 0;

    sc_memoryInit();
    sc_regInit();

    while (!q) {
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
                    int c, p;
                    stringstream ss;
                    string s;

                    int vl;
                    sc_memoryGet(i * 10 + j, vl);
                    sc_commandDecode(vl, c, p);
                    if (i == kurx && j == kury) {
                        mt_setbgcolor(colors::red);
                        mt_setfgcolor(colors::blue);

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

                        mt_setbgcolor(black);
                        mt_setfgcolor(white);

                        printf(" ");
                    }
                    else {
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
                        cout << " ";
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
        mt_gotoXY((x + x * 0.75) / 2 - 5, 11);
        // cout << "O E V M";
        int val;
        sc_regGet(P, val);
        if (val) {
            mt_setfgcolor(colors::red);
            cout << "P ";
            mt_setfgcolor(colors::white);
        }
        else {
            cout << "P ";
        } 

        sc_regGet(D, val);
        if (val) {
            mt_setfgcolor(colors::red);
            cout << "D ";
            mt_setfgcolor(colors::white);
        }
        else {
            cout << "D ";
        }

        sc_regGet(M, val);
        if (val) {
            mt_setfgcolor(colors::red);
            cout << "M ";
            mt_setfgcolor(colors::white);
        }
        else {
            cout << "M ";
        }   

        sc_regGet(T, val);
        if (val) {
            mt_setfgcolor(colors::red);
            cout << "T ";
            mt_setfgcolor(colors::white);
        }
        else {
            cout << "T ";
        }

        sc_regGet(E, val);
        if (val) {
            mt_setfgcolor(colors::red);
            cout << "E ";
            mt_setfgcolor(colors::white);
        }
        else {
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

        unsigned int **num = new unsigned int *[11];
        for (int i = 0; i < 11; i++) {
            num[i] = new unsigned int[2];
        }

        int tmp;
        bc_bigcharread("bigchar.bin", num, 11, tmp); 

        bc_box(1, 13, (x * 0.6) - 4, 12);
        bc_printbigchar(num[10], 2, 15, colors::white, colors::black);

        int vl, cm, op;
        stringstream ss;
        string c, p;
        sc_memoryGet(10 * kurx + kury, vl);
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

        for (int i = 0, x = 11; i < 2; i++, x += 9) {
            bc_printbigchar(num[c[i] - '0'], x, 15, colors::white, colors::black); 
        }

        for (int i = 0, x = 29; i < 2; i++, x += 9) {
            bc_printbigchar(num[p[i] - '0'], x, 15, colors::white, colors::black); 
        }

        mt_gotoXY(x * 0.75 / 2 - 29, 25);
        cout << "Input/Output:" << endl;
        mt_gotoXY(x * 0.75 / 2 - 29, 26);
        cout << "35< +1F1F" << endl;
        mt_gotoXY(x * 0.75 / 2 - 29, 27);
        cout << "35< +1F1F" << endl;

        keys k;
    
        int ans = rk_readkey(k);

        if (!ans) {
            switch (k) {
                case keys::q: {
                    q = 1;

                    break;
                }
                case keys::arrU: {
                    if (kurx == 0) {
                        kurx = 9;
                    }
                    else {
                        kurx--;
                    }

                    break;
                }
                case keys::arrD: {
                    if (kurx == 9) {
                        kurx = 0;
                    }
                    else {
                        kurx++;
                    }

                    break;
                }
                case keys::arrL: {
                    if (kury == 0) {
                        kury = 9;
                    }
                    else {
                        kury--;
                    }

                    break;
                }
                case keys::arrR: {
                    if(kury == 9) {
                        kury = 0;
                    }
                    else {
                        kury++;
                    }

                    break;
                }
                case keys::c: {
                    mt_clrscr();
                    int c, p, value;
                    cout << "Enter command and operand: ";
                    cin >> hex >> c >> p;

                    if (!sc_commandEncode(c, p, value)) {
                        sc_memorySet(kurx * 10 + kury, value);
                    }
                    else {
                        cout << "Error! Invalid command or operand number. Press any key to continue.";
                        
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
                        cout << "Error! Invalid file name. Press any key to continue.";

                        cin.get();
                        cin.get();

                        break;
                    }

                    if (s.substr(s.size() - 4, s.size()) != ".bin") {
                        cout << "Error! Invalid file format. Supported only .bin format. Press any key to continue.";

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
                        cout << "Error! Invalid file name. Press any key to continue.";

                        cin.get();
                        cin.get();

                        break;
                    }

                    if (s.substr(s.size() - 4, s.size()) != ".bin") {
                        cout << "Error! Invalid file format. Supported only .bin format. Press any key to continue.";

                        cin.get();
                        cin.get();

                        break; 
                    }

                    if (sc_memoryLoad(s) == -1) {
                        cout << "Error! File with name" << s << "does not exist. Press any key to continue.";

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
                            cout << "Error! Invalid values. Press any key to continue.";

                            cin.get();
                            cin.get();
                        }
    

                    break;
                }
            }
        }
    }

    return 0;
}