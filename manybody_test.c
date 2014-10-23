#include <stdio.h>

#include "manybody.c"

void state_test(){
	int result = 0;
	cyl_params cp = {0.2, 1};
	vec3 box = {20., 20., 11.};

	fprintf( stdout, "Testing state_malloc: ");
	state *s = state_malloc( cp, box, 500);
	result = (s != NULL);
	if( !result ){ 
		fprintf( stdout, "failed!\n");
		return; 
	}
	result = result && ( s->nbx == 6 && s->nby == 6 && s->nbz == 3 );
	result = result && ( s->bucket.x - 3.333333333333333 < 1.0e-7 );
	result = result && ( s->bucket.z - 3.6666666666666665 < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}
	state_free( s);
}

int main(){
	state_test();
	return 0;
}