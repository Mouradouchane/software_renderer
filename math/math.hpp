
/*
	========================================
	renderer math library for 2D 3D gemotry
	========================================
*/

#include "../types/types.hpp"

#ifndef MATH_HPP
	
	#define MATH_HPP

// vector's addition
// r = a + b 
vec2d operator + (vec2d const& a, vec2d const& b);
vec3d operator + (vec3d const& a, vec3d const& b);
vec4d operator + (vec4d const& a, vec4d const& b);

// vector's subtraction 
// r = a - b 
vec2d operator - (vec2d const& a, vec2d const& b);
vec3d operator - (vec3d const& a, vec3d const& b);
vec4d operator - (vec4d const& a, vec4d const& b);

// vector's dot product 
// v = a . b 
float64 operator * (vec2d const& a, vec2d const& b);
float64 operator * (vec3d const& a, vec3d const& b);
float64 operator * (vec4d const& a, vec4d const& b);


namespace math {
	
	/*
		scale vector by value 
		a *= scalar;
	*/
	void scale(vec2d& a, int32_t scalar);
	void scale(vec3d& a, int32_t scalar);
	void scale(vec4d& a, int32_t scalar);

	/*
		vector cross product
		c = a * b
	*/
	vec2d cross_product(vec2d const& a, vec2d const& b);
	vec3d cross_product(vec3d const& a, vec3d const& b);
	vec4d cross_product(vec4d const& a, vec4d const& b);

	/*
		vector length
		f = ||a||
	*/
	float32 length(vec2d const& a);
	float32 length(vec3d const& a);
	float32 length(vec4d const& a);

	/*
		unit vector 
		u = |a|
	*/
	vec2d unit_vector(vec2d const& a);
	vec3d unit_vector(vec3d const& a);
	vec4d unit_vector(vec4d const& a);

	/*
		distance from a to b
		d = square_root( (b.x - a.x)² + (b.y - a.y)² )
	*/
	float32 distance2d(vec2d const& a , vec2d const& b);
	float32 distance3d(vec3d const& a , vec3d const& b);

	/*
		slope
	*/


} 
// end : namespace math

#endif
