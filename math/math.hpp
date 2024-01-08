
/*
	========================================
	renderer math library for 2D 3D gemotry
	========================================
*/

#include "../types/types.hpp"

#ifndef MATH_HPP
	
	#define MATH_HPP

/*
	global vector operators 
*/

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
sfloat operator * (vec2d const& a, vec2d const& b);
sfloat operator * (vec3d const& a, vec3d const& b);
sfloat operator * (vec4d const& a, vec4d const& b);


namespace math {

	
	// calc the change of deltha from v1 to v2 
	// dt = v1 - v2
	sfloat deltha( sfloat v1 , sfloat v2 );

	// slope of the line : 
	// s = dy / dx 
	sfloat slope2d(vec2d const& a, vec2d const& b);
	sfloat slope3d(vec3d const& a, vec3d const& b);

	// distance between a and b
	// distance = sqrt( (b.x - a.x)² + (b.y - a.y)² )
	sfloat distance2d(vec2d const& a , vec2d const& b);
	sfloat distance3d(vec3d const& a , vec3d const& b);

	// find point on the line in 2d
	sfloat y_intercept_2d(sfloat x, sfloat slope, sfloat y_at_x0);
	sfloat x_intercept_2d(sfloat y, sfloat slope, sfloat y_at_y0);

	// find intersection when x or y is 0
	sfloat y_intercept_at_x0_2d( vector2d const& point , sfloat slope );
	sfloat x_intercept_at_y0_2d( sfloat y_at_x0 , sfloat slope );

	// find where tow points intersect in 2D 
	vector2d tow_points_intersection(
		vector2d const& p1 , sfloat p1_slope, 
		vector2d const& p2 , sfloat p2_slope
	);

	// find if point is inside or outside the triangle
	bool is_point_inside_triangle(
		vector2d const& p1 , vector2d const& p2 , vector2d const& p3  
	);
	bool is_point_inside_triangle(
		vector3d const& p1 , vector3d const& p2 , vector3d const& p3
	);

	// triangle center of size
	vector2d centroid( 
		vector2d const& p1 , vector2d const& p2 , vector2d const& p3  
	);
	vector3d centroid( 
		vector3d const& p1 , vector3d const& p2 , vector3d const& p3  
	);

	// triangle area in 2D or 3D
	sfloat triangle_area(
		vector2d const& p1 , vector2d const& p2 , vector2d const& p3  
	);
	sfloat triangle_area(
		vector3d const& p1 , vector3d const& p2 , vector3d const& p3  
	);

	namespace vector {

		// scale vector by value
		// a *= scalar;
		void scale(vec2d& a, int32_t scalar);
		void scale(vec3d& a, int32_t scalar);
		void scale(vec4d& a, int32_t scalar);

		// vector cross product
		// c = a * b
		vec2d product(vec2d const& a, vec2d const& b);
		vec3d product(vec3d const& a, vec3d const& b);
		vec4d product(vec4d const& a, vec4d const& b);

		// vector length : ||a||
		sfloat length(vec2d const& a);
		sfloat length(vec3d const& a);
		sfloat length(vec4d const& a);

		// unit vector : |a|
		vec2d unit(vec2d const& a);
		vec3d unit(vec3d const& a);
		vec4d unit(vec4d const& a);
		
		// calc normal between to vectors in 2D or 3D
		vector2d normal( vector2d const& p1 , vector2d const& p2 );
		vector3d normal( vector3d const& p1 , vector3d const& p2 );
	
	}
	// end : namespace vector

} 
// end : namespace math

#endif
