/*!*******************************************************************
 * cylinders.c
 * jefwagner@gmail.com
 *********************************************************************
 */

#include "vecs.h"
#include "distributions.h"
#include "math_const.h"

/*!
 * Cylinder object
 *
 * The member data is a 3-vector point that specifices the position of
 * one of the endpoints, a 3-vector length, and a radius. The second
 * endpoint is obtained by adding the length to the first endpoint.
 */
typedef struct{ 
	vec3 p, d;
	double r;
} cyl;

/*!
 * A point along a cylinder.
 *
 * Given a cylinder object `c`, and a proportianl length along the
 * cyinder `l` (such that 0<=l<=1), find the point along the axis.
 */
static vec3 cyl_point( cyl c, double l){
	return vec3_add( c.p, vec3_smul( c.d, l));
}

int cyl_box_overlap( cyl c, vec3 b0, vec3 b1){
	vec3 pend, pmin, pmax;

	pend = vec3_add( c.p, c.d);

	pmin.x = min( pend.x, c.p.x);
	pmin.y = min( pend.y, c.p.y);
	pmin.z = min( pend.z, c.p.z);
	pmax.x = max( pend.x, c.p.x);
	pmax.y = max( pend.y, c.p.y);
	pmax.z = max( pend.z, c.p.z);

	out = pmin.x > b0.x+c.r;
	out *= pmin.y > b0.y+c.r;
	out *= pmin.z > b0.z+c.r;
	out *= pmax.x < b0.x+c.r;
	out *= pmax.y < b0.y+c.r;
	out *= pmax.z < b0.z+c.r;
	return out;
}

/*!
 * Minimum distance between two cylinders
 *
 * This function finds the minimum distance between two cylinders
 * given as `cyl` structs. If the point of closest contact is not
 * along the length of the two cylinders, then the closer endpoint is
 * used to calculate the distance between the cylinders.
 *
 * This is accomplished by treating the cylinders mathematically as
 * two lines (\[\vec{L}(l)=\vec{p}+\vec{d}l\]), and finding the value
 * of \[l\] where the lines are closest. If the value of \[l\] is
 * between 0 and 1, then the point of closest approach is along the
 * cylinder, otherwise the point of closest approach should be one of
 * the endpoints.
 */
double cyl_dist( cyl c0, cyl c1){
	vec3 p0, p1;
	vec3 pm = vec3_sub( c0.p, c1.p);
	double a = vec3_dot( c0.d, c0.d);
	double b = vec3_dot( c0.d, c1.d);
	double d = vec3_dot( c1.d, c1.d);
	double t0 = -vec3_dot( pm, c0.d);
	double t1 = vec3_dot( pm, c1.d);
	double det = a*c - b*b;
	double l0 = -d*t0 + b*t1;
	double l1 = -b*t0 + a*t1;
	if( l0 < 0. ){
		p0 = c0.p;
	}else if( l0 <= 1. ){
		p0 = vec3_add( c0.p, vec3_smul( c0.d, l0));
	}else{
		p0 = vec3_add( c0.p, c0.d);
	}
	if( l1 < 0. ){
		p1 = c1.p;
	}else if( l1 <= 1. ){
		p1 = vec3_add( c1.p, vec3_smul( c1.d, l1));
	}else{
		p1 = vec3_add( c0.p, c0.d);
	}
	return vec3_dist( p0, p1); 
}

int cyl_cyl_overlap( cyl c0, cyl c1){
	return( cyl_dist( c0, c1) < c0.r+c1.r );	
}

/*!
 * A structure that holds everything
 */
typedef struct{
	int n;
	cyl *a;
	int *next;
	int *heads;
} state;

/*!
 * This structure loops through all cylinders by looping through
 * all the boxes, and looping through each box.
 */
 void example_loop( state *s){
 	int i, j, k, ii
	for( i=0; i<NBX; i++){
		for( j=0; j<NBY; j++){
			for( k=0; k<NBZ; k++){
				ii = s->heads[NBZ*NBY*i+NBY*j+k];
				while( ii > 0 ){
					/* do work with s->a[ii] */
					ii = s->next[ii];
				}
			}
		}
	}
}

/*!
 * Constructor for the state.
 */
state* state_malloc( int n, int nb){
	state *s = (state *) malloc( sizeof(state));
	if( s == NULL ){
		return NULL;
	}
	s->n = n;
	s->a = (cyl *) malloc( n*sizeof(cyl));
	if( s->a == NULL ){
		free( s);
		return NULL;
	}
	s->next = (int *) malloc( n*sizeof(int));
	if( s->next == NULL){
		free( s->a);
		free( s);
		return NULL;
	}
	s->heads = (int *) malloc( nb*sizeof(int));
	if( s->heads == NULL ){
		free( s->next);
		free( s->a);
		free( s);
		return NULL;
	}
	return s;
}

/*!
 * Destructor for the state.
 */
void state_free( state* s){
	free( s->heads);
	free( s->next);
	free( s->a);
	free( s);
}

/*!
 * 
 */
int valid_move( const state *s, cyl c){

}

void state_initialize( state *s){
	int i;
	cyl c;
	for( i=0; i<; i++){
		s->heads[i] = NULL;
	}
	for( i=0; i<s->n i++){
		do{
			c.p.x = NBX*BW*rand()/RAND_MAX;
			c.p.y = NBY*BW*rand()/RAND_MAX;
			c.p.z = NBZ*BW*rand()/RAND_MAX;
			c.d = vec3_norm(rand_ball());
		}while( valid_move( s, c));
		s->a[i] = c;
		s->a[i].d = d;
	}
}

int main( int argc, char **argv){

	return 0;
}