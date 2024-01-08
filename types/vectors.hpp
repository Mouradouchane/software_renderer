
/*
	=================================================
	====================== vectors ==================
	=================================================
*/

#ifndef _stdint
	#define _stdint	
	#include <stdint.h> // for int32 int64 ...
#endif

#ifndef VECTORS_HPP

    #define VECTORS_HPP

class vec2d {

public :

	vector2d vector;

	// constructor's
	vec2d();
	vec2d(sfloat x , sfloat y);

	// destructor
	~vec2d() = default;

};
// end : class vec2d 

class vec3d {

public :

	vector3d vector;

	// constructor's
	vec3d();
	vec3d(sfloat x , sfloat y , sfloat z = 1.0f);

	// destructor
	~vec3d() = default;

};
// end : class vec3d 

class vec4d {

public : 

	vector4d vector;
	
	// constructor's
	vec4d();
	vec4d(sfloat x, sfloat y, sfloat z = 1.0f, sfloat w = 1.0f);

	// destructor
	~vec4d() = default;

};
// end : class vec4d 

#endif

