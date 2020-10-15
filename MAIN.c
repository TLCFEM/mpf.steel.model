#include <stdio.h>
#include "MPF.h"
#include "STEELBRB.h"

int main() {
    double TE = 0., TS = 0., TK = 0., CE = 0., CS = 0., CK = 0.;
    double HIST[7];
    double PROP[10];

    PROP[0] = 2E5;
    PROP[1] = 4E2;
    PROP[2] = 1E-2;
    PROP[3] = 2E1;
    PROP[4] = 185E-1;
    PROP[5] = 15E-2;
    PROP[6] = 1E-2;
    PROP[7] = 7E0;
    PROP[8] = 0E0;
    PROP[9] = 0E0;

    PROP[0] = 2E5;
    PROP[1] = 4E2;
    PROP[2] = 2E3;
    PROP[3] = 66E1;
    PROP[4] = 2E-1;
    PROP[5] = 6E-1;
    PROP[6] = 45E1;
    PROP[7] = 15E-2;
    PROP[8] = 4E-1;

    for(unsigned I = 0; I < 7; ++I)
        HIST[I] = 0.;

    for(unsigned I = 1; I <= 100; ++I) {
        TE += 2E-4;
        steelbrb(&TE, &TS, &TK, &CE, &CS, &CK, HIST, PROP);
        printf("%+.8E\t%+.8E\t%+.8E\n", TE, TS, TK);
        CE = TE;
        CS = TS;
        CK = TK;
    }
    for(unsigned I = 1; I <= 100; ++I) {
        TE -= 2E-4;
        steelbrb(&TE, &TS, &TK, &CE, &CS, &CK, HIST, PROP);
        printf("%+.8E\t%+.8E\t%+.8E\n", TE, TS, TK);
        CE = TE;
        CS = TS;
        CK = TK;
    }

    return 0;
}