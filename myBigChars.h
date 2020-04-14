#ifndef _MYBIGCHARS_H

#include "myTerm.h"
#include <bits/stdc++.h>

using namespace std;

int bc_printA(string str);
int bc_printA(char c);
int bc_box(int x1, int y1, int width, int height);
int bc_printbigchar(unsigned int a[2], int x, int y, colors cl, colors bg);
int bc_setbigcharpos(unsigned int* big, int x, int y, int value);
int bc_getbigcharpos(unsigned int* big, int x, int y, int& value);
int bc_bigcharwrite(string file, unsigned int**& big, int count);
int bc_bigcharread(
        string file, unsigned int**& big, int count, int& read_count);

#endif