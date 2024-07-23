
/*
	in this file there is "render" function
	a function who responsible for call all 
	the rendering stage's .
*/

#pragma once 

#ifndef RENDER_HPP
#define RENDER_HPP

#include "macros.hpp"
#include "types.hpp"
#include "math.hpp"
#include "configs.hpp"
#include "preformance.hpp"
#include "window.hpp"
#include "global.hpp"

#include "draw.hpp"

namespace renderer {

	extern sfloat fov_deg; // filed of view "in deg" 
	extern sfloat fov; // filed of view "in rad"
	extern sfloat hfov; // half fov

	extern const sfloat max_fov; 
	extern const sfloat min_fov;

	extern sfloat aspect_ratio;

	extern frustum view_frustum;

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

	bool alloc_meshes_for_projection(
		std::vector<mesh*>* meshes_
	);

	bool init();
	void destroy();

	// transform meshes from "model space" to "world space"
	void to_world_space();

	void orthographic_projection();
	void perspective_projection();
	void projection();

	// move from ndc to screen space
	void to_screen_space();

	// draw models
	void rasterization();

	// all of the rendering stages happend here 
	// take a look in function code in render.cpp for deatils
	void render();

	void rotate_mesh(
		mesh* model , 
		vec3d const& rotate_point , // point to rotate around
		vec3d const& directions // x,y,z rotation values
	);

}
// end : graphics namespace

#endif
