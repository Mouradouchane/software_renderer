

#ifndef RENDER_CPP
#define RENDER_CPP

#include "render.hpp"
// #include "draw.cpp"

namespace graphics {

	const sfloat min_fov = math::to_radian(20);
	const sfloat max_fov = math::to_radian(160);

	sfloat fov = math::to_radian(90);
	sfloat hfov = 1 / std::tanf(fov / 2);

	sfloat aspect_ratio = 1.0f;
	sfloat z_normalaize_factor = NULL;

	ndc ndc_space;

	buffer<scolor>* front_buffer = nullptr;
	buffer<scolor>* back_buffer = nullptr;

	BITMAPINFO bitmap_info = { 0 };
	BITMAP     bitmap = { 0 };
	HBITMAP    hbitmap = NULL;
	HDC        bitmap_hdc = NULL;

	scolor clear_color = { 0,0,0,0 };

// few triangles for testing 
triangle3d trigs[6] = {
	triangle3d(0, 0, 0,		0, 1, 0,	1, 0, 0),
	triangle3d(0, 1, 0,		1, 1, 0,	1, 0, 0),

	triangle3d(0, 0, 1,		0, 1, 1,	1, 0, 1),
	triangle3d(0, 1, 1,		1, 1, 1,	1, 0, 1),

	triangle3d(1, 0, 0,		1, 1, 0,	1, 1, 1),
	triangle3d(1, 0, 0,		1, 0, 1,	1, 1, 1),

};
triangle3d ptrigs[6] = {};

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

	transfrom_to_world_space();

	// setup rendering stuff
	clear_color.a = 255;
	aspect_ratio = ((sfloat)back_buffer->height / (sfloat)back_buffer->width);
	ndc_space = ndc{ 1,-1, -1,1, -1,1 };

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

void transfrom_to_world_space() {
	
	for (uint32_t t = 0; t < 6; t += 1) {
		for (uint32_t p = 0; p < 3; p += 1) {
			trigs[t].points[p].x = (trigs[t].points[p].x * 100) + 700;
			trigs[t].points[p].y = (trigs[t].points[p].y * 100) + 700;
			trigs[t].points[p].z = (trigs[t].points[p].z*5) - 100;
		}
	}
	
}

vec3d perspective_projection(vec3d& point) {

	// perspective transformation
	vec3d new_point{
		(point.x / point.z) * ndc_space.n ,//* hfov * aspect_ratio,
		(point.y / point.z) * ndc_space.n ,//* hfov,
		point.z * (ndc_space.f + ndc_space.n) - (ndc_space.f * ndc_space.n),
		point.z
	};

	// orthographic projection
	new_point.x = new_point.x * (2 / (ndc_space.r - ndc_space.l)) - ((ndc_space.r + ndc_space.l) / (ndc_space.r - ndc_space.l));
	new_point.y = new_point.y * (2 / (ndc_space.t - ndc_space.b)) - ((ndc_space.t + ndc_space.b) / (ndc_space.t - ndc_space.b));
	new_point.z = new_point.z * (2 / (ndc_space.f - ndc_space.n)) - ((ndc_space.f + ndc_space.n) / (ndc_space.f - ndc_space.n));

	// perspective divide
	if (new_point.w != 0) {

		new_point.x /= new_point.w;
		new_point.y /= new_point.w;
		new_point.z /= new_point.w;
	}

	return new_point;
}

void transform_thread() {

	while (global::running) {
		
		for (uint32_t t = 0; t < 6; t += 1) {
			for (uint32_t p = 0; p < 3; p += 1) {
				trigs[t].points[p].x -= 3;
				trigs[t].points[p].y -= 2;
				trigs[t].points[p].z += 0.2;
			}
		}
	
		Sleep(100);
	}

}
std::thread trans_thread(transform_thread);

void projection() {

	for (uint32_t t = 0; t < 6; t += 1) {
		for (uint32_t p = 0; p < 3; p += 1) {
			ptrigs[t].points[p] = perspective_projection(trigs[t].points[p]);
		}
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
	for (uint32_t t = 0; t < 6; t += 1) {
		draw::draw_triangle(
			ptrigs[t].points[0], ptrigs[t].points[1], ptrigs[t].points[2],
			scolor{255,255,255,255}
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

bool render() {
	
	projection();

	for (uint32_t t = 0; t < 6; t += 1) {
		for (uint32_t p = 0; p < 3; p += 1) {
			to_screen_space(ptrigs[t].points[p]);
		}
	}

	// draw objects
	rasterization();

	return true;
}

}

#endif
