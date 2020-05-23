#include "mySignal.h"
#include "control.h"
#include "draw.h"
#include "myReadkey.h"
#include "simplepc.h"

extern int kurx, kury, insc, accum;
extern bool timer;

bool press = 0;

void sing(int sn)
{
    if (sn == SIGALRM) {
        int t;
        sc_regGet(T, t);

        if (!t) {
            struct itimerval nv, ov;

            nv.it_interval.tv_sec = 1;
            nv.it_interval.tv_usec = 500;
            nv.it_value.tv_sec = 1;
            nv.it_value.tv_usec = 500;

            ov.it_interval.tv_sec = 0;
            ov.it_interval.tv_usec = 0;
            ov.it_value.tv_sec = 0;
            ov.it_value.tv_usec = 0;

            rk_mytermrestore();
            setitimer(ITIMER_REAL, &ov, NULL);
            if (CU() == -1) {
                timer = 0;
                signal(SIGALRM, SIG_IGN);
                ov.it_interval.tv_sec = 0;
                ov.it_interval.tv_usec = 0;
                ov.it_value.tv_sec = 0;
                ov.it_value.tv_usec = 0;

                setitimer(ITIMER_REAL, &ov, NULL);
            } else {
                setitimer(ITIMER_REAL, &nv, NULL);
            }
            rk_mytermregime(0, 0, 1, 0, 0);
            draw();
        }
    } else {
        rk_mytermrestore();
        signal(SIGALRM, SIG_IGN);
        struct itimerval ov;
        ov.it_interval.tv_sec = 0;
        ov.it_interval.tv_usec = 0;
        ov.it_value.tv_sec = 0;
        ov.it_value.tv_usec = 0;

        setitimer(ITIMER_REAL, &ov, NULL);
        timer = 0;
        kurx = kury = 0;
        sc_regInit();
        sc_memoryInit();
        insc = 0;
        accum = 0;
    }
}