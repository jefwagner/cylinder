/*!*******************************************************************
 * lennardjones.h
 * jefwagner@gmail.com
 *********************************************************************
 */

#ifndef JW_LENNARDJONES
#define JW_LENNARDJONES

typedef struct{ double u0, r0;} lj_params;
#define TWO_1_6 1.122462048309373

double lj_simple( double r, lj_params p);
#define LJ_RMAX 2.2272467953508484
double lj_truncated( double r, lj_params p);
double lj_shifted( double r, lj_params p);


#endif /* JW_LENNARDJONES */