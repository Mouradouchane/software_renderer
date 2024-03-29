
/*
	in this file there is "render" function
	a function who responsible for call all 
	the rendering stage's .
*/

#ifndef RENDER_HPP
#define RENDER_HPP

#include "../macros/macros.hpp"
#include "../types/types.hpp"
#include "../math/math.hpp"
#include "../preformance/preformance.hpp"
#include "../configs/configs.hpp"
#include "../window/window.hpp"
#include "draw.hpp"

namespace graphics {

	extern sfloat fov_deg; // filed of view "in deg" 
	extern sfloat fov; // filed of view "in rad"
	extern sfloat hfov; // half fov

	extern const sfloat max_fov; 
	extern const sfloat min_fov;

	extern sfloat aspect_ratio;

	extern cube frustum;

	// main frame buffer's
	extern buffer<scolor>* back_buffer;
	extern buffer<scolor>* front_buffer;
	extern buffer<sfloat>* depth_buffer; // z-buffer
	extern scolor clear_color;

	// bitmap & hdc for gdi
	extern BITMAP     bitmap;
	extern HBITMAP    hbitmap;
	extern HDC        bitmap_hdc;
	extern BITMAPINFO bitmap_info;

	bool init();
	void destroy();

	void to_world_space();

	vec3d orthographic_projection(vec3d& point);
	vec3d perspective_projection( vec3d& point); // + ortho
	void  projection();

	// convert point from ndc to screen space
	void to_screen_space(vec3d& point);

	// draw primitives
	void rasterization();

	// all the rendering stages called here
	void render();

}
// end : graphics namespace

#endif
