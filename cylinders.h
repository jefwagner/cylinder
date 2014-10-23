/*!*******************************************************************
 * cylinders.h
 * jefwagner@gmail.com
 *********************************************************************
 */

#ifndef JW_CYLINDERS
#define JW_CYLINDERS

#include "vecs.h"

typedef struct{ 
	vec3 p, d;
	double r;
} cyl;

inline static vec3 cyl_point( cyl c, double l){
	return vec3_add( c.p, vec3_smul( c.d, l));
}

int cyl_box_overlap( cyl c, vec3 box);
double cyl_dist( cyl c0, cyl c1);
int cyl_cyl_overlap( cyl c0, cyl c1);

#endif /* JW_CYLINDERS*/