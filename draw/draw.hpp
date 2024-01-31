
/*
	here all the rasterization function for 2d & 3d 
	shapes , probally lines and triangles :)
*/

#include "../types/types.hpp"
#include "../math/math.hpp"

#ifndef DRAW_HPP

#define DRAW_HPP

namespace draw {

	void line(line2d& line);
	void line(line3d& line);

	void triangle(triangle2d& triangle);
	void triangle(triangle3d& triangle);

/*  TODO : implement curves
	void curve(curve2d& curve);
	void curve(curve3d& curve);
*/
	
	void set_pixle(sfloat x, sfloat y, srgba& color);
	void set_sample(sfloat x, sfloat y , srgba& color);

}
// end : namespace draw

#endif