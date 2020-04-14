#ifndef _MYTERM_H

#include <bits/stdc++.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

enum colors { black, red, green, yellow, blue, magenta, cyan, white };

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int& cols, int& rows);
int mt_setfgcolor(colors color);
int mt_setbgcolor(colors color);

#endif