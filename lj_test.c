#include <stdio.h>

#include "lennardjones.c"

void test_lj(){
	int status = 0;
	lj_params p = { .u0 = 2., .r0 = 3.};
	double a;

	fprintf( stdout, "Testing lj_simple: ");
	a = lj_simple( p.r0, p);
	status = ( a + p.u0 < 1.0e-7 );
	a = lj_simple( p.r0*TWO_1_6, p);
	status = status && ( a + 0.75*p.u0 < 1.0e-7 );
	a = lj_simple( p.r0/TWO_1_6, p);
	status = status && ( a - 0. < 1.0e-7 );
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing lj_shifted: ");
	p.u0 = 5.; p.r0 = 0.5; 
	a = lj_shifted( p.r0, p);
	status = ( a - 0. < 1.0e-7 );
	a = lj_shifted( p.r0*TWO_1_6, p);
	status = status && ( a - 0. < 1.0e-7 );
	a = lj_shifted( p.r0/TWO_1_6, p );
	status = status && ( a - p.u0 < 1.0e-7 );
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing lj_truncated: ");
	p.u0 = 1.; p.r0 = 2.;
	a = lj_truncated( p.r0, p);
	status = ( a + p.u0*(1.-LJ_DU) < 1.0e-7 );
	a = lj_truncated( p.r0*TWO_1_6, p);
	status = status && ( a + p.u0*(0.75-LJ_DU) < 1.0e-7 );
	a = lj_truncated( p.r0/TWO_1_6, p);
	status = status && ( a - p.u0*(0+LJ_DU) < 1.0e-7 );
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

}

int main(){
	test_lj();
	return 0;
}