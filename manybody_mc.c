/*!
 * A structure that holds the state.
 *
 * The data structure is a 3-D array of linked list. Each element in
 * the array corresponds to a box in 3-D space, and the linked list
 * hold pointers to the cylinders that reside in that box. The
 * cylinders are storred in the `a` array, the pointers to the next
 * element in the linked list are in the `next` array, and the heads
 * of the linked list for each box are in the `heads` array.
 */
typedef struct{
	int n;
	cyl *a;
	int *next;
	int *heads;
} state;

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
 * System parameters
 */
typedef struct{
	int nbx, nby, nbz;
	double r, d;
	vec3 box;
} system_params;

/*!
 * This structure loops through all cylinders.
 */
void example_loop( state *s, vec3 box){
	int i;
	for( i=0; i<s->n; i++){
		/* work on s->a[i] */
	}
}

void example_cyl_loop( state *s, vec3 box,
					   cyl c, int index){
	int i, j, k, ii;

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