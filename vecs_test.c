#include <stdio.h>

#include "math_const.h"
#include "vecs.h"

void vec2_arithmatic_test(){
	int result = 0;
	double a;
	vec2 v0 = {0., 1.};
	vec2 v1 = {1., 0.};
	vec2 v2;
	fprintf( stdout, "Testing vec2_add and vec2_addto: ");
	v2 = vec2_add( v0, v1);
	result = ( v2.x == 1. && v2.y == 1.);
	vec2_addto( &v0, v1);
	result = result && (v0.x == 1. && v0.y == 1. );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec2_sub and vec2_subto: ");
	v2 = vec2_sub( v0, v1);
	result = ( v2.x == 0. && v2.y == 1.);
	vec2_subto( &v0, v1);
	result = result && (v0.x == 0. && v0.y == 1. );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec2_neg and vec2_negto: ");
	v2 = vec2_neg( v1);
	result = ( v2.x == -1. && v2.y == 0.);
	vec2_negto( &v0);
	result = result && (v0.x == 0. && v0.y == -1. );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec2_smul and vec2_smulto: ");
	v2 = vec2_smul( v0, -1.);
	result = ( v2.x == 0. && v2.y == 1.);
	vec2_smulto( &v0, -1);
	result = result && (v0.x == 0. && v0.y == 1. );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}	

	fprintf( stdout, "Testing vec2_dot, vec2_cross, vec2_mag: ");
	a = vec2_dot( v0, v1);
	result = ( a == 0.);
	a = vec2_cross( v0, v1);
	result = result && ( a == -1.);
	v2 = vec2_add( v0, v1);
	a = vec2_mag( v2);
	result = result && ( (a - ROOT2) < 1.0e-7);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}	

	fprintf( stdout, "Testing vec2_unit and vec2_unitto: ");
	v2 = vec2_unit( v2);
	result = ( (v2.x - 1./ROOT2) < 1.0e-7 && (v2.y - 1./ROOT2) < 1.0e-7 );
	v2 = vec2_add( v0, v1);
	vec2_unitto( &v2);
	result = result && ( (v2.x - 1./ROOT2) < 1.0e-7 && 
		                 (v2.y - 1./ROOT2) < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec2_rot and vec2_rotto: ");
	v2 = vec2_rot( v1, PI_2);
	result = ( (v2.x - v0.x) < 1.0e-7 && (v2.y - v2.y) < 1.0e-7 );
	v2 = v1;
	vec2_rotto( &v2, PI_2);
	result = result && ( (v2.x - v0.x) < 1.0e-7 && 
		                 (v2.y - v0.y) < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec2_dist: ");
	a = vec2_dist( v0, v1);
	result = ( (a - ROOT2) < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}
}

void vec3_arithmatic_test(){
	int result = 0;
	double a;
	vec3 ihat = {1., 0., 0.};
	vec3 jhat = {0., 1., 0.};
	vec3 khat = {0., 0., 1.};
	vec3 v0;

	fprintf( stdout, "Testing vec3_add and vec3_addto: ");
	v0 = vec3_add( ihat, jhat);
	result = ( v0.x == 1. && v0.y == 1. && v0.z == 0.);
	vec3_addto( &v0, khat);
	result = result && (v0.x == 1. && v0.y == 1. && v0.z == 1.);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec3_sub and vec3_subto: ");
	v0 = vec3_sub( ihat, jhat);
	result = ( v0.x == 1. && v0.y == -1. && v0.z == 0.);
	vec3_subto( &v0, khat);
	result = result && (v0.x == 1. && v0.y == -1. && v0.z == -1.);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec3_neg and vec3_negto: ");
	v0 = vec3_neg( ihat);
	result = ( v0.x == -1. && v0.y == 0. && v0.z == 0.);
	vec3_negto( &v0);
	result = result && (v0.x == 1. && v0.y == 0. && v0.z == 0.);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec3_smul and vec3_smulto: ");
	v0 = vec3_smul( jhat, -2.);
	result = ( v0.x == 0. && v0.y == -2. && v0.z == 0.);
	vec3_smulto( &v0, -1.5);
	result = result && (v0.x == 0. && v0.y == 3. && v0.z == 0.);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}	

	fprintf( stdout, "Testing vec3_dot and vec3_mag: ");
	v0 = vec3_smul( vec3_add( ihat, jhat), 2.0);
	a = vec3_dot( v0, ihat);
	result = ( a == 2.);
	a = vec3_mag( v0);
	result = result && ( a - 2.*ROOT2 < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}	

	fprintf( stdout, "Testing vec3_cross and vec3_crossto: ");
	v0 = vec3_cross( ihat, jhat);
	result = ( v0.x == 0. && v0.y == 0. && v0.z == 1.);
	v0 = ihat;
	vec3_crossto( &v0, jhat);
	result = result && ( v0.x == 0. && v0.y == 0. && v0.z == 1.);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}	

	fprintf( stdout, "Testing vec3_unit and vec3_unitto: ");
	v0 = vec3_unit( vec3_add( ihat, vec3_add( jhat, khat)));
	a = 1./sqrt(3.);
	result = ( v0.x - a < 1.0e-7 && v0.y - a < 1.0e07);
	v0 = vec3_smul( v0, sqrt(3.));
	vec3_unitto( &v0);
	result = result && ( v0.x - a < 1.0e-7 && v0.y - a < 1.0e07);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec3_rotAA and vec3_rotAAto: ");
	v0 = vec3_rotAA( ihat, vec3_add( ihat, vec3_add( jhat, khat)), 2.*PI_3);
	result = ( v0.x - 0. < 1.0e-7 &&
	  		   v0.y - 1. < 1.0e-7 && 
	           v0.z - 0. < 1.0e-7);
	v0 = khat;
	vec3_rotAAto( &v0, vec3_add( ihat, vec3_add( jhat, khat)), 2.*PI_3);
	result = result && ( v0.x - 1. < 1.0e-7 &&
	  		             v0.y - 0. < 1.0e-7 && 
	                     v0.z - 0. < 1.0e-7);
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}

	fprintf( stdout, "Testing vec3_dist: ");
	a = vec3_dist( ihat, vec3_add( jhat, khat));
	result = ( (a - sqrt(3.)) < 1.0e-7 );
	if( result ){
		fprintf( stdout, "passed!\n");
	}else{
		fprintf( stdout, "failed!\n");
	}
}

int main(){
	vec2_arithmatic_test();
	vec3_arithmatic_test();
	return 0;
}