#include "myTerm.h"

int mt_clrscr()
{
    printf("\E[H\E[J");
    return 0;
}

int mt_gotoXY(int x, int y)
{
    if (x >= 0 && y >= 0) {
        printf("\E[%d;%dH", y, x);
        return 0;
    }
    return -1;
}

int mt_getscreensize(int& cols, int& rows)
{
    winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    cols = size.ws_col;
    rows = size.ws_row;
    return 0;
}

int mt_setfgcolor(colors color)
{
    if (color >= 0 && color <= 7) {
        printf("\E[3%dm", color);
        return 0;
    }
    return -1;
}

int mt_setbgcolor(colors color)
{
    if (color >= 0 && color <= 7) {
        printf("\E[4%dm", color);
        return 0;
    }
    return -1;
}