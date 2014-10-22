/*!*******************************************************************
 * lennardjones.h
 * jefwagner@gmail.com
 *********************************************************************
 */

/*!
 * Lennard-Jones parameters
 *
 * This function holds the parameters for the several Lennard-Jones
 * style functions. They are `r0` the position of the minimum, `u0`
 * the depth of the minimum. In addition we define the number 2^(1/6),
 * which gives the ratio between the position of the minimum, and the
 * position of the zero.
 */
typedef struct{ double u0, r0;} lj_params;
#define TWO_1_6 1.122462048309373

/*!
 * Simple infinite range Lennard-Jones potential
 */
double lj_simple( double r, lj_params p){
	double u = p.r0/r;
	u = u*u*u*u*u*u;
	u = u*u-2.*u;
	u = p.u0*u;
	return u;
}

/*!
 * A truncated finite range Lennard-Jones potential
 *
 * This is a truncated finite range Lennard-Jones potential. Here we
 * assume that outside some multiple of the distance to the minimum
 * the potential goes to zero. We shift the entire potential up so
 * that the potential is continous.
 */
#define LJ_RMAX 2.2272467953508484
#define LJ_DU 0.016316891135999996
/* #define LJ_RMAX 2.0 */
/* #define LJ_DU 0.031005859375 */
/* #define LJ_RMAX 3.0 */
/* #define LJ_DU 0.0027416025485425474 */
/* #define LJ_RMAX 5.0 */
/* #define LJ_DU 0.000127995904 */
/* #define LJ_RMAX 7.5 */
/* #define LJ_DU 0.00001123727981616774 */
/* #define LJ_RMAX 10.0 */
/* #define LJ_DU 0.000001999999 */
double lj_truncated( double r, lj_params p){
	double u;
	if( r > p.r0*LJ_RMAX){
		u = 0.;
	}else{
		u = p.r0/r;
		u = u*u*u*u*u*u;
		u = u*u-2.*u;
		u = p.u0*(u+LJ_DU);
	}
	return u;
}

/*!
 * A shifted finite range Lennard-Jones potential
 * 
 * This is a repulsive only Lennard-Jones potential. For r > r0 the
 * potential is zero, and whole potential is shifted up so that it is
 * continuous and differntiable.
 */
double lj_shifted( double r, lj_params p){
	double u;
	if( r > p.r0){
		u = 0.;
	}else{
		u = p.r0/r;
		u = u*u*u*u*u*u;
		u = u*u - 2.*u;
		u = p.u0*(u+1.);
	}
	return u;
}
