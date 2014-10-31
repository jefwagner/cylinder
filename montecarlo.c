/*!*******************************************************************
 * montecarlo.c
 * jefwagner@gmail.com
 *********************************************************************
 */
/*!
 * 
 */

#include "math_const.h"
#include "vecs.h"
#include "distributions.h"
#include "lennardjones.h"
#include "cylinders.h"
#include "manybody.h"

/*!
 * Move a cylinder.
 *
 * Move a cylinder up to half it's length, and rotate it up to a Pi/6
 * rotation.
 */
cyl move_cyl( cyl c_old){
	cyl c_new;

	c_new.p = vec3_smul( rand_ball(), 0.5*vec3_mag(c_old.d));
	c_new.p = vec3_add( c_old.p, c_new.p);
	c_new.d = rand_rot( c_old.d, PI_6);
	c_new.r = c_old.r;
	return c_new;
}

/*!
 * Energy between two cylinders
 *
 * This calculates a lj potential between two cylinders: it has an
 * attractive lj potential between the centers, and a repulsive lj
 * potential between the points of closest approach.
 */
double u_cc( cyl c1, cyl c2){
	double u0;
	lj_params p_attractive = { 1., 2.*c1.r};
	lj_params p_repulsive = { 1., 2.*c1.r/TWO_1_6};

	double sep = vec3_dist( cyl_point( c1, 0.5), cyl_point( c2, 0.5));

	u0 = lj_truncated( sep, p_attractive);
	u0 += lj_shifted( cyl_dist( c1, c2), p_repulsive);

	return u0;
}

/*!
 * Total energy involving indexed cylinder. 
 */
double u_i( state *s, int index, cyl c){
	int i, j, k, m;
	int i_min, i_max, j_min, j_max, k_min, k_max;
	vec3 p;
	cyl_ll *old, *cur;
	double u;

	p = c.p;
	i = (int) p.x/s->bucket.x;
	i_min = (i==0)?i:i-1;
	i_max = (i==s->nbx-1)?i:i+1;
	j = (int) p.y/s->bucket.y;
	j_min = (j==0)?j:j-1;
	j_max = (j==s->nby-1)?j:j+1;
	k = (int) p.z/s->bucket.z;
	k_min = (k==0)?k:k-1;
	k_max = (k==s->nbz-1)?k:k+1;
	m = (s->nbx)*( (s->nby)*k + j) + i;

	old = &(s->a[index]);
	u = 0.;
	for( i=i_min; i<=i_max; i++){
		for( j=j_min; j<=j_max; j++){
			for( k=k_min; k<=k_max; k++){
				m = (s->nbx)*( (s->nby)*k + j) + i;
				for( cur = s->heads[m]; cur != NULL; cur = cur->next){
					if( cur != old ){
						u += u_cc( cur->c, c);
					}
				}
			}
		}
	}

	return u;
}

/*!
 * The difference in energy.
 *
 * The difference in energy in moving cylidner index with the index i,
 * to the new position c_new.
 */
double du( state *s, int i, cyl c_new){
	return( u_i( s, i, c_new) - u_i( s, i, s->a[i].c) );
}


