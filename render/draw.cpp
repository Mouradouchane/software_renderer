
#pragma once

#ifndef DRAW_CPP
#define DRAW_CPP

#include "render.hpp"

namespace draw {

/*
	general purpose functions
*/
void sort_by_y(vec3d& p1, vec3d& p2, vec3d& p3, bool bysmaller) {

	if (bysmaller) {
		if (p1.y > p2.y || ((p1.y == p2.y) && p1.x > p2.x)) std::swap(p1, p2);
		if (p1.y > p3.y || ((p1.y == p3.y) && p1.x > p3.x)) std::swap(p1, p3);
		if (p2.y > p3.y || ((p2.y == p3.y) && p2.x > p3.x)) std::swap(p2, p3);
	}
	else {
		if (p1.y < p2.y || ((p1.y == p2.y) && p1.x < p2.x)) std::swap(p1, p2);
		if (p1.y < p3.y || ((p1.y == p3.y) && p1.x < p3.x)) std::swap(p1, p3);
		if (p2.y < p3.y || ((p2.y == p3.y) && p2.x < p3.x)) std::swap(p2, p3);
	}

}

void sort_by_x(vec3d& p1, vec3d& p2, vec3d& p3, bool bysmaller) {

	if (bysmaller) {
		if (p1.x > p2.x || ((p1.x == p2.x) && p1.y > p2.y)) std::swap(p1, p2);
		if (p1.x > p3.x || ((p1.x == p3.x) && p1.y > p3.y)) std::swap(p1, p3);
		if (p2.x > p3.x || ((p2.x == p3.x) && p2.y > p3.y)) std::swap(p2, p3);
	}
	else {
		if (p1.x < p2.x || ((p1.x == p2.x) && p1.y < p2.y)) std::swap(p1, p2);
		if (p1.x < p3.x || ((p1.x == p3.x) && p1.y < p3.y)) std::swap(p1, p3);
		if (p2.x < p3.x || ((p2.x == p3.x) && p2.y < p3.y)) std::swap(p2, p3);
	}

}

scolor blend(scolor& back_color, scolor& front_color) {
	/*
	if (front_color.a == 0) return back_color;
	if (back_color.a == 0)  return front_color;
	*/
	
	// else : blend process
	scolor new_color;
	
	// solve for "a" alpha first
	// alpha's formula : a = af + ( 1 - af ) * ab
	new_color.a = front_color.a + (255 - front_color.a) * back_color.a;

	/* ================ blend formula ====================
			  af * cf + ( 1 - af ) * cb
		c = _______________________________
						a
	*/
	uint16_t af = (255 - front_color.a);
	new_color.r = (front_color.a * front_color.r + af * back_color.r) / new_color.a;
	new_color.g = (front_color.a * front_color.g + af * back_color.g) / new_color.a;
	new_color.b = (front_color.a * front_color.b + af * back_color.b) / new_color.a;

	return new_color;
}

void set_pixel(uint16_t x, uint16_t y , scolor& color) {
	graphics::back_buffer->set(x, y, color);
}

scolor random_scolor(bool random_alpha) {
	
	scolor color;
	
	color.r = math::random::uint8();
	color.g = math::random::uint8();
	color.b = math::random::uint8();
	color.a = (random_alpha) ? math::random::uint8() : UINT8_MAX;

	return color;
}

bgra8 random_bgra8(bool random_alpha) {
	return bgra8{
		math::random::uint8(),
		math::random::uint8(),
		math::random::uint8(),
		(random_alpha) ? math::random::uint8() : UINT8_MAX
	};
}

/*
	 draw lines functions

void draw_line_over_x(vec3d& p1, vec3d& p2, sfloat slope, scolor& color){
	
	if (p1.x > p2.x) std::swap(p1, p2);

	sfloat Y_intercept = math::y_intercept_at_x0_2d(p1 , slope);
	int16_t x = p1.x;
	int16_t y = p1.y;
	
	if (color.a < 255) {
		for (   ; x <= p2.x; x += 1) {
			y = (int16_t)math::y_intercept_2d(x, slope, Y_intercept);
			set_pixel( x, y, blend(graphics::back_buffer->get(x, y),color) );
		}
	}
	else {
		for (   ; x <= p2.x ; x += 1 ) {
			y = (int32_t)math::y_intercept_2d(x, slope, Y_intercept);
			set_pixel(x, y, color);
		}
	}

}

void draw_line_over_y(vec3d& p1, vec3d& p2, sfloat slope, scolor& color){

	if (p1.y > p2.y) std::swap(p1, p2);

	sfloat Y_intercept = math::y_intercept_at_x0_2d(p1,slope);
	int16_t x = p1.x;
	int16_t y = p1.y;

	if (color.a < 255) {
		for (   ; y <= p2.y; y += 1) {
			x = (int16_t)math::x_intercept_2d(y, slope, Y_intercept);
			set_pixel(x,y, blend(graphics::back_buffer->get(x,y), color));
		}
	}
	else {
		for (   ; y <= p2.y ; y += 1 ) {
			x = (int16_t)math::x_intercept_2d(y, slope, Y_intercept);
			set_pixel(x, y, color);
		}
	}

}

void draw_horizontal_line(vec3d& p1, vec3d& p2, scolor& color) {

	if (x_start > x_end) std::swap(x_start, x_end);

	if (color.a < 255) {
		for (   ; x_start <= x_end; x_start += 1) {
			set_pixel(x_start, Y, blend(graphics::back_buffer->get(x_start,Y), color) );
		}
	}
	else {
		for (   ; x_start <= x_end; x_start += 1) {
			set_pixel(x_start, Y, color);
		}
	}

}

void draw_vertical_line(vec3d& p1, vec3d& p2, scolor& color){

	if (y_start > y_end) std::swap(y_start, y_end);
	
	if (color.a < 255) {
		for (   ; y_start <= y_end; y_start += 1) {
			set_pixel(X, y_start, blend(graphics::back_buffer->get(X, y_start), color) );
		}
	}
	else {
		for (   ; y_start <= y_end; y_start += 1) {
			set_pixel(X, y_start, color);
		}
	}

}

void line_3d(vec3d& p1, vec3d& p2, scolor& color{
	// if invisible 
	if (color.a == 0) return;

	// calc line slope 
	sfloat slope = math::slope2d(p1, p2);

	if (slope == 0) {
		draw_horizontal_line(p1.x, p2.x, p1.y, color);
		return;
	}
	
	//if (slope > 999 || slope < -999) {
	if ( p1.x == p2.x ) {
		draw_vertical_line(p1.y, p2.y, p1.x, color);
	}

	if (slope < 1 && slope > -1) {
		draw_line_over_x(p1, p2, slope, color);
		return;
	}
	else {
		draw_line_over_y(p1, p2, slope, color);
		return;
	}

}
*/

bool top_left_rule(vec3d& a, vec3d& b) {
	return ((a.x < b.x) && (a.y == b.y)) || (a.y > b.y);
}

// check if from p1 to p2 is "clock-wise" using 3rd point
bool is_clock_wise(vec3d& test_point, vec3d& p1, vec3d& p2) {

	vec2d a{ p2.x - p1.x, p2.y - p1.y};
	vec2d b{ test_point.x  - p1.x, test_point.y  - p1.y};

	return (a.x * b.y) - (a.y * b.x) >= 0;
}

void fill_row(int32_t x_start, int32_t x_end, int32_t Y, int32_t z_start, int32_t z_end, scolor& color, bool blendcolor) {

	if (x_start >= x_end) std::swap(x_start, x_end);

	if (blendcolor) {
		for (int32_t X = x_start; X <= x_end; X++) {
			set_pixel(
				X, Y, blend(graphics::back_buffer->get(X,Y) , color)
			);
		}
	}
	else {
		for (int32_t X = x_start; X <= x_end; X++ ) {
			set_pixel(X, Y, color);
		}
	}

}

void fill_3d_triangle(
	vec3d a, vec3d b, vec3d c, scolor& color
) {

	bool do_alpha_blending = color.a < UINT8_MAX;

	a.x = std::floor(a.x); a.y = std::floor(a.y) , a.z = 1 / a.z;
	b.x = std::floor(b.x); b.y = std::floor(b.y) , b.z = 1 / b.z;
	c.x = std::floor(c.x); c.y = std::floor(c.y) , c.z = 1 / c.z;

	// sort triangle point by y for fill in orderer
	sort_by_y(a, b, c);

	// centroid to help us getting "clock-wise" orientation
	vec3d centroid = math::centroid(a, b, c);

	int8_t bais_ab = 0, bais_bc = 0, bais_ac = 0;

	// "clock-wise" check for proper rasterzation
	if (is_clock_wise(centroid, a, b)) {
		bais_ab = (top_left_rule(a, b)) ? 0 : -1;
		bais_bc = (top_left_rule(b, c)) ? 0 : -1;
		bais_ac = (top_left_rule(c, a)) ? 0 :  1;
	}
	else {
		bais_ab = (top_left_rule(b, a)) ? 0 :  1;
		bais_bc = (top_left_rule(c, b)) ? 0 :  1;
		bais_ac = (top_left_rule(a, c)) ? 0 : -1;
	}

	int32_t x_start = a.x, x_end = b.x, y = a.y;

	// calc slopes of triangle
	sfloat slope_ab = math::slope2d(a,b);
	sfloat slope_ac = math::slope2d(a,c);
	sfloat slope_bc = math::slope2d(b,c);

	// calc Y intercepts of triangle 
	// p.y - (slope * p.x)
	sfloat i_ab = a.y - (slope_ab * a.x);
	sfloat i_ac = a.y - (slope_ac * a.x);
	sfloat i_bc = b.y - (slope_bc * b.x);

	sfloat z_start = 0;
	sfloat z_end = 0;

	// take the inverse of z's for "depth calculation"
	sfloat p1_z = 1 / a.z;
	sfloat p2_z = 1 / b.z;
	sfloat p3_z = 1 / c.z;

	// fill the first half of the triangle from a to b
	if (slope_ab != 0 && slope_ac != 0) {

		for (   ; y <= b.y ; y++ ) {

			// x = (y - b) / m
			x_start = (y - i_ab) / slope_ab + bais_ab;
			x_end   = (y - i_ac) / slope_ac + bais_ac;

			// fill range
			fill_row(x_start, x_end, y , z_start , z_end , color , do_alpha_blending);
		}

	}
	else {
		x_start += bais_ab;
		x_end   += bais_ac;
		
		fill_row(x_start, x_end, y, z_start, z_end, color , do_alpha_blending);
		y += 1;
	}

	if (slope_bc != 0 && slope_ac != 0) {

		// fill the other half of the triangle from p2 to p3
		for (	; y <= c.y; y++ ) {
			
			// x = (y - b) / m
			x_start = (y - i_ac) / slope_ac + bais_ac;
			x_end   = (y - i_bc) / slope_bc + bais_bc;

			fill_row(x_start, x_end, y, z_start, z_end, color , do_alpha_blending);
		}
	}

}

void draw_3d_triangle(
	vec3d& p1, vec3d& p2, vec3d& p3,
	scolor& color
) {
	/*
	if (color.a == 0) return;

	line_3d(p1, p2, color);
	line_3d(p1, p3, color);
	line_3d(p2, p3, color);
	*/
}



}
// end : namespace draw

#endif
