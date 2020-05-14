#include "myReadkey.h"

struct termios savetty, tty;

int rk_mytermsave()
{
    tcgetattr(0, &savetty);

    return 0;
}

int rk_mytermrestore()
{
    tcsetattr(0, TCSAFLUSH, &savetty);

    return 0;
}

int rk_mytermregime(bool regime, bool vtime, bool vmin, bool echo, bool sigint)
{
    tcgetattr(0, &tty);
    if (!echo) {
        tty.c_lflag &= ~(ECHO);
    } else {
        tty.c_lflag &= ECHO;
    }
    if (!sigint) {
        tty.c_lflag &= ~(ISIG);
    }

    if (!regime) {
        tty.c_lflag &= ~(ICANON);
    } else {
        tty.c_lflag &= ICANON;
    }

    if (vmin) {
        tty.c_cc[VMIN] = 1;
    }

    if (vtime) {
        tty.c_cc[VTIME] = 1;
    }

    tcsetattr(0, TCSAFLUSH, &tty);

    return 0;
}

int rk_readkey(keys& k)
{
    int ans = 0;

    rk_mytermsave();

    rk_mytermregime(0, 0, 1, 0, 0);

    char c;

    read(0, &c, 1);

    if ((int)c == 27) {
        char ch[4];
        stringstream ss;
        string s;
        map<string, keys> mp;

        mp["[A"] = keys::arrU;
        mp["[B"] = keys::arrD;
        mp["[D"] = keys::arrL;
        mp["[C"] = keys::arrR;
        mp["[15~"] = keys::F5;
        mp["[17~"] = keys::F6;

        read(0, ch, 4);

        cout << ch;

        ss << ch;
        ss >> s;

        if (mp.count(s)) {
            k = mp[s];
        }

        else {
            ans = -1;
        }
    } else {
        map<char, keys> mp;

        mp['l'] = keys::l;
        mp['s'] = keys::s;
        mp['r'] = keys::r;
        mp['t'] = keys::t;
        mp['i'] = keys::i;
        mp['q'] = keys::q;
        mp['c'] = keys::c;
        mp['v'] = keys::v;

        if (mp.count(c)) {
            k = mp[c];
        } else {
            ans = -1;
        }
    }

    rk_mytermrestore();

    return ans;
}