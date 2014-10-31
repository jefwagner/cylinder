/*!*******************************************************************
 * manybody.h
 * jefwagner@gmail.com
 *********************************************************************
 */

#ifndef JW_MANYBODY
#define JW_MANYBODY

typedef struct{
	double r, l;
} cyl_params;

typedef struct cyl_ll_struct{
	cyl c;
	struct cyl_ll_struct *next;
} cyl_ll;

typedef struct{
	cyl_params cp;
	vec3 box;
	int n; 
	cyl_ll *a; 
	int nbx, nby, nbz;
	vec3 bucket;
	cyl_ll **heads;
} state;

state* state_malloc( cyl_params cp, vec3 box, int n);
void state_free( state* s);
int cyl_list_add( state *s, int l);
int cyl_list_move( state *s, int l, vec3 pnew);
int state_uniform_initialize( state *s);
int state_print( FILE *file, state *s);

#endif /* JW_MANYBODY */
