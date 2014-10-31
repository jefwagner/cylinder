#include <stdio.h>

#include "manybody.c"

int cyl_print_ln( FILE *file, cyl c){
	return fprintf( file, "%1.3e %1.3e %1.3e %1.3e %1.3e %1.3e %1.3e \n",
		            c.p.x, c.p.y, c.p.z, c.d.x, c.d.y, c.d.z, c.r);
}

void state_test(){
	FILE *file;
	int result = 0;
	cyl_params cp = {0.2, 1};
	vec3 box = {20., 20.5, 11.};
	vec3 d = {0., 0., 1.};
	vec3 p = {0.5, 0.5, 0.5};

	fprintf( stdout, "Testing state_malloc: ");
	state *s = state_malloc( cp, box, 500);
	result = (s != NULL);
	if( !result ){ 
		fprintf( stdout, "failed!\n");
		return; 
	}
	result = result && ( s->nbx == 6 && s->nby == 7 && s->nbz == 3 );
	result = result && ( s->bucket.x - 3.333333333333333 < 1.0e-7 );
	result = result && ( s->bucket.z - 3.6666666666666665 < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing cyl_list_add: ");
	s->a[0].c.p = p;
	s->a[0].c.d = d;
	s->a[1].c.p = p;
	s->a[1].c.d = d;
	s->a[2].c.p = p;
	s->a[2].c.d = d;
	s->a[3].c.p = p;
	s->a[3].c.d = d;
	p.x = 4.; p.y = 0.; p.z = 0.;
	s->a[4].c.p = p;
	s->a[4].c.d = d;
	result = cyl_list_add( s, 0);
	result = result && cyl_list_add( s, 1);
	result = result && cyl_list_add( s, 2);
	result = result && cyl_list_add( s, 3);
	result = result && cyl_list_add( s, 4);
	result = result && (s->heads[0] == &(s->a[3]));
	result = result && (s->heads[1] == &(s->a[4]));
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing cyl_list_move: ");
	result = cyl_list_move( s, 3, p);
	result = result && (s->heads[0] == &(s->a[2]));
	result = result && (s->heads[1] == &(s->a[3]));
	result = result && cyl_list_move( s, 0, p);
	result = result && (s->heads[1] == &(s->a[0]));
	result = result && (s->heads[0]->next->next == NULL);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing state_uniform_initialize: ");
	result = state_uniform_initialize( s);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing state_print: ");
	file = fopen( "test_uniform.dat", "w");
	result = state_print( file, s);
	fclose( file);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}	
	fprintf( stdout, " printed to file \"test_uniform.dat\"\n");

	state_free( s);
}

int main(){
	state_test();
	return 0;
}