/*!*******************************************************************
 * lennardjones.h
 * jefwagner@gmail.com
 *********************************************************************
 */

#ifndef JW_LENNARDJONES
#define JW_LENNARDJONES

typedef struct{ double u0, r0;} lj_params;

double lj_simple( double r, lj_params p);
double lj_truncated( double r, lj_params p);
double lj_shifted( double r, lj_params p);


#endif