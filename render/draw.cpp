
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

scolor blend(scolor const& back_color, scolor const& front_color) {
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
	renderer::back_buffer->set(x, y, color);
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

void draw_line_over_x(vec3d& p1, vec3d& p2, sfloat slope, scolor const& color){
	
	if (p1.x > p2.x) std::swap(p1, p2);

	sfloat Y_intercept = math::y_intercept_at_x0_2d(p1 , slope);
	uint32_t x = (uint32_t)p1.x;
	uint32_t y = (uint32_t)p1.y;
	uint32_t index = 0;

	if (color.a < UINT8_MAX) {
		for (   ; x <= p2.x; x += 1) {
			y = (int32_t)math::y_intercept_2d(x, slope, Y_intercept);
			index = renderer::back_buffer->width * y + x;

			renderer::back_buffer->memory[ index ] = blend(
				renderer::back_buffer->memory[ index ] , color
			);
		}
	}
	else {
		for (   ; x <= p2.x ; x += 1 ) {
			y = (int32_t)math::y_intercept_2d(x, slope, Y_intercept);
			index = renderer::back_buffer->width * y + x;

			renderer::back_buffer->memory[index] = color;
		}
	}

}

void draw_line_over_y(vec3d& p1, vec3d& p2, sfloat slope, scolor const& color){

	if (p1.y > p2.y) std::swap(p1, p2);

	sfloat Y_intercept = math::y_intercept_at_x0_2d(p1,slope);
	uint32_t x = (uint32_t)p1.x;
	uint32_t y = (uint32_t)p1.y;
	uint32_t index = 0;

	if (color.a < UINT8_MAX) {
		for (   ; y <= p2.y; y += 1) {
			x = (uint32_t)math::x_intercept_2d(y, slope, Y_intercept);
			index = renderer::back_buffer->width * y + x;

			renderer::back_buffer->memory[index] = blend(
				renderer::back_buffer->memory[index], color
			);
		}
	}
	else {
		for (   ; y <= p2.y ; y += 1 ) {
			x = (uint32_t)math::x_intercept_2d(y, slope, Y_intercept);
			index = renderer::back_buffer->width * y + x;

			renderer::back_buffer->memory[index] = color;
		}
	}

}

void draw_horizontal_line(int32_t x_start , int32_t x_end , int32_t Y , scolor const& color) {

	if (x_start > x_end) std::swap(x_start, x_end);
	uint32_t buffer_row = renderer::back_buffer->width * Y;

	if (color.a < UINT8_MAX) {
		for (	; x_start <= x_end; x_start += 1) {
			renderer::back_buffer->memory[buffer_row + x_start] = blend (
				renderer::back_buffer->memory[buffer_row + x_start] , color
			);
		}
	}
	else {
		for (   ; x_start <= x_end; x_start += 1) {
			renderer::back_buffer->memory[buffer_row + x_start] = color;
		}
	}

}

void draw_vertical_line(int32_t y_start, int32_t y_end, int32_t X, scolor const& color){

	if (y_start > y_end) std::swap(y_start, y_end);
	
	if (color.a < UINT8_MAX) {
		for (   ; y_start <= y_end; y_start += 1) {
			renderer::back_buffer->memory[renderer::back_buffer->width * y_start + X] = blend(
				renderer::back_buffer->memory[renderer::back_buffer->width * y_start + X] , color
			);
		}
	}
	else {
		for (   ; y_start <= y_end; y_start += 1) {
			renderer::back_buffer->memory[renderer::back_buffer->width * y_start + X] = color;
		}
	}

}

void draw_line(vec3d& p1, vec3d& p2, scolor const& color){

	// calc line slope 
	sfloat slope = math::slope2d(p1, p2);

	if (slope == 0) {
		draw_horizontal_line(
			(int32_t)p1.x, (int32_t)p2.x, (int32_t)p1.y, color
		);
		return;
	}
	
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
	sfloat z = 0;
	
	uint32_t buffer_row = renderer::back_buffer->width * Y, buffer_index = 0;

	if (color.a < UINT8_MAX) { // do alpha blending

		for (int32_t X = x_start; X <= x_end; X++) {
			z = m * X + B;
			buffer_index = buffer_row + X;

			// depth test
			if (z > renderer::depth_buffer->memory[buffer_index]) {
				renderer::back_buffer->memory[buffer_index]  = blend(renderer::back_buffer->memory[buffer_index], color);
				renderer::depth_buffer->memory[buffer_index] = z;
			}
		}

	}
	else { // no alpha blending

		for (int32_t X = x_start; X <= x_end; X++) {
			z = m * X + B;
			buffer_index = buffer_row + X;

			// depth test
			if ( z > renderer::depth_buffer->memory[buffer_index] ) {
				renderer::back_buffer->memory[buffer_index]  = color;
				renderer::depth_buffer->memory[buffer_index] = z;
			}
		}
	}
	
}

void fill_3d_triangle(
	vec3d a, vec3d b, vec3d c, scolor& color
) {

	a.x = std::floor(a.x); a.y = std::floor(a.y);
	b.x = std::floor(b.x); b.y = std::floor(b.y);
	c.x = std::floor(c.x); c.y = std::floor(c.y);

	// sort triangle point by y for fill in orderer
	sort_by_y(a, b, c);

	// take the 1/old_z for depth test
	sfloat wA = 1 / a.z; 
	sfloat wB = 1 / b.z;
	sfloat wC = 1 / c.z;

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
			gamma = 1 - alpha - beta;
			z_start = (alpha * wA) + (beta * wB) + (gamma * wC);

			p.x = sfloat(x_end) + 0.5;

			alpha = math::area_of_2d_triangle(p, c, b) / area;
			beta  = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - alpha - beta;
			z_end = (alpha * wA) + (beta * wB) + (gamma * wC);

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
		gamma = 1 - alpha - beta;
		z_start = (alpha * wA) + (beta * wB) + (gamma * wC);

		p.x = sfloat(x_end) + 0.5;

		alpha = math::area_of_2d_triangle(p, c, b) / area;
		beta  = math::area_of_2d_triangle(a, p, c) / area;
		gamma = 1 - alpha - beta;
		z_end = (alpha * wA) + (beta * wB) + (gamma * wC);

		fill_row(x_start, x_end, y, z_start, z_end, color);
		y += 1;
	}

	if (slope_bc != 0 && slope_ac != 0) {

		// fill the other half of the triangle from p2 to p3
		for (	; y <= c.y ; y++ ) {
			
			// x = (y - b) / m
			x_start = (y - i_ac) / slope_ac + bais_ac;
			x_end   = (y - i_bc) / slope_bc + bais_bc;

			p.x = sfloat(x_start) + 0.5;
			p.y = sfloat(y) + 0.5;

			alpha = math::area_of_2d_triangle(p, b, c) / area;
			beta  = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - alpha - beta;
			z_start = (alpha * wA) + (beta * wB) + (gamma * wC);

			p.x = sfloat(x_end) + 0.5;

			alpha = math::area_of_2d_triangle(p, c, b) / area;
			beta  = math::area_of_2d_triangle(a, p, c) / area;
			gamma = 1 - alpha - beta;
			z_end = (alpha * wA) + (beta * wB) + (gamma * wC);

			fill_row(x_start, x_end, y, z_start, z_end, color);

		}

	}

}

void draw_3d_triangle(
	vec3d& p1, vec3d& p2, vec3d& p3, scolor& color
) {
	
	draw_line(p1, p2, color);
	draw_line(p1, p3, color);
	draw_line(p2, p3, color);
	
}

/*
	draw circle functions
*/
void fill_circle_row(int32_t x_start, int32_t x_end, int32_t Y, scolor const& color) {

	if (x_start > x_end) {
		std::swap(x_start, x_end);
	}

	uint32_t y_row = renderer::back_buffer->width * Y;

	if (color.a < UINT8_MAX) {
		for (; x_start <= x_end; x_start++) {
			renderer::back_buffer->memory[y_row + x_start] = blend(renderer::back_buffer->memory[y_row + x_start] , color);
		}
	}
	else {
		for (	; x_start <= x_end ; x_start++ ) {
			renderer::back_buffer->memory[y_row + x_start] = color;
		}
	}

}

void fill_circle(int32_t x_origin, int32_t y_origin, int32_t radius, scolor const& color) {

	uint32_t rsqr = radius * radius;
	uint32_t ysqr = 0;

	for (int32_t y = -radius; y < 0; y++ ) {

		ysqr = y * y;

		for (int32_t x = -radius; x <= radius; x++) {

			if (x * x + ysqr <= rsqr) {

				fill_circle_row(x_origin - x, x_origin + x, y_origin + y, color);
				fill_circle_row(x_origin - x, x_origin + x, y_origin - y, color);
				break;
			}

		}

	}

	fill_circle_row(x_origin - radius, x_origin + radius, y_origin , color);
}


}
// end : namespace draw

#endif
