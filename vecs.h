/*!*******************************************************************
 * vecs.c
 * jefwagner@gmail.com
 *********************************************************************
 */

#include <math.h>

#ifndef JW_VEC2
#define JW_VEC2
/*!
 * 2-Vector struct and functions
 * ----------------------------
 * vec2_add : addition
 * vec2_addto : in place addition
 * vec2_sub : subtraction
 * vec2_subto : in place subtraction
 * vec2_neg : negation
 * vec2_negto : in place negation
 * vec2_smul : scalar multiplication
 * vec2_smulto : in place scalar multiplication
 * vec2_dot : inner product
 * vec2_cross : 2-dim cross product
 * vec2_mag : magnitude
 * vec2_unit : noralized vector
 * vec2_unitto : in place normalized vector
 * vec2_rot : rotation
 * vec2_rotto : in place rotation
 * vec2_dist : distance between two 2-vectors
 */
typedef struct{ double x, y; } vec2;

static inline vec2 vec2_add( vec2 p0, vec2 p1){
	vec2 pout;
	pout.x = p0.x + p1.x;
	pout.y = p0.y + p1.y;
	return pout;
}

static inline void vec2_addto( vec2 *p0, vec2 p1){
	p0->x += p1.x;
	p0->y += p1.y;
}

static inline vec2 vec2_sub( vec2 p0, vec2 p1){
	vec2 pout;
	pout.x = p0.x - p1.x;
	pout.y = p0.y - p1.y;
	return pout;
}

static inline void vec2_subto( vec2 *p0, vec2 p1){
	p0->x -= p1.x;
	p0->y -= p1.y;
}

static inline vec2 vec2_neg( vec2 p){
	vec2 pout;
	pout.x = -p.x;
	pout.y = -p.y;
	return pout;
}

static inline void vec2_negto( vec2 *p){
	p->x = -p->x;
	p->y = -p->y;
}

static inline vec2 vec2_smul( vec2 p, double a){
	vec2 pout;
	pout.x = a*p.x;
	pout.y = a*p.y;
	return pout;
}

static inline void vec2_smulto( vec2 *p, double a){
	p->x *= a;
	p->y *= a;
}

static inline double vec2_dot( vec2 p0, vec2 p1){
	return p0.x*p1.x + p0.y*p1.y;
}

static inline double vec2_cross( vec2 p0, vec2 p1){
	return p0.x*p1.y - p0.y*p1.x;
}

static inline double vec2_mag( vec2 p){
	return sqrt( p.x*p.x + p.y*p.y);
}

static inline vec2 vec2_unit( vec2 p){
	double mag = vec2_mag( p);
	return vec2_smul( p, 1./mag);
}

static inline void vec2_unitto( vec2 *p){
	double mag = vec2_mag( *p);
	vec2_smulto( p, 1./mag);
}

static inline vec2 vec2_rot( vec2 v, double th){
	vec2 vout;
	double c = cos(th);
	double s = sin(th);
	vout.x = v.x*c - v.y*s;
	vout.y = v.y*c + v.x*s;
	return vout;
}

static inline void vec2_rotto( vec2 *v, double th){
	double x;
	double c = cos(th);
	double s = sin(th);
	x = v->x*c - v->y*s;
	v->y = v->y*c + v->x*s;
	v->x = x;
}

static inline double vec2_dist( vec2 p0, vec2 p1){
	return vec2_mag( vec2_sub( p0, p1));
}

#endif

#ifndef JW_VEC3
#define JW_VEC3

/*!
 * 3-Vector struct and functions
 * ----------------------------
 * vec3_add : addition
 * vec3_addto : in place addition
 * vec3_sub : subtraction
 * vec3_subto : in place subtraction
 * vec3_neg : negation
 * vec3_negto : in place negation
 * vec3_smul : scalar multiplication
 * vec3_smulto : in place scalar multiplication
 * vec3_dot : inner product
 * vec3_cross : 3-dim cross product
 * vec3_crossto : in place cross product
 * vec3_mag : magnitude
 * vec3_unit : noralized vector
 * vec3_unitto : in place normalized vector
 * vec3_rotAA : axis angle rotation
 * vec3_rotAAto : in place axis angle rotation
 * vec3_dist : distance between two 3-vectors
 */
typedef struct{ double x, y, z; } vec3;

static inline vec3 vec3_add( vec3 p0, vec3 p1){
	vec3 pout;
	pout.x = p0.x + p1.x;
	pout.y = p0.y + p1.y;
	pout.z = p0.z + p1.z;
	return pout;
}

static inline void vec3_addto( vec3 *p0, vec3 p1){
	p0->x += p1.x;
	p0->y += p1.y;
	p0->z += p1.z;
}

static inline vec3 vec3_sub( vec3 p0, vec3 p1){
	vec3 pout;
	pout.x = p0.x - p1.x;
	pout.y = p0.y - p1.y;
	pout.z = p0.z - p1.z;
	return pout;
}

static inline void vec3_subto( vec3 *p0, vec3 p1){
	p0->x -= p1.x;
	p0->y -= p1.y;
	p0->z -= p1.z;
}

static inline vec3 vec3_neg( vec3 p){
	vec3 pout;
	pout.x = -p.x;
	pout.y = -p.y;
	pout.z = -p.z;
	return pout;
}

static inline void vec3_negto( vec3 *p){
	p->x = -p->x;
	p->y = -p->y;
	p->z = -p->z;
}

static inline vec3 vec3_smul( vec3 p, double a){
	vec3 pout;
	pout.x = a*p.x;
	pout.y = a*p.y;
	pout.z = a*p.z;
	return pout;
}

static inline void vec3_smulto( vec3 *p, double a){
	p->x *= a;
	p->y *= a;
	p->z *= a;
}

static inline double vec3_dot( vec3 p0, vec3 p1){
	return p0.x*p1.x + p0.y*p1.y + p0.z*p1.z;
}

static inline vec3 vec3_cross( vec3 p0, vec3 p1){
	vec3 pout;
	pout.x = p0.y*p1.z - p0.z*p1.y;
	pout.y = p0.z*p1.x - p0.x*p1.z;
	pout.z = p0.x*p1.y - p0.y*p1.x;
	return pout;
}

static inline void vec3_crossto( vec3 *p0, vec3 p1){
	double x, y;
	x = p0->y*p1.z - p0->z*p1.y;
	y = p0->z*p1.x - p0->x*p1.z;
	p0->z = p0->x*p1.y - p0->y*p1.x;
	p0->x = x;
	p0->y = y;
}

static inline double vec3_mag( vec3 p){
	return sqrt( p.x*p.x + p.y*p.y + p.z*p.z);
}

static inline vec3 vec3_unit( vec3 p){
	double mag = vec3_mag( p);
	return vec3_smul( p, 1./mag);
}

static inline void vec3_unitto( vec3 *p){
	double mag = vec3_mag( *p);
	vec3_smulto( p, 1./mag);
}

static inline vec3 vec3_rotAA( vec3 v, vec3 u, double th ){
	vec3 vout;
	double c = cos(th);
	double s = sin(th);
	vec3_unitto( &u);
	vout.x = (c + u.x*u.x*(1.-c))*v.x;
	vout.x += (u.x*u.y*(1.-c)-u.z*s)*v.y;
	vout.x += (u.x*u.z*(1.-c)+u.y*s)*v.z;
	vout.y = (u.y*u.x*(1.-c)+u.z*s)*v.x;
	vout.y += (c + u.y*u.y*(1.-c))*v.y;
	vout.y += (u.y*u.z*(1.-c)-u.x*s)*v.z;
	vout.z = (u.z*u.x*(1-c)-u.y*s)*v.x;
	vout.z += (u.z*u.y*(1-c)+u.x*s)*v.y;
	vout.z += (c + u.z*u.z*(1-c))*v.z;
	return vout;
}

static inline void vec3_rotAAto( vec3 *v, vec3 u, double th ){
	double x, y;
	double c = cos(th);
	double s = sin(th);
	vec3_unitto( &u);
	x = (c + u.x*u.x*(1.-c))*v->x;
	x += (u.x*u.y*(1.-c)-u.z*s)*v->y;
	x += (u.x*u.z*(1.-c)+u.y*s)*v->z;
	y = (u.y*u.x*(1.-c)+u.z*s)*v->x;
	y += (c + u.y*u.y*(1.-c))*v->y;
	y += (u.y*u.z*(1.-c)-u.x*s)*v->z;
	v->z = (u.z*u.x*(1-c)-u.y*s)*v->x;
	v->z += (u.z*u.y*(1-c)+u.x*s)*v->y;
	v->z += (c + u.z*u.z*(1-c))*v->z;
	v->x = x;
	v->y = y;
}

static inline double vec3_dist( vec3 p0, vec3 p1){
	return vec3_mag( vec3_sub( p0, p1));
}

#endif
