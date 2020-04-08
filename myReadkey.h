#ifndef _MYREADKEY_H

#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

enum keys {
    l,
    s,
    r,
    t,
    i,
    q,
    c,
    v,
    F5,
    F6,
    arrU,
    arrD,
    arrL,
    arrR
};

int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(bool regime, bool vtime, bool vmin, bool echo, bool
sigint);
int rk_readkey (keys &k); 

#endif