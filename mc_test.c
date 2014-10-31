/*!*******************************************************************
 * mc_test.c
 * jefwagner@gmail.com
 *********************************************************************
 */

#include <stdio.h>

#include "montecarlo.c"

void mc_test(){
	int result;
	double u;
	cyl c1, c2;
	c1.r = 0.2;
	c2.r = 0.2;

	fprintf( stdout, "Testing move_cyl: ");
	c1.p.x = 0.; c1.p.y = 0.; c1.p.z = 0.;
	c1.d.x = 0.; c1.d.y = 0.; c1.d.z = 1.;
	c2 = move_cyl( c1);
	result = (vec3_mag( c2.p) <= 0.5);
	result = result && ( c2.d.z >= 0 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing u_cc: ");	
	c2.p.x = 0.4; c2.p.y = 0.; c2.p.z = 0.;
	c2.d.x = 0.; c2.d.y = 0.; c2.d.z = 1.;
	u = u_cc( c1, c2);
	result = ( u + 1. - 0.016316891135999996 < 1.e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}
}

int main(){
	mc_test();
	return 0;
}