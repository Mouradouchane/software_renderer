
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

void fill_row(int32_t x_start, int32_t x_end, int32_t Y, sfloat z_start, sfloat z_end, scolor& color) {

	if (x_start > x_end) {
		std::swap(x_start, x_end);
		std::swap(z_start, z_end);
	}

	sfloat m = math::slope2d( vec2d{(sfloat)x_start,z_start} , vec2d{(sfloat)x_end,z_end} );
	sfloat B = math::y_intercept_at_x0_2d( vec2d{(sfloat)x_start,z_start} , m );

	sfloat zfactor = (x_end - x_start) != 0 ? sfloat( 1 / (x_end - x_start) ) : 1;
	sfloat z = 0 , bz = 0 , t = 0;

	for (int32_t X = x_start; X <= x_end; X++ ) {
			
		// z = m * X + B;
		z = math::lerp(z_start, z_end, t);
		// bz = graphics::depth_buffer->get(X, Y);

		// depth test
		if (z > graphics::depth_buffer->get(X, Y)) {
			set_pixel(X, Y, color);
			graphics::depth_buffer->set(X, Y, z);
		}

		t += zfactor;
	}
	

}

void fill_3d_triangle(
	vec3d a, vec3d b, vec3d c, scolor& color
) {

	a.x = std::floor(a.x); a.y = std::floor(a.y);
	b.x = std::floor(b.x); b.y = std::floor(b.y);
	c.x = std::floor(c.x); c.y = std::floor(c.y);

	// take the 1/old_z for depth test
	sfloat wA = 1 / a.w; 
	sfloat wB = 1 / b.w;
	sfloat wC = 1 / c.w;

	// sort triangle point by y for fill in orderer
	sort_by_y(a, b, c);

	sfloat area  = math::area_of_2d_triangle(a,b,c); // area of project triangle
	sfloat alpha = 0, beta = 0, gamma = 0; // area of sub triangles

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
	sfloat z_start = 0 , z_end = 0;
	vec3d p{ a.x , a.y , 0, 0};

	// calc slopes of triangle
	sfloat slope_ab = math::slope2d(a,b);
	sfloat slope_ac = math::slope2d(a,c);
	sfloat slope_bc = math::slope2d(b,c);

	// calc Y intercepts of triangle 
	// p.y - (slope * p.x)
	sfloat i_ab = a.y - (slope_ab * a.x);
	sfloat i_ac = a.y - (slope_ac * a.x);
	sfloat i_bc = b.y - (slope_bc * b.x);

	// fill the first half of the triangle from a to b
	if (slope_ab != 0 && slope_ac != 0) {

		for (   ; y <= b.y ; y++ ) {

			// x = (y - b) / m
			x_start = (y - i_ab) / slope_ab + bais_ab;
			x_end   = (y - i_ac) / slope_ac + bais_ac;
			
			p.x = sfloat(x_start) + 0.5;
			p.y = sfloat(y) + 0.5;

			alpha = math::area_of_2d_triangle(p, b, c) / area;
			beta  = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - (alpha + beta);
			z_start = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

			p.x = sfloat(x_end + 0.5);

			alpha = math::area_of_2d_triangle(p, c, b) / area;
			beta  = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - (alpha + beta);
			z_end = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

			fill_row(x_start, x_end, y, z_start, z_end, color);
			
		}

	}
	else {
		x_start += bais_ab;
		x_end   += bais_ac;

		p.x = sfloat(x_start) + 0.5;
		p.y = sfloat(y) + 0.5;

		alpha = math::area_of_2d_triangle(p, b, c) / area;
		beta = math::area_of_2d_triangle(a, p, c) / area;
		gamma = 1 - (alpha + beta);
		z_start = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

		p.x = sfloat(x_end + 0.5);

		alpha = math::area_of_2d_triangle(p, c, b) / area;
		beta = math::area_of_2d_triangle(a, p, c) / area;
		gamma = 1 - (alpha + beta);
		z_end = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

		fill_row(x_start, x_end, y, z_start, z_end, color);
		y += 1;
	}

	if (slope_bc != 0 && slope_ac != 0) {

		// fill the other half of the triangle from p2 to p3
		for (	; y <= c.y ; y++ ) {
			
			// x = (y - b) / m
			x_start = (y - i_ac) / slope_ac + bais_ac;
			x_end = (y - i_bc) / slope_bc + bais_bc;

			p.x = sfloat(x_start) + 0.5;
			p.y = sfloat(y) + 0.5;

			alpha = math::area_of_2d_triangle(p, b, c) / area;
			beta = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - (alpha + beta);
			z_start = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

			p.x = sfloat(x_end + 0.5);

			alpha = math::area_of_2d_triangle(p, c, b) / area;
			beta = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - (alpha + beta);
			z_end = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

			fill_row(x_start, x_end, y, z_start, z_end, color);

		}

	}

}

void fill_3d_triangle_proto1(
	vec3d a, vec3d b, vec3d c, scolor& color
) {

	a.x = std::floor(a.x); a.y = std::floor(a.y);
	b.x = std::floor(b.x); b.y = std::floor(b.y);
	c.x = std::floor(c.x); c.y = std::floor(c.y);

	// take the 1/old_z for depth test
	sfloat wA = 1 / a.w;
	sfloat wB = 1 / b.w;
	sfloat wC = 1 / c.w;

	// sort triangle point by y for fill in orderer
	sort_by_y(a, b, c);

	sfloat area = math::area_of_2d_triangle(a, b, c); // area of project triangle
	sfloat alpha = 0, beta = 0, gamma = 0; // area of sub triangles

	// centroid to help us getting "clock-wise" orientation
	vec3d centroid = math::centroid(a, b, c);

	int8_t bais_ab = 0, bais_bc = 0, bais_ac = 0;

	// "clock-wise" check for proper rasterzation
	if (is_clock_wise(centroid, a, b)) {
		bais_ab = (top_left_rule(a, b)) ? 0 : -1;
		bais_bc = (top_left_rule(b, c)) ? 0 : -1;
		bais_ac = (top_left_rule(c, a)) ? 0 : 1;
	}
	else {
		bais_ab = (top_left_rule(b, a)) ? 0 : 1;
		bais_bc = (top_left_rule(c, b)) ? 0 : 1;
		bais_ac = (top_left_rule(a, c)) ? 0 : -1;
	}

	int32_t x_start = a.x, x_end = b.x, y = a.y;
	sfloat z = 0;
	vec3d p{ a.x , a.y , 0, 0 };

	// calc slopes of triangle
	sfloat slope_ab = math::slope2d(a, b);
	sfloat slope_ac = math::slope2d(a, c);
	sfloat slope_bc = math::slope2d(b, c);

	// calc Y intercepts of triangle 
	// p.y - (slope * p.x)
	sfloat i_ab = a.y - (slope_ab * a.x);
	sfloat i_ac = a.y - (slope_ac * a.x);
	sfloat i_bc = b.y - (slope_bc * b.x);

	// fill the first half of the triangle from a to b
	if (slope_ab != 0 && slope_ac != 0) {

		for (	; y <= b.y ; y++ ) {

			// x = (y - b) / m
			x_start = (y - i_ab) / slope_ab + bais_ab;
			x_end   = (y - i_ac) / slope_ac + bais_ac;

			if (x_start > x_end) {
				std::swap(x_start, x_end);
			}

			p.x = sfloat(x_start) + 0.5;
			p.y = sfloat(y) + 0.5;

			for (	; x_start <= x_end ; x_start += 1 , p.x += 1) {

				alpha = math::area_of_2d_triangle(p, b, c) / area;
				beta  = math::area_of_2d_triangle(a, p, c) / area;
				gamma = 1 - (alpha + beta);

				z = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

				if (z > graphics::depth_buffer->get(x_start, y)) {
					graphics::back_buffer->set(x_start, y, color);
					graphics::depth_buffer->set(x_start, y, z);
				}

			}

		}

	}
	else {
		x_start += bais_ab;
		x_end   += bais_ac;

		if (x_start > x_end) {
			std::swap(x_start, x_end);
		}

		p.x = sfloat(x_start) + 0.5;
		p.y = sfloat(y) + 0.5;

		for (	; x_start <= x_end ; x_start += 1 , p.x += 1) {

			alpha = math::area_of_2d_triangle(p, b, c) / area;
			beta  = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - (alpha + beta);

			z = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

			if (z > graphics::depth_buffer->get(x_start, y)) {
				graphics::back_buffer->set(x_start, y, color);
				graphics::depth_buffer->set(x_start, y, z);
			}

		}

		y += 1;
	}

	if (slope_bc != 0 && slope_ac != 0) {

		// fill the other half of the triangle from p2 to p3
		for (	; y <= c.y ; y++ ) {

			// x = (y - b) / m
			x_start = (y - i_ac) / slope_ac + bais_ac;
			x_end   = (y - i_bc) / slope_bc + bais_bc;

			if (x_start > x_end) {
				std::swap(x_start, x_end);
			}

			p.x = sfloat(x_start) + 0.5;
			p.y = sfloat(y) + 0.5;

			for (	; x_start <= x_end ; x_start += 1 , p.x += 1) {

				alpha = math::area_of_2d_triangle(p, b, c) / area;
				beta  = math::area_of_2d_triangle(a, p, c) / area;
				gamma = 1 - (alpha + beta);

				z = 1 / ((alpha * wA) + (beta * wB) + (gamma * wC));

				if (z > graphics::depth_buffer->get(x_start, y)) {
					graphics::back_buffer->set(x_start, y, color);
					graphics::depth_buffer->set(x_start, y, z);
				}

			}

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
