
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

void fill_row(int32_t x_start, int32_t x_end, int32_t Y, int32_t z_start, int32_t z_end, scolor& color) {

	if (x_start >= x_end) std::swap(x_start, x_end);

	for (int32_t X = x_start; X <= x_end; X++ ) {
		set_pixel(X, Y, color);
	}

}

void fill_3d_triangle(
	vec3d& p1, vec3d& p2, vec3d& p3, scolor& color
) {

	// sort triangle point by y for fill in orderer
	sort_by_y(p1, p2, p3);

	// centroid to help us getting "clock-wise" orientation
	vec3d centroid = math::centroid(p1, p2, p3);

	int8_t bais_1 = 0, bais_2 = 0, bais_3 = 0;

	// using centroid and 2d cross_product to sort point in "clock-wise"
	if (math::vector::cross_product(centroid, p1,p2).z >= 0) {
		bais_1 = (top_left_rule(p1, p2)) ? 0 : -1;
		bais_2 = (top_left_rule(p2, p3)) ? 0 : -1;
		bais_3 = (top_left_rule(p3, p1)) ? 0 :  1;
	}
	else {
		bais_1 = (top_left_rule(p2, p1)) ? 0 :  1;
		bais_2 = (top_left_rule(p3, p2)) ? 0 :  1;
		bais_3 = (top_left_rule(p1, p3)) ? 0 : -1;
	}

	// calc slopes of triangle
	sfloat m1 = math::slope2d(p2,p1);
	sfloat m2 = math::slope2d(p3,p2);
	sfloat m3 = math::slope2d(p3,p1);

	// calc Y intercepts of triangle 
	// p.y - (slope * p.x)
	sfloat i1 = p1.y - (m1 * p1.x);
	sfloat i2 = p2.y - (m2 * p2.x);
	sfloat i3 = p3.y - (m3 * p3.x);

	int32_t x_start = int32_t(p1.x);
	int32_t x_end = int32_t(p2.x);
	int32_t y = int32_t(p1.y);

	sfloat z_start = 0;
	sfloat z_end = 0;

	// take the inverse of z's for "depth calculation"
	sfloat p1_z = 1 / p1.z;
	sfloat p2_z = 1 / p2.z;
	sfloat p3_z = 1 / p3.z;

	// fill the first half of the triangle from p1 to p2
	if (m1 != 0 && m3 != 0) {

		for (   ; y <= p2.y ; y += 1) {

			// x = (y - b) / m
			x_start = ((y - i1) / m1) + bais_1;
			x_end   = ((y - i3) / m3) + bais_3;
			
			// fill range
			fill_row(x_start, x_end, y , z_start , z_end , color);
		}

	}
	else {
		x_start += bais_1;
		x_end   += bais_3;
		
		fill_row(x_start, x_end, y, z_start, z_end, color);
		y += 1;
	}

	if (m2 != 0 && m3 != 0) {
		// fill the other half of the triangle from p2 to p3
		for (	; y <= p3.y; y += 1) {
			
			// x = (y - b) / m
			x_start = ((y - i3) / m3) + bais_3;
			x_end = ((y - i2) / m2) + bais_2;

			fill_row(x_start, x_end, y, z_start, z_end, color);
		}
	}
	else {
		x_start += bais_1;
		x_end += bais_2;

		fill_row(x_start, x_end, y, z_start, z_end, color);
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
