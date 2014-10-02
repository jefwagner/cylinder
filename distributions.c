/*!*******************************************************************
 * distributions.c
 * jefwagner@gmail.com
 *********************************************************************
 */

#include "vecs.h"
#include "math_const.h"

 /*!
 * Random 2-vector in a disk
 *
 * Uniformly generate a random 2-vector in a disk of radius 1.
 */
vec2 rand_disk(){
	vec2 p;
	do{
		p.x = 2.*rand()/RAND_MAX-1.;
		p.y = 2.*rand()/RAND_MAX-1.;
	}while( vec2_mag(p) < 1 );
	return p;
}

/*!
 * Random 3-vector in a ball
 *
 * Uniformly generate a random 3-vector in a disk of radius 1.
 */
vec3 rand_ball(){
	vec3 p;
	do{
		p.x = 2.*rand()/RAND_MAX-1.;
		p.y = 2.*rand()/RAND_MAX-1.;
		p.z = 2.*rand()/RAND_MAX-1.;
	}while( vec3_mag(p) < 1 );
	return p;	
}

/*! 
 * Randomly rotate a 3-vector within an angle `th_max`. 
 * 
 * Randomly generate a new 3-vector the same length as `v`. The new
 * 3-vector is uniformly distributed over a spherical cap centered on
 * `v` with a half- angle of `th_max`.
 */ 
vec3 rand_rot( vec3 v, double th_max ){
	vec3 u, vout;
	/* azimuthal angle */
    double ph = 2.*PI*rand()/RAND_MAX;
    /* polar angle, properly weighted using the inverse of the CDF. */
    double x = 1.*rand()/RAND_MAX;
    double th = acos(1.-(1.-cos(th_max))*x);
    /* generate a vector `u` normal to `v` */
    double r = sqrt( v.x*v.x + v.y*v.y);
    if( r == 0. ){
    	/* if the vector is on the z-axis, make new vector in x-axis */
    	u.z = 0.;
    	u.x = v.z;
    	u.y = 0.;
    }else{
    	/* else, the plane spaned by `v` and `u` contains the z-axis */
    	u.z = r;
    	u.x = -v.z/r*v.x;
    	u.y = -v.z/r*v.y;
    }
    /* rotate the vector `u` around `v` by angle `ph` */
    vec3_rotAAto( &u, v, ph);
    /* rotate the vector `v` around `u` by angle `th` */
    return vec3_rotAA( v, u, th);
}