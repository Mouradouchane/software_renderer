
/*
	here all the function for drawing 2d ,3d 
*/

#ifndef DRAW_HPP
#define DRAW_HPP

/*
	here all the function for drawing 2d ,3d
*/
namespace draw {

	void sort_by_y(
		vec3d& p1, vec3d& p2, vec3d& p3, bool bysmaller = true
	);

	scolor blend(
		scolor& back_color, scolor& front_color
	);

	void set_pixel(
		uint16_t x, uint16_t y, scolor& color
	);

	bool top_left_rule(vec3d& a, vec3d& b);

	/*
		draw line functions
	*/
	void draw_line(vec3d& p1, vec3d& p2, scolor color);
	
	void draw_horizontal_line(vec3d& p1, vec3d& p2, scolor& color);
	void draw_vertical_line(vec3d& p1, vec3d& p2, scolor& color);
	
	void draw_line_over_x(vec3d& p1, vec3d& p2, sfloat slope, scolor& color);
	void draw_line_over_y(vec3d& p1, vec3d& p2, sfloat slope, scolor& color);

	/*
		draw circle functions
	*/
	void draw_point(vec3d& point, uint16_t radius, scolor& color);

	/*
		draw triangle functions
	*/
	void draw_triangle(vec3d& p1, vec3d& p2, vec3d& p3, scolor& color);
	void fill_triangle(vec3d& p1, vec3d& p2, vec3d& p3, scolor& color);

	scolor random_scolor(bool random_alpha = true);
	bgra8  random_bgra8 (bool random_alpha = true);

	/*
		TODO : implement curves
		void draw_curve(vec2d* vertices, scolor& color);
		void draw_curve(vec3d* vertices, scolor& color);
	*/

}
// end : namespace draw

#endif

