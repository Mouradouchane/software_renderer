

#ifndef RENDER_CPP
#define RENDER_CPP

#include "render.hpp"
// #include "draw.cpp"

namespace graphics {

// ===== rendering configs =====
const sfloat min_fov = math::to_radian(20);
const sfloat max_fov = math::to_radian(160);

sfloat fov_deg = 100; // degree
sfloat fov  = math::to_radian(fov_deg);
sfloat hfov = 1 / std::tanf(fov / 2);

sfloat aspect_ratio = NULL;

sfloat half_screen_width  = NULL;
sfloat half_screen_height = NULL;

cube frustum = { 0 }; // view frustum variables

sfloat ortho_dx = NULL;
sfloat ortho_dy = NULL;
sfloat ortho_dz = NULL;

sfloat ortho_dxw = NULL;
sfloat ortho_dyw = NULL;
sfloat ortho_dzw = NULL;

sfloat z_factor = NULL;

sfloat far_plus_near = NULL;
sfloat far_mult_near = NULL;

sfloat perpsective_x_factor = NULL;
sfloat perspective_y_factor = NULL;

// =====================================

// ============= buffers =============
buffer<sfloat>* depth_buffer = nullptr; // z-buffer
buffer<scolor>* front_buffer = nullptr;
buffer<scolor>* back_buffer  = nullptr;

sfloat max_depth_value = -(std::numeric_limits<float>::infinity());

BITMAPINFO bitmap_info = { 0 };
BITMAP     bitmap = { 0 };
HBITMAP    hbitmap = NULL;
HDC        bitmap_hdc = NULL;

scolor clear_color = { 0,0,0,0 };

// few triangles for testing 
vec3d p1 = { 0, 0, -0.1 }, p2 = { 1, 0, -0.1 }, p3 = { 0, 1, -0.1 }, p4 = { 1, 1, -0.1 };
vec3d p5 = { 0, 0, -1 }, p6 = { 1, 0, -1 }, p7 = { 0, 1, -1 }, p8 = { 1, 1, -1 };
vec3d pivot = { 0, 0, 0,0 };

size_t trig_size = 2;
triangle3d trigs[12] = {

	triangle3d(p1,p6,p8),
	triangle3d(p2,p5,p7),
	/*
	triangle3d(p1,p2,p3),
	triangle3d(p2,p3,p4),
	*/
	triangle3d(p5,p6,p7),
	triangle3d(p6,p7,p8),

	triangle3d(p2,p5,p6),
	triangle3d(p2,p5,p1),

	triangle3d(p3,p7,p8),
	triangle3d(p3,p4,p8),

	triangle3d(p3,p4,p8),
	
	triangle3d(p1,p5,p6),
	triangle3d(p2,p7,p8),
	triangle3d(p1,p7,p5),
};
triangle3d ptrigs[12] = {};

scolor colors[12] = {
	scolor{255,0,0,255},
	scolor{0,0,255,255},
	scolor{255,0,0,255},
	scolor{255,255,0,255},

	scolor{255,0,0,255},
	scolor{255,255,0,255},
	scolor{255,0,0,255},
	scolor{255,255,0,255},

	scolor{255,0,0,255},
	scolor{255,255,0,255},
	scolor{255,0,0,255},
	scolor{255,255,0,255}
};

bool init() {

	// allocate back-buffer
	back_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (back_buffer == nullptr) {
		exceptions::show_error(
			global::error_title, "failed to allocate memory for 'back buffer' !"
		);
		return false;
	}

	// allocate front-buffer
	front_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (front_buffer == nullptr) {
		exceptions::show_error(
			global::error_title, "failed to allocate memory for 'front buffer' !"
		);
		return false;
	}

	// allocate depth-buffer
	depth_buffer = new buffer<sfloat>(
		0,0, window::width, window::height 
	);

	if (depth_buffer == nullptr) {
		exceptions::show_error(
			global::error_title, "failed to allocate memory for 'depth buffer' !"
		);
		return false;
	}

	// setup rendering variables
	half_screen_width  = (sfloat)back_buffer->width / 2;
	half_screen_height = (sfloat)back_buffer->height / 2;

	aspect_ratio = ((sfloat)window::height / (sfloat)window::width);

	frustum.l = -half_screen_width;
	frustum.r =  half_screen_width;
	frustum.b = -half_screen_height;
	frustum.t =  half_screen_height;
	frustum.n = 1;
	frustum.f = 100;

	perpsective_x_factor = frustum.n * aspect_ratio * hfov;
	perspective_y_factor = frustum.n * hfov;
	
	ortho_dx = (2 / (frustum.r - frustum.l));
	ortho_dy = (2 / (frustum.t - frustum.b));
	ortho_dz = (2 / (frustum.f - frustum.n));

	ortho_dxw = -((frustum.r + frustum.l) / (frustum.r - frustum.l));
	ortho_dyw = -((frustum.t + frustum.b) / (frustum.t - frustum.b));
	ortho_dzw = -((frustum.f + frustum.n) / (frustum.f - frustum.n));

	z_factor = (frustum.f / (frustum.f - frustum.n));

	far_plus_near =  frustum.f + frustum.n;
	far_mult_near = -(frustum.f * frustum.n);

	to_world_space();
	clear_color.a = 255;
	
	// setup bitmap stuff
	GetClientRect(window::handle, &window::rect);
	AdjustWindowRectEx(&window::rect, window::style, 0, 0);

	ZeroMemory(&(bitmap), sizeof(BITMAP));

	bitmap.bmWidth  = window::width;
	bitmap.bmHeight = window::height;
	bitmap.bmPlanes = 1;
	bitmap.bmWidthBytes = sizeof(scolor);
	bitmap.bmBitsPixel  = sizeof(scolor) * 8;
	bitmap.bmBits = back_buffer->memory;
	bitmap.bmType = 0;

	// create a window compatible hdc for frame_buffer -> bitmap 
	bitmap_hdc = CreateCompatibleDC(window::hdc);

	// just a handle to the bitmap 
	hbitmap = CreateBitmap(
		back_buffer->width,
		back_buffer->height,
		bitmap.bmPlanes,
		bitmap.bmBitsPixel,
		back_buffer->memory
	);

	SelectObject(graphics::bitmap_hdc, graphics::hbitmap);

	return true;
}

void destroy() {

	if (graphics::front_buffer != nullptr) {
		graphics::front_buffer->~buffer();
		graphics::front_buffer = nullptr;
	}

	if (graphics::back_buffer != nullptr) {
		graphics::back_buffer->~buffer();
		graphics::back_buffer  = nullptr;
	}

}

void to_world_space() {
	
	int32_t size = 6;
	int32_t x = -size/2, y = -size/2, z = -10;

	for (uint32_t t = 0; t < trig_size; t += 1) {
		for (uint32_t p = 0; p < 3; p += 1) {
			trigs[t].points[p].x = (trigs[t].points[p].x * size) + x;
			trigs[t].points[p].y = (trigs[t].points[p].y * size) + y;
			trigs[t].points[p].z = (trigs[t].points[p].z * size) + z;
		}
	}

	pivot.x = (pivot.x * size) + x;
	pivot.y = (pivot.y * size) + y;
	pivot.z = (pivot.z * size) + z;

}

/*
void transform_thread() {
	Sleep(500);

	while (global::running) {

		for (uint32_t t = 0; t < trig_size; t += 1) {
			for (uint32_t p = 0; p < 3; p += 1) {
				math::y_rotate(pivot, trigs[t].points[p], -0.1);
			}
		}

		Sleep(100);
	}

}
std::thread trans_thread(transform_thread);
*/

vec3d perspective_projection(vec3d& point) {

	vec3d new_point = {};

	// perspective transformation
	new_point.x = point.x * perpsective_x_factor; // near * aspect_ratio
	new_point.y = point.y * perspective_y_factor; // near
	new_point.w = point.z;
	new_point.z = point.z * far_plus_near + far_mult_near;

	// perspective divide
	if (new_point.w != 0) {
		new_point.x /= new_point.w;
		new_point.y /= new_point.w;
		new_point.z /= new_point.w;
	}

	// remap to 0,1 rangle
	new_point.x = (new_point.x + 1) / 2;
	new_point.y = (new_point.y + 1) / 2;

	return new_point;
}

vec3d orthographic_projection(vec3d& point){

	vec3d new_point = { 
		point.x * aspect_ratio * hfov , 
		point.y * hfov , 
		point.z , point.z
	};

	// orthographic projection
	new_point.x = new_point.x * ortho_dx + ortho_dxw;
	new_point.y = new_point.y * ortho_dy + ortho_dyw;
	new_point.z = new_point.z * ortho_dz + ortho_dzw;

	return new_point;
}

void projection() {

	if (config::projection_type == PERSPECTIVE_PROJECTION) {

		for (uint32_t t = 0; t < trig_size; t += 1) {
			for (uint32_t p = 0; p < 3; p += 1) {
				ptrigs[t].points[p] = perspective_projection(trigs[t].points[p]);
			}
		}

	}
	else { // orthographic projection

		for (uint32_t t = 0; t < trig_size; t += 1) {
			for (uint32_t p = 0; p < 3; p += 1) {
				ptrigs[t].points[p] = orthographic_projection(trigs[t].points[p]);
			}
		}

	}

}

void to_screen_space(vec3d& point) {
	/*
	point.x = (point.x + 1) * half_screen_width;
	point.y = (point.y + 1) * half_screen_height;

	point.x = point.x * back_buffer->width  + half_screen_width;
	point.y = point.y * back_buffer->height + half_screen_height;
	*/
	point.x = point.x * back_buffer->width;
	point.y = point.y * back_buffer->height;
}

void draw_fps_info() {

	global::fps_msg = "FPS : " + std::to_string(preformance::fps);

	DrawTextA(
		bitmap_hdc,
		global::fps_msg.c_str(),
		global::fps_msg.length(),
		&(global::fps_msg_rect),
		DT_LEFT
	);

	global::loop_msg = "LOOP TIME : " + std::to_string(preformance::total_taken_time) + "ms";

	DrawTextA(
		bitmap_hdc,
		global::loop_msg.c_str(),
		global::loop_msg.length(),
		&(global::loop_msg_rect),
		DT_LEFT
	);

}

void rasterization() {

	// clear buffers
	back_buffer->fill(clear_color);
	depth_buffer->fill(max_depth_value);

	// draw to buffer
	for (uint32_t t = 0; t < trig_size; t += 1) {

		draw::fill_3d_triangle_proto1(
			ptrigs[t].points[0], ptrigs[t].points[1], ptrigs[t].points[2],
			colors[t]
		);

	}

	// update bitmap buffer address
	SetBitmapBits(
		hbitmap,
		back_buffer->size * sizeof(scolor),
		back_buffer->memory
	);

	SelectObject(bitmap_hdc, hbitmap);
	 
	if(config::draw_fps_info) draw_fps_info();

	// blt buffer into screen
	BitBlt(
		window::hdc,
		0,0,

		back_buffer->width,
		back_buffer->height,

		bitmap_hdc,
		0,0,
		SRCCOPY
	);

	// swap buffers
	std::swap(front_buffer, back_buffer);
}

bool debug_transform = 0;
void render() {
	
	// transformation
	if (debug_transform) {
		for (uint32_t t = 0; t < trig_size; t += 1) {
			for (uint32_t p = 0; p < 3; p += 1) {
				trigs[t].points[p].z += 0.1;
				trigs[t].points[p].x += 0.01;
				//math::z_rotate(pivot, trigs[t].points[p], -0.01);
				//math::y_rotate(pivot, trigs[t].points[p], -0.02);
				//math::x_rotate(pivot, trigs[t].points[p], 0.02);
			}
		}
		//pivot.z -= 0.01;
	}

	projection();

	for (uint32_t t = 0; t < trig_size; t += 1) {
		for (uint32_t p = 0; p < 3; p += 1) {
			to_screen_space(ptrigs[t].points[p]);
		}
	}

	// draw objects
	rasterization();

}

}

#endif
