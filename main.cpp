#include "simplepc.h"
#include "myTerm.h"

extern int a[100];
extern int32_t reg;

int32_t main()
{
    int x, y;
    mt_getscreensize(x, y);
    mt_gotoXY(x, y);
    mt_setfgcolor(yellow);
    mt_setbgcolor(red);
    cout << 0;
    cin >> x;
    mt_clrscr();
    
    return 0;
}