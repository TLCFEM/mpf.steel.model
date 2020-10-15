#ifndef MPF_H
#define MPF_H

// TE(IN)       : TRIAL STRAIN (1)
// TS(OUT)      : TRIAL STRESS (1)
// TK(OUT)      : TRIAL STIFFNESS (1)
// CE(IN)       : CURRENT STRAIN (1)
// CS(IN)       : CURRENT STRESS (1)
// CK(IN)       : CURRENT STIFFNESS (1)
// HIST(IN/OUT) : ARRAY OF HISTORY VARIABLES AND CONSTANTS (7)
// PROP(IN)     : ARRAY OF CONSTANTS (10)
void mpfsteel(double* TE, double* TS, double* TK, double* CE, double* CS, double* CK, double* HIST, double* PROP);

#endif