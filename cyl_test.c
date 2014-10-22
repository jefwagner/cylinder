#include <stdio.h>

#include "vecs.h"
#include "cylinders.c"

void cyl_test(){
	cyl c0, c1;
	vec3 p;
	double a;
	int status = 0;

	fprintf( stdout, "Testing cyl_point: ");
	c0.p.x = 0.; c0.p.y = 0.; c0.p.z = 0.;
	c0.d.x = 2.; c0.d.y = -2.; c0.d.z = 4.;
	c0.r = 0.1;
	p = cyl_point( c0, 0.5);
	status = ( p.x == 1. && p.y == -1. && p.z == 2.);
	p = cyl_point( c0, 0.75);
	status = status && ( p.z - 3. < 1.0e-4);
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing cyl_box_overlap: ");
	c0.p.x = 1.; c0.p.y = 1.; c0.p.z = 1.;
	c0.d.x = 1.; c0.d.y = 0.; c0.d.z = 0.;
	c0.r = 0.5;
	p.x = 3.; p.y = 2.; p.z = 2.;
	status = cyl_box_overlap( c0, p);
	p.x = 1.5; p.y = 2.; p.z = 2.;
	status = status && !cyl_box_overlap( c0, p);
	p.x = 2.6; p.y = 2.; p.z = 2.;
	status = status && cyl_box_overlap( c0, p);
	c0.r = 0.7;
	status = status && !cyl_box_overlap( c0, p);
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing cyl_dist: ");
	c0.p.x = 1.; c0.p.y = 0.; c0.p.z = 0.;
	c0.d.x = -1.; c0.d.y = 1.; c0.d.z = 0.;
	c0.r = 0.2;
	c1.p.x = 0.; c1.p.y = 0.; c1.p.z = 1.;
	c1.d.x = 1.; c1.d.y = 1.; c1.d.z = 0.;
	c1.r = 0.2;
	a = cyl_dist( c0, c1);
	status = ( a - 1. < 1.0e-7 );
	c1.p.x = 1.; c1.p.y = 1.; c1.p.z = 1.;
	a = cyl_dist( c0, c1);
	status = status && ( a - sqrt(1.5) < 1.0e-7 );
	c1.p.x = 2.; c1.p.y = 0; c1.p.z = 1.;
	a = cyl_dist( c0, c1);
	status = status && ( a - sqrt(2.) < 1.0e-7 );
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing cyl_dist: ");
	c0.p.x = 1.; c0.p.y = 0.; c0.p.z = 0.;
	c0.d.x = -1.; c0.d.y = 1.; c0.d.z = 0.;
	c0.r = 0.2;
	c1.p.x = 0.; c1.p.y = 0.; c1.p.z = 1.;
	c1.d.x = 1.; c1.d.y = 1.; c1.d.z = 0.;
	c1.r = 0.2;
	status = !cyl_cyl_overlap( c0, c1);
	c0.r = 0.6; c1.r = 0.6;
	status = status && cyl_cyl_overlap( c0, c1);
	if( status){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

}

int main(){
	cyl_test();
	return 0;
}