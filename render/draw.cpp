
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
*/
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

bool top_left_rule(vec3d& a, vec3d& b) {
	return ((a.x < b.x) && (a.y == b.y)) || (a.y > b.y);
}

void fill_3d_triangle(
	vec3d& p1, vec3d& p2, vec3d& p3,
	scolor& color
) {

	// sort triangle point by y for fill in orderer
	sort_by_y(p1, p2, p3);

	// centroid to help us getting "clock-wise" orientation
	vec2d centroid = math::centroid(
		vec2d{ p1.x,p1.y }, vec2d{ p2.x,p2.y }, vec2d{ p3.x , p3.y }
	);

	int8_t ab_bais = 0, bc_bais = 0, ac_bais = 0;

	/*
		check if centroid is on the right side of "p1 , p2"
		if so then the direction is gonna be "p1 , p2 , p3"
		otherwise  the direction is gonna be "p1 , p3 , p2"
	*/
	if (math::vector::cross_product(centroid, p1, p2) >= 0) {

		ab_bais = (top_left_rule(p1, p2)) ? 0 : -1;
		bc_bais = (top_left_rule(p2, p3)) ? 0 : -1;
		ac_bais = (top_left_rule(p3, p1)) ? 0 :  1;

	}
	else {
		ab_bais = (top_left_rule(p2, p1)) ? 0 :  1;
		bc_bais = (top_left_rule(p3, p2)) ? 0 :  1;
		ac_bais = (top_left_rule(p1, p3)) ? 0 : -1;
	}

	// p1 -> p2
	sfloat slope_1 = math::slope2d(p1, p2);
	sfloat intercept_1 = math::y_intercept_at_x0_2d(p1, slope_1);
	
	// p1 -> p3
	sfloat slope_3 = math::slope2d(p1, p3);
	sfloat intercept_3 = math::y_intercept_at_x0_2d(p1, slope_3);
	
	int32_t x_start = p1.x;
	int32_t x_end = p2.x;
	int32_t y = p1.y;

	// fill from p1 to p2
	if (slope_1 != 0) {

		for (   ; y <= p2.y ; y += 1) {
			
			x_start = (int32_t)math::x_intercept_2d(y, slope_1, intercept_1) + ab_bais;
			x_end   = (int32_t)math::x_intercept_2d(y, slope_3, intercept_3) + ac_bais;
			
			// fill range
			draw_horizontal_line(x_start, x_end, y, color);
		}

	}
	else {
		x_start += ab_bais;
		x_end   += ac_bais;
		
		draw_horizontal_line(x_start, x_end, y, color);
		y += 1;
	}

	// p2 -> p3
	sfloat slope_2 = math::slope2d(p2, p3);
	sfloat intercept_2 = math::y_intercept_at_x0_2d(p2, slope_2);
	
	// fill from p2 to p3
	for (   ; y <= p3.y; y += 1) {
		
		x_start = (int32_t)math::x_intercept_2d(y, slope_3, intercept_3) + ac_bais;
		x_end   = (int32_t)math::x_intercept_2d(y, slope_2, intercept_2) + bc_bais;
		draw_horizontal_line(x_start, x_end, y, color);

	}
	
}

void draw_3d_triangle(
	vec3d& p1, vec3d& p2, vec3d& p3,
	scolor& color
) {

	if (color.a == 0) return;

	line_3d(p1, p2, color);
	line_3d(p1, p3, color);
	line_3d(p2, p3, color);

}



}
// end : namespace draw

#endif
