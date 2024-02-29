
/*
	here all the function for drawing 2d ,3d 
*/

#ifndef DRAW_HPP
#define DRAW_HPP

/*
	here all the function for drawing 2d ,3d
*/
namespace draw {

	void line(vec2d& p1, vec2d& p2, scolor& color);
	void line(vec3d& p1, vec3d& p2, scolor& color);

	void draw_horizontal_line(
		uint32_t x_start , uint32_t x_end ,
		uint32_t Y , scolor color
	);

	void draw_vertical_line(
		uint32_t y_start , uint32_t y_end,
		uint32_t X , scolor color
	);

	void draw_line_over_x(
		vec2d p1, vec2d p2,
		sfloat slope, scolor& color
	);

	void draw_line_over_y(
		vec2d p1, vec2d p2,
		sfloat slope, scolor& color
	);

	void point(
		uint32_t x, uint32_t y,
		uint16_t size , scolor& color
	);

	void draw_triangle_2d(
		vec2d p1, vec2d p2, vec2d p3,
		scolor& color
	);

	void draw_triangle(
		vec2d& p1, vec2d& p2, vec2d& p3,
		scolor& color
	);
	void draw_triangle(
		vec3d& p1, vec3d& p2, vec3d& p3,
		scolor& color
	);

	void fill_triangle_2d(
		vec2d p1, vec2d p2, vec2d p3,
		scolor& color
	);

	void fill_triangle_3d(
		vec3d p1, vec3d p2, vec3d p3,
		scolor& color
	);

	void fill_triangle(
		vec2d& p1, vec2d& p2, vec2d& p3,
		scolor& color
	);

	void set_pixel(
		uint32_t x, uint32_t y, 
		scolor& color
	);

	// blend tow colors 
	scolor blend(
		scolor& back_color,
		scolor& front_color
	);

	// TODO : move this to it's right place
	void sort_by_y(
		vec2d& p1, vec2d& p2, vec2d& p3, 
		bool bysmaller = true
	);
	void sort_by_y(
		vec3d& p1, vec3d& p2, vec3d& p3, 
		bool bysmaller = true
	);

	bool top_left_rule(vec2d& a , vec2d& b);

	/*
		TODO : implement curves
		void curve(curve2d& curve);
		void curve(curve3d& curve);
	*/

}
// end : namespace draw

#endif

