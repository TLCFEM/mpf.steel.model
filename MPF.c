#include "MPF.h"
#include <float.h>
#include <math.h>

void mpfsteel(double* TE, double* TS, double* TK, double* CE, double* CS, double* CK, double* HIST, double* PROP) {
    const double IE = *TE - *CE;
    if(fabs(IE) <= 1E-14) {
        *TS = *CS;
        *TK = *CK;
        return;
    }

    double SS = 0.;

    if(1. == PROP[8]) {
        SS = fmax(0., PROP[6] * (HIST[5] * PROP[0] - PROP[1] * PROP[7]));
        HIST[5] = fmax(fabs(*TE), HIST[5]);
    }

    const double TLS = IE > 0. ? 1. : -1.;

    if(TLS != HIST[6]) {
        if(0. != HIST[6]) {
            HIST[0] = *CS;
            HIST[1] = *CE;
            HIST[4] = HIST[3];
            HIST[3] = PROP[1] * PROP[2] - PROP[1] - SS;
            if(0. < TLS)
                HIST[3] = -HIST[3];
            HIST[3] = (HIST[3] + PROP[0] * *CE - *CS) / (PROP[0] - PROP[0] * PROP[2]);
            HIST[2] = PROP[0] * (HIST[3] - HIST[1]) + HIST[0];
        } else if(0. < TLS) {
            HIST[2] = PROP[1];
            HIST[3] = PROP[1] / PROP[0];
        } else {
            HIST[2] = -PROP[1];
            HIST[3] = -PROP[1] / PROP[0];
        }
        HIST[6] = TLS;
    }

    double TR = PROP[3];
    if(0. == PROP[9]) {
        const double XI = fabs(HIST[1] - HIST[4]) / PROP[1] * PROP[0];
        TR -= PROP[4] * XI / (PROP[5] + XI);
    }

    const double TMPA = HIST[3] - HIST[1];
    const double TMPD = HIST[2] - HIST[0];
    const double NE = fmax(DBL_EPSILON, (*TE - HIST[1]) / TMPA);
    const double TMPB = 1. + pow(NE, TR);
    const double TMPC = (1. - PROP[2]) * pow(TMPB, -1. / TR);
    const double NS = (PROP[2] + TMPC) * NE;

    *TS = NS * TMPD + HIST[0];
    *TK = TMPD / TMPA * (PROP[2] + TMPC / TMPB);
}