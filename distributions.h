/*!*******************************************************************
 * distributions.h
 * jefwagner@gmail.com
 *********************************************************************
 */

#include "vecs.h"

#ifndef JW_DIST
#define JW_DIST

vec2 rand_disk();
vec3 rand_ball();
vec3 rand_rot( vec3 v, double th_max );

#endif