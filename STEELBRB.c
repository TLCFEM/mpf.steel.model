#include "STEELBRB.h"
#include <math.h>

// TE(IN)       : TRIAL STRAIN (1)
// TS(OUT)      : TRIAL STRESS (1)
// TK(OUT)      : TRIAL STIFFNESS (1)
// CE(IN)       : CURRENT STRAIN (1)
// CS(IN)       : CURRENT STRESS (1)
// CK(IN)       : CURRENT STIFFNESS (1)
// HIST(IN/OUT) : ARRAY OF HISTORY VARIABLES AND CONSTANTS (2)
// PROP(IN)     : ARRAY OF CONSTANTS (9)
int steelbrb(double* TE, double* TS, double* TK, double* CE, double* CS, double* CK, double* HIST, double* PROP) {
    const unsigned max_iteration = 20;
    const double tolerance = 1E-14;

    const double s_modulus = -PROP[0] - PROP[2];
    const double c_const = (PROP[6] - PROP[1]) / PROP[7];
    const double t_const = (PROP[3] - PROP[1]) / PROP[4];

    const double incre_strain = *TE - *CE;

    if(fabs(incre_strain) < 1E-14) {
        *TS = *CS;
        *TK = *CK;
        return 0;
    }

    *TS = *CS + (*TK = PROP[0]) * incre_strain;

    const double current_accumulated_strain = HIST[0]; // u
    const double current_plastic_strain = HIST[1];     // \delta_1

    if((*TS - PROP[2] * HIST[1]) / incre_strain < 0.) return 0;

    const double tension_flag = incre_strain >= 0.;
    const double exponent = tension_flag ? PROP[5] : PROP[8];

    double incre = .5 * incre_strain, incre_plastic_strain = 0.;
    unsigned counter = 0;
    while(1) {
        if(max_iteration == ++counter)
            return 1;

        incre_plastic_strain += incre;

        HIST[1] = current_plastic_strain + incre_plastic_strain;
        *TS = PROP[0] * (*TE - HIST[1]);
        HIST[0] = current_accumulated_strain + fabs(incre_plastic_strain);

        double sigma_y, d_sigma_y;
        if(tension_flag) {
            d_sigma_y = t_const * exp(-HIST[0] / PROP[4]);
            sigma_y = PROP[3] - d_sigma_y * PROP[4];
        } else {
            d_sigma_y = c_const * exp(-HIST[0] / PROP[7]);
            sigma_y = PROP[6] - d_sigma_y * PROP[7];
        }

        const double numerator = *TS - PROP[2] * HIST[1];
        const double fraction = numerator / sigma_y;
        const double pow_term = pow(fabs(fraction), exponent);
        double residual = -incre_strain * pow_term;
        const double jacobian = 1. + exponent / numerator * residual * (s_modulus - fraction * (incre_plastic_strain >= 0. ? d_sigma_y : -d_sigma_y));
        residual += incre_plastic_strain;

        if(fabs(incre = -residual / jacobian) <= tolerance) {
            *TK *= 1. - (pow_term + incre_strain * PROP[0] * exponent * pow_term / numerator) / jacobian;

            return 0;
        }
    }
}