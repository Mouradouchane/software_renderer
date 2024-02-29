

#ifndef RENDER_CPP
#define RENDER_CPP

#include "render.hpp"
// #include "draw.cpp"

namespace graphics {

const sfloat min_fov = math::to_radian(20);
const sfloat max_fov = math::to_radian(160);

sfloat fov = math::to_radian(90);
sfloat hfov = 1 / std::tanf(fov/2);

sfloat aspect_ratio = NULL;
sfloat z_normalaize_factor = NULL;

ndc ndc_space;

buffer<scolor>* front_buffer = nullptr;
buffer<scolor>* back_buffer  = nullptr;

BITMAPINFO bitmap_info = { 0 };
BITMAP     bitmap = { 0 };
HBITMAP    hbitmap = NULL;
HDC        bitmap_hdc = NULL;

scolor clear_color = { 0,0,0,0 };

// few triangles for testing 
triangle3d trig1(20, 40, -125, 69, 98, -125, 88, 32, -125);
triangle3d ptrig1;

bool init() {

	clear_color.a = 255;

	// setup rendering stuff
	aspect_ratio = window::height / window::width;

	ndc_space = ndc{ 1,-1, -1,1, -1,1 };

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

	GetClientRect(window::handle, &window::rect);
	AdjustWindowRectEx(&window::rect, window::style, 0, 0);

	ZeroMemory(&(bitmap), sizeof(BITMAP));

	// setup bitmap
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

vec3d perspective_projection(vec3d& point) {

	// perspective transformation
	vec3d new_point{
		(point.x * hfov * aspect_ratio) ,
		(point.y * hfov),
		point.z * (ndc_space.f + ndc_space.n) + -(ndc_space.f * ndc_space.n),
		point.z
	};

	// orthographic projection
	new_point.x = new_point.x * (2 / (ndc_space.r - ndc_space.l)) + -((ndc_space.r + ndc_space.l) / (ndc_space.r - ndc_space.l));
	new_point.y = new_point.y * (2 / (ndc_space.t - ndc_space.b)) + -((ndc_space.t + ndc_space.b) / (ndc_space.t - ndc_space.b));
	new_point.z = new_point.z * (2 / (ndc_space.f - ndc_space.n)) + -((ndc_space.f + ndc_space.n) / (ndc_space.f - ndc_space.n));

	// perspective divide
	if (new_point.w != 0) {

		new_point.x /= new_point.w;
		new_point.y /= new_point.w;
		new_point.z /= new_point.w;
	}

	return new_point;
}

void projection() {

	for (uint32_t p = 0; p < 3; p += 1) {
		ptrig1.points[p] = perspective_projection(trig1.points[p]);
	}

}

void to_screen_space(vec3d& point) {
	point.x = point.x * back_buffer->width  + (back_buffer->width/2);
	point.y = point.y * back_buffer->height + (back_buffer->height/2);
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

	// clear buffer
	back_buffer->fill(clear_color);

	// draw to buffer
	draw::draw_triangle(
		ptrig1.points[0], ptrig1.points[1], ptrig1.points[2],
		scolor{255,255,255,255}
	);

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

bool render() {
	
	projection();

	for (uint32_t p = 0; p < 3; p += 1) {
		to_screen_space(ptrig1.points[p]);
	}

	// draw objects
	rasterization();

	return true;
}

}

#endif
