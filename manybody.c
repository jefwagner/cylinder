/*!*******************************************************************
 * manybody.c
 * jefwagner@gmail.com
 *********************************************************************
 */
/*!
 * This file contains the details of a data structure and algorithms
 * that are useful when dealing with a manybody system, where the
 * interaction between the bodies are of finite range. The space (here
 * assumed to be a rectangular prism) is broken up into buckets, where
 * the size of the bucket is such that only object in the same or
 * neighboring buckets will interact. In this case, the data structure
 * and the algorithms will specifically deal with cylinder as defined
 * in the `cylinders.c` file. (In c++ we could do this for 1 general
 * case using generic programing with templates.)
 */

#include <stdlib.h>
#include <math.h>

#include "vecs.h"
#include "cylinders.h"
#include "lennardjones.h"
#include "math_const.h"

/*!
 * A structure for the object parameters.
 * 
 * For cylinders the two parameters are:
 * + `r` the radius of the cylinder
 * + `l` the length of the cylinder
 */
typedef struct{
	double r, l;
} cyl_params;

/*!
 * A linked list structure
 */
typedef struct cyl_ll_struct{
	cyl c;
	struct cyl_ll_struct *next;
} cyl_ll;

/*!
 * A structure that holds the state.
 *
 * The data structure that all the neccesary information for the
 * state. It contains:
 * + `cp` object parameters
 * + `box` full enclosing box size
 * + `n` number of objects
 * + `a` array of linked_list objects
 * + `nbx`, `nby`, `nbz` The number of buckets in x, y, and z axis
 * + `heads` array of pointers to the heads of the list for each bucket
 */
typedef struct{
	cyl_params cp;
	vec3 box;
	int n; 
	cyl_ll *a; 
	int nbx, nby, nbz;
	vec3 bucket;
	cyl_ll **heads;
} state;

/*!
 * Constructor for the state.
 *
 * This constructor take the parameters that define the state:
 * + `cp` the cylinder radius and length
 * + `box` the size of the enclosing box
 * + `n` the number of cylinders
 * 
 * Using those parameters it defines the size and number of buckets,
 * and allocates the memory for the three neccessary arrays, and upon
 * successful completetion returns a pointer to the state. If at any
 * point the memory allocation faile, it frees all memory and
 * returns `NULL`.
 */
state* state_malloc( cyl_params cp, vec3 box, int n){
	double min_bucket_size;
	int i, nb;

	state *s = (state *) malloc( sizeof(state));
	if( s == NULL ){
		return NULL;
	}
	s->cp = cp;
	s->box = box;
	s->n = n;

	min_bucket_size = 2.*(LJ_RMAX*cp.r+cp.l);
	s->nbx = (int) (box.x/min_bucket_size);
	s->nby = (int) (box.y/min_bucket_size);
	s->nbz = (int) (box.z/min_bucket_size);
	s->bucket.x = box.x/s->nbx;
	s->bucket.y = box.y/s->nby;
	s->bucket.z = box.z/s->nbz;

	s->a = (cyl_ll *) malloc( n*sizeof(cyl_ll));
	if( s->a == NULL ){
		free( s);
		return NULL;
	}
	for( i=0; i<n; i++){
		s->a[i].next = NULL;
	}
	nb = s->nbx * s->nby * s->nbz;
	s->heads = (cyl_ll **) malloc( nb*sizeof(cyl_ll *));
	if( s->heads == NULL ){
		free( s->a);
		free( s);
		return NULL;
	}
	for( i=0; i<nb; i++){
		s->heads[i] = NULL;
	}
	return s;
}

/*!
 * Destructor for the state.
 */
void state_free( state* s){
	free( s->heads);
	free( s->a);
	free( s);
}

/*!
 * Add a cylinder the appropriate bucket.
 */
int cyl_list_add( state *s, int l){
	vec3 p = s->a[l].c.p;
	int i = (int) p.x/s->bucket.x;
	int j = (int) p.y/s->bucket.y;
	int k = (int) p.z/s->bucket.z;
	int m = (s->nbx)*( (s->nby)*k + j) + i;
	s->a[l].next = s->heads[m];
	s->heads[m] = &(s->a[l]);
	return 1;
}

/*!
 * Move a cylinder to a new bucket.
 *
 * Move a cylinder to a new bucket based on a new point `pnew`.
 */
int cyl_list_move( state *s, int l, vec3 pnew){
	int retval;
	cyl_ll *cur;
	vec3 p = s->a[l].c.p;
	int i = (int) p.x/s->bucket.x;
	int j = (int) p.y/s->bucket.y;
	int k = (int) p.z/s->bucket.z;
	int m = (s->nbx)*( (s->nby)*k + j) + i;
	s->a[l].c.p = pnew;
	int ii = (int) pnew.x/s->bucket.x;
	int jj = (int) pnew.y/s->bucket.y;
	int kk = (int) pnew.z/s->bucket.z;
	int mm = (s->nbx)*( (s->nby)*kk + jj) + ii;
	if( m == mm ){
		return 1;
	}
	/* remove the cyl from list `m` */
	cur = s->heads[m];
	if( cur == &(s->a[l])){
		s->heads[m] = cur->next;
		retval = 1;
	}else{
		while( cur->next != &(s->a[l]) && cur->next != NULL ){
			cur = cur->next;
		}
		if( cur->next != NULL ){
			cur->next = cur->next->next;
			retval = 1;
		}else{
			retval = 0;
		}
	}
	/* add the cyl to the list `mm` */
	s->a[l].next = s->heads[mm];
	s->heads[mm] = &(s->a[l]);
	return retval;
}

/*!
 * Uniform initialization.
 *
 * This function initialized the state with uniformly spaced
 * cylinders. Since the bounding box for a cylinder is a box with 1
 * long side and two short sides (which are refered two as `height`
 * and `width` respectively) the first step finds out which direction
 * (x, y, or z) best fits the cylinders long-wise. After that, we find
 * out how many to cylinders to place in the x, y, and z direction by
 * going through all possible permutations and minimizing a weighted
 * sum that compares the relative difference in total number, and
 * rations x:y, x:z, and y:z. Finally it fills in the state with the
 * cylinders.
 */
int state_uniform_initialize( state *s){
	vec3 bbox, d;
	double width, height, rem_min;
	int nx_max, ny_max, nz_max;

	int nx, ny, nz;
	double rat_xy, rat_xz, rat_yz, tot_dif_min;

	int i, j, k, l;
	double num_dif, rat, rat_dif_xy, rat_dif, tot_dif;

	width = 2.*(s->cp.r);
	height = 2.*(s->cp.r) + s->cp.l;
	bbox.x = fmod( s->box.x, height);
	bbox.y = fmod( s->box.y, height);
	bbox.z = fmod( s->box.z, height);
	rem_min = min( bbox.x, bbox.y);
	rem_min = min( rem_min, bbox.z);

	if( bbox.x == rem_min ){
		nx_max = (int) (s->box.x/height);
		ny_max = (int) (s->box.y/width);
		nz_max = (int) (s->box.z/width);
		d.x = (s->cp.l); d.y = 0.; d.z = 0.;
	}else if( bbox.y == rem_min ){
		nx_max = (int) (s->box.x/width);
		ny_max = (int) (s->box.y/height);
		nz_max = (int) (s->box.z/width);
		d.x = 0.; d.y = (s->cp.l); d.z = 0.;
	}else{
		nx_max = (int) (s->box.x/width);
		ny_max = (int) (s->box.y/width);
		nz_max = (int) (s->box.z/height);
		d.x = 0.; d.y = 0.; d.z = (s->cp.l);
	}

	if( nx_max*ny_max*nz_max < s->n ){
		return 0;
	}

	tot_dif_min = 10000.;
	nx = nx_max; ny = ny_max; nz = nz_max;
	rat_xy = ((double) nx_max)/ny_max;
	rat_xy = rat_xy>1.?rat_xy:(-1./rat_xy);
	rat_xz = ((double) nx_max)/nz_max;
	rat_xz = rat_xz>1.?rat_xz:(-1./rat_xz);
	rat_yz = ((double) ny_max)/ny_max;
	rat_yz = rat_yz>1.?rat_yz:(-1./rat_yz);

	for( i=nx_max; i>0; i--){
		for( j=ny_max; j>0; j--){
			rat = ((double) i)/j;
			rat = rat_xy>1.?rat:(-1./rat);
			rat_dif_xy = fabs((rat-rat_xy)/rat_xy);
			for( k=nz_max; k>0; k--){
				if( i*j*k < s->n ){ break; }
				num_dif = ((double) (i*j*k - s->n))/(s->n);
				rat = ((double) i)/k;
				rat = rat_xz>1.?rat:(-1./rat);
				rat_dif = rat_dif_xy + fabs((rat-rat_xz)/rat_xz);
				rat = ((double) j)/k;
				rat = rat_yz>1.?rat:(-1./rat);
				rat_dif += fabs((rat-rat_yz)/rat_yz);
				tot_dif = 0.75*num_dif + 0.25*rat_dif;
				if( tot_dif < tot_dif_min ){
					tot_dif = tot_dif_min;
					nx = i;
					ny = j;
					nz = k;
				}
			}
		}
	}

	bbox.x = s->box.x/nx;
	bbox.y = s->box.y/ny;
	bbox.z = s->box.z/nz;

	l = 0;
	for( i=0; i<nx; i++){
		for( j=0; j<ny; j++){
			for( k=0; k<nz; k++){
				if( l == s->n ){ break; }
				s->a[l].c.p.x = (i+0.5)*bbox.x;
				s->a[l].c.p.y = (j+0.5)*bbox.y;
				s->a[l].c.p.z = (k+0.5)*bbox.z;
				vec3_subto( &(s->a[l].c.p), vec3_smul(d, 0.5));
				s->a[l].c.d = d;
				s->a[l].c.r = s->cp.r;
				cyl_list_add( s, l);
				l++;
			}
			if( l == s->n ){ break; }
		}
		if( l == s->n ){ break; }
	}

	return 1;
}
