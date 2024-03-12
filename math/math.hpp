
/*
	========================================
	renderer math library for 2D 3D gemotry
	========================================
*/

#include "../types/types.hpp"

#ifndef TIME_H
#define TIME_H
	#include <time.h>
#endif

#ifndef RANDOM_H
#define RANDOM_H
	#include <random>
#endif

#ifndef MATH_H
#define MATH_H
	#include <math.h>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
	#include <iostream>
#endif

#ifndef MATH_HPP
	
#define MATH_HPP

/*
	global vector operators 
*/

// vector's addition
// r = a + b 
vec2d operator + (vec2d const& a, vec2d const& b);
vec3d operator + (vec3d const& a, vec3d const& b);

// vector's subtraction 
// r = a - b 
vec2d operator - (vec2d const& a, vec2d const& b);
vec3d operator - (vec3d const& a, vec3d const& b);

// vector's dot product 
// v = a . b 
sfloat operator * (vec2d const& a, vec2d const& b);
sfloat operator * (vec3d const& a, vec3d const& b);

namespace math {

	extern uint16_t max_slope;
	extern const sfloat pi;

	void x_rotate(vec3d const& origin, vec3d& point, sfloat rad_angle = 0);
	void y_rotate(vec3d const& origin, vec3d& point, sfloat rad_angle = 0);
	void z_rotate(vec3d const& origin, vec3d& point, sfloat rad_angle = 0);

	/* 
		class for random generation based on time function
	*/
	class random {

		public :

		// unsigned 
		static uint8_t  uint8 (uint8_t  min=0, uint8_t  max=UINT8_MAX);
		static uint16_t uint16(uint16_t min=0, uint16_t max=UINT16_MAX);
		static uint32_t uint32(uint32_t min=0, uint32_t max=UINT32_MAX);
		static uint64_t uint64(uint64_t min=0, uint64_t max=UINT64_MAX);
	
		// signed
		static int8_t  int8 (int8_t  min=0, int8_t  max=INT8_MAX);
		static int16_t int16(int16_t min=0, int16_t max=INT16_MAX);
		static int32_t int32(int32_t min=0, int32_t max=INT32_MAX);
		static int64_t int64(int64_t min=0, int64_t max=INT64_MAX);

	};
	// end : class random

	// to convert between rad & deg
	sfloat to_radian(sfloat degree_value);
	sfloat to_degree(sfloat radian_value);

	// calc the change of deltha from v1 to v2 
	// dt = v1 - v2
	sfloat deltha( sfloat v1 , sfloat v2 );

	// slope of the line : b -> a
	// s = dy / dx
	sfloat slope2d(vec2d const& a, vec2d const& b);
	sfloat slope2d(vec3d const& a, vec3d const& b);
	// todo !!!
	sfloat slope3d(vec3d const& a, vec3d const& b);

	// distance between a and b
	// distance = sqrt( (b.x - a.x)² + (b.y - a.y)² )
	sfloat distance2d(vec2d const& a , vec2d const& b);
	sfloat distance3d(vec3d const& a , vec3d const& b);

	// find y in x poisiton on hte line
	// y = slope * x + y_at_x0
	sfloat y_intercept_2d(sfloat x, sfloat slope, sfloat y_at_x0);

	// find x in y poisiton on the line
	// x = (y - b) / slope
	sfloat x_intercept_2d(sfloat y, sfloat slope, sfloat y_at_x0);

	// find y when x = 0 on the line 
	// Y = p.y - (slope * p.x)
	sfloat y_intercept_at_x0_2d(vec2d const& point, sfloat slope);

	// find x when y = 0 on the line
	// X = (y - y_at_x0) / slope
	sfloat x_intercept_at_y0_2d(sfloat y_at_x0, sfloat slope);

	// find where tow points intersect in 2D 
	// formula :: x = ((d - c) / ((a - b) | 1))
	// formula :: y = ( a * ( (d - c) / ((a - b) | 1) ) ) + c
	vec2d tow_points_intersection(
		vec2d const& p1 , sfloat p1_slope , 
		vec2d const& p2 , sfloat p2_slope
	);

	// find if point is inside or outside the triangle
	bool is_point_inside_triangle(
		vec2d const& target_point ,
		vec2d const& p1 , vec2d const& p2 , vec2d const& p3 , 
		bool ignore_point_on_the_line = false
	);
	bool is_point_inside_triangle(
		vec3d const& target_point , 
		vec3d const& p1 , vec3d const& p2 , vec3d const& p3 ,
		bool ignore_point_on_the_line = false
	);

	// centroid of 2D triangle
	// ap = (a1 + p2 + a3) / 3 
	vec2d centroid(
		vec2d const& p1 , vec2d const& p2 , vec2d const& p3
	);
	vec2d centroid(
		sfloat x1, sfloat y1, sfloat x2, sfloat y2, sfloat x3, sfloat y3
	);
	// centroid of 3D triangle
	vec3d centroid( 
		vec3d const& p1 , vec3d const& p2 , vec3d const& p3
	);

	// calculate the area of 2D triangle using "Heron's Formula"
    // note : no negative area
	// formula1 : p = (a+b+c) / 3
	// formula2 : area = sqrt( p * (p - A) * (p - B) * (p - C) )
	sfloat triangle_area(
		vec2d const& p1 , vec2d const& p2 , vec2d const& p3
	);
	sfloat triangle_area(
		vec3d const& p1 , vec3d const& p2 , vec3d const& p3
	);

	namespace vector {

		// scale vector by value
		// a *= scalar;
		void scale(vec2d& a, sfloat scalar);
		void scale(vec3d& a, sfloat scalar);

		// vector cross product between 3 points in space
		// note : ordering is matter
		// c = a * b or ||a||*||b|| sin(angle)  
		sfloat cross_product(vec2d const& origin, vec2d const& p1, vec2d const& p2);
		vec3d  cross_product(vec3d const& origin, vec3d const& p1, vec3d const& p2);

		// note : length of the vector based on the origin(0,0,0)
		// formula :: len = sqrt(x² + y²)
		sfloat length(vec2d const& a);
		sfloat length(vec3d const& a);

		// note : none zero vector length
		// formula :: |a| =  a / ||a||
		vec2d unit(vec2d const& a);
		vec3d unit(vec3d const& a);
		
		// get normals between vectors in 2D or 3D
		vec2d left_normal(vec2d const& p1, vec2d const& p2);
		vec3d left_normal(vec3d const& p1, vec3d const& p2);
		vec2d right_normal(vec2d const& p1 , vec2d const& p2);
		vec3d right_normal(vec3d const& p1 , vec3d const& p2);
	
	}
	// end : namespace vector

} 
// end : namespace math

#endif
