#include "myBigChars.h"

int bc_printA(string str) {
    printf("\E(0");
    cout << str;
    printf("\E(B");
    return 0;
}

int bc_printA(char c) {
    printf("\E(0");
    cout << c;
    printf("\E(B");
    return 0;
}

int bc_box (int x1, int y1, int width, int height) {
    int col, row;
    mt_getscreensize(col, row);

    if (x1 < 1 || y1 < 1 || x1 + width > col || y1 + height > row || width < 2 || height < 2) {
        return -1;
    }
    

    mt_gotoXY(x1, y1);
    bc_printA('l');
    for (int i = 1; i < width - 1; i++) {
        bc_printA('q');
    }
    mt_gotoXY(x1 + width - 1, y1);
    bc_printA('k');

    for (int i = 1; i < height - 1; i++) {
        mt_gotoXY(x1, y1 + i);
        bc_printA('x');
        mt_gotoXY(x1 + width - 1, y1 + i);
        bc_printA('x');
    }

    mt_gotoXY(x1, y1 + height - 1);
    bc_printA('m');
    for (int i = 1; i < width - 1; i++) {
        bc_printA('q');
    }

    mt_gotoXY(x1 + width - 1, y1 + height - 1);
    bc_printA('j');

    return 0;
}

int bc_printbigchar (unsigned int a[2], int x, int y, colors cl, colors bg) {
    int col, row;
    mt_getscreensize(col, row);

    if (x < 1 || y < 1 || x + 8 > col || y + 8 > row) {
        return -1;
    }

    mt_setfgcolor(cl);
    mt_setbgcolor(bg);
    for (int i = 0 ; i < 2; i++) {
        int t = 1;
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 8; k++) {
                mt_gotoXY(x + k, y + j);
                if (a[i] & t) {
                    bc_printA('a');
                }
                else {
                    mt_setbgcolor(bg);
                    cout << ' ';
                }
                t <<= 1;
            }
        }
        y += 4;
    }

    return 0;
}

int bc_setbigcharpos (unsigned int* big, int x, int y, int value) {
    if (x < 0 || y < 0 || x > 8 || y > 8 || (value != 1 && value != 0)) {
        return -1;
    }

    unsigned int i = (x > 3 ? 1 : 0);

    if (value) {
        big[i] |= 1 << ((x % 4) * 8 + y);
    }
    else {
        big[i] &= ~(1 << ((x % 4) * 8 + y));
    }
    
}

int bc_getbigcharpos(unsigned int* big, int x, int y, int& value) {
    if (x < 0 || y < 0 || x > 8 || y > 8) {
        return -1;
    }

    unsigned int t = big[(x > 3 ? 1 : 0)] & (1 << ((x % 4) * 8 + y));

    while (!(t & 1) && t > 0) {
        t >>= 1;
    }
    value = t;

    return 0;
}

int bc_bigcharwrite (string file, unsigned int** &big, int count) {
    if (count < 1) {
        return -1;
    }

    ofstream out(file, ios::binary);

    for (int i = 0; i < count; i++) {
        out.write((char*)&big[i], sizeof(big[i]));
    }

    out.close();

    return 0;
}

int bc_bigcharread (string file, unsigned int** &big, int count, int& read_count) {
    ifstream inp(file, ios::binary);
    read_count = 0;

    if (count < 1 || !inp.is_open()) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        inp.read((char*)&big[i], sizeof(big[i]));
        if (inp.eof()) {
            read_count = 0;
            return -1;
        }
        read_count += sizeof(big[i]);
    }

    inp.close();

    return 0;
}