

#ifndef RENDER_CPP
#define RENDER_CPP

#include "render.hpp"

namespace renderer {

// ===== rendering configs =====
const sfloat min_fov = math::to_radian(20);
const sfloat max_fov = math::to_radian(160);

sfloat fov_deg = 100; // degree
sfloat fov  = math::to_radian(fov_deg);
sfloat hfov = 1 / std::tanf(fov / 2);

sfloat aspect_ratio = NULL;

sfloat half_screen_width  = NULL;
sfloat half_screen_height = NULL;

frustum view_frustum = { 0 }; // view frustum variables

sfloat ortho_dx = NULL;
sfloat ortho_dy = NULL;
sfloat ortho_dz = NULL;

sfloat ortho_dxw = NULL;
sfloat ortho_dyw = NULL;
sfloat ortho_dzw = NULL;

sfloat z_factor  = NULL;
sfloat zn_factor = NULL;

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

//BITMAPINFO bitmap_info = { 0 };
BITMAP     bitmap = { 0 };
HBITMAP    hbitmap = NULL;
HDC        bitmap_hdc = NULL;

scolor clear_color = { 0,0,0,0 };


mesh* model_pointer(uint32_t index) {
	
	if (g_meshes == nullptr || g_meshes->size() <= index) {
		return nullptr;
	}

	return (*g_meshes)[index];
}

mesh* pmodel_pointer(uint32_t index) {

	if (g_pmeshes == nullptr || g_pmeshes->size() <= index) {
		return nullptr;
	}

	return (*g_pmeshes)[index];
}

bool init() {

	// allocate back-buffer
	back_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (back_buffer == nullptr) {
		show_error(
			error_title, "failed to allocate memory for 'back buffer' !"
		);
		return false;
	}

	// allocate front-buffer
	front_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (front_buffer == nullptr) {
		show_error(
			error_title, "failed to allocate memory for 'front buffer' !"
		);
		return false;
	}

	// allocate depth-buffer
	depth_buffer = new buffer<sfloat>(
		0, 0, window::width, window::height
	);

	if (depth_buffer == nullptr) {
		show_error(
			error_title, "failed to allocate memory for 'depth buffer' !"
		);
		return false;
	}

	// setup rendering variables
	half_screen_width  = (sfloat)back_buffer->width / 2;
	half_screen_height = (sfloat)back_buffer->height / 2;

	aspect_ratio = ((sfloat)window::height / (sfloat)window::width);

	view_frustum.l  = -1;
	view_frustum.r  =  1;
	view_frustum.b  = -1;
	view_frustum.t  =  1;
	view_frustum.n  = -1;
	view_frustum.f  = -50;

	perpsective_x_factor = view_frustum.n * aspect_ratio * hfov;
	perspective_y_factor = view_frustum.n * hfov;

	ortho_dx = (2 / (view_frustum.r - view_frustum.l));
	ortho_dy = (2 / (view_frustum.t - view_frustum.b));
	ortho_dz = (2 / (view_frustum.f - view_frustum.n));

	ortho_dxw = -((view_frustum.r + view_frustum.l) / (view_frustum.r - view_frustum.l));
	ortho_dyw = -((view_frustum.t + view_frustum.b) / (view_frustum.t - view_frustum.b));
	ortho_dzw = -((view_frustum.f + view_frustum.n) / (view_frustum.f - view_frustum.n));

	z_factor  = (view_frustum.f / (view_frustum.f - view_frustum.n));
	zn_factor = -z_factor * view_frustum.n;

	far_plus_near = view_frustum.f + view_frustum.n;
	far_mult_near = -(view_frustum.f * view_frustum.n);

	// TODO : load models
	to_world_space(model_pointer(0), { 0,-0.2,-5 }, { 0,0,0 });
	to_world_space(model_pointer(1), { 0,0,-12 }, { 0,0,0 });

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

	SelectObject(renderer::bitmap_hdc, renderer::hbitmap);

	return true;
}

void destroy() {

	if (renderer::front_buffer != nullptr) {
		renderer::front_buffer->~buffer();
		renderer::front_buffer = nullptr;
	}

	if (renderer::back_buffer != nullptr) {
		renderer::back_buffer->~buffer();
		renderer::back_buffer  = nullptr;
	}

}

// NOTE : copy only vertices , normals , indeces
int8_t copy_mesh(uint32_t index) {

	mesh*  model = model_pointer(index);

	if (model == nullptr) {
		return INVALID_MESH;
	}

	// try to delete old copy "cleaning"
	if ((*g_pmeshes)[index] != nullptr) {
		delete ((*g_pmeshes)[index]);
	}
	
	(*g_pmeshes)[index] = new mesh();
	mesh* pmodel = pmodel_pointer(index);

	if (pmodel != nullptr) {

		// coping process
		pmodel->vertices = model->vertices;
		pmodel->normals  = model->normals;
		pmodel->indeces  = model->indeces;

		return COPY_MESH_SUCCESSED;
	}

	return COPY_MESHES_FAILED;
}

int8_t copy_meshes_for_rendering() {

	for (uint32_t i = 0; i < g_meshes->size(); i++) {

		if (copy_mesh(i) != COPY_MESH_SUCCESSED) {

			return COPY_MESHES_FAILED;
		}

	}

	return COPY_MESHES_SUCCESSED;
}

// TODO : implement rotate_by
void to_world_space(
	mesh* model , vec3d const& move_by , vec3d const& rotate_by 
) {
	
	if (model != nullptr) {
		
		model->pivot.x += move_by.x;
		model->pivot.y += move_by.y;
		model->pivot.z += move_by.z;

		for (vec3d& vertex : model->vertices) {
			vertex.x += move_by.x;
			vertex.y += move_by.y;
			vertex.z += move_by.z;
		}

	}

}

// TODO : implement camera
void to_camera_space() {
	

}

void perspective_projection() {

	if (g_pmeshes != nullptr) {
		
		for (mesh* pmodel : *g_pmeshes) {

			for (vec3d& vertex : pmodel->vertices) {

				// perspective transformation
				vertex.x = vertex.x * perpsective_x_factor;
				vertex.y = vertex.y * perspective_y_factor;
				vertex.w = vertex.z;
				vertex.z = vertex.z * z_factor + zn_factor;

				// perspective divide "go to NDC"
				if (vertex.w != 0) {
					vertex.x /= -vertex.w;
					vertex.y /= -vertex.w;
					vertex.z /= -vertex.w;
				}

			}

		}

	}

}

// todo : add orthographic projection
void orthographic_projection( ) {
	/*
	vec3d new_point = { 
		point.x * aspect_ratio * hfov , 
		point.y * hfov , 
		point.z , point.z
	};

	// orthographic projection
	new_point.x = new_point.x * ortho_dx + ortho_dxw;
	new_point.y = new_point.y * ortho_dy + ortho_dyw;
	new_point.z = new_point.z * ortho_dz + ortho_dzw;
	*/
}

void projection() {

	if (config::projection_type == PERSPECTIVE_PROJECTION) {

		perspective_projection();
	}
	else { 

		orthographic_projection();
	}

}

void to_screen_space(){

/*
// remap to 0,1 rangle 
point.x = ((point.x + 1) / 2).x * back_buffer->width;
point.y = ((point.y + 1) / 2).y * back_buffer->height;
*/

if (g_pmeshes != nullptr) {

	for (mesh* pmodel : *g_pmeshes) {

		for (vec3d& vertex : pmodel->vertices) {
			// x = x * w + (w/2);
			vertex.x = vertex.x * back_buffer->width + half_screen_width;
			vertex.y = vertex.y * back_buffer->height + half_screen_height;
		}

	}

}

}

void draw_fps_info() {

	fps_msg = "FPS : " + std::to_string(fps);

	DrawTextA(
		bitmap_hdc,
		fps_msg.c_str(),
		fps_msg.length(),
		&(fps_msg_rect),
		DT_LEFT
	);

	loop_msg = "LOOP TIME : " + std::to_string(total_taken_time) + "ms";

	DrawTextA(
		bitmap_hdc,
		loop_msg.c_str(),
		loop_msg.length(),
		&(loop_msg_rect),
		DT_LEFT
	);

}

void rasterization() {

	// clear buffers
	back_buffer->fill(clear_color);
	depth_buffer->fill(max_depth_value);

	// draw to buffer
	if (g_pmeshes != nullptr) {

		for (mesh* pmodel : *g_pmeshes) {

			for (vec3d& vertex : pmodel->vertices) {

				draw::fill_circle(vertex.x, vertex.y, 1, { 255,0,255,255 });
			}

		}

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
		0, 0,

		back_buffer->width,
		back_buffer->height,

		bitmap_hdc,
		0, 0,
		SRCCOPY
	);

	// swap buffers
	std::swap(front_buffer, back_buffer);
}

bool interval_transform_test = true;
void render() {
	
	// transform models
	if (interval_transform_test) {

		if (g_meshes->size() != 0) {
			rotate_mesh(
				*(g_meshes->begin()), (*g_meshes->begin())->pivot , vec3d{ -0.00,0.01,0.0 }
			);
		}

	}

	// some transformation in world space
	
	// copy meshes for rendering
	if (copy_meshes_for_rendering() != COPY_MESHES_SUCCESSED) {

		// force stop something went wrong
		g_running = false;
		return;
	}

	// camera transforamtion
	
	// culling stage 
	
	// projection stage 
	projection();

	// clipping stage 
	
	// move projected models to screen space
	to_screen_space();

	// rendering stage
	rasterization();

	// delete copies

}

void rotate_mesh(
	mesh* model,
	vec3d const& rotate_point, // point to rotate around
	vec3d const& directions    // x,y,z rotation values
){

	for (uint32_t v = 0; v < model->vertices.size(); v++) {

		math::x_rotate(rotate_point, model->vertices[v], directions.x);
		math::y_rotate(rotate_point, model->vertices[v], directions.y);
		math::z_rotate(rotate_point, model->vertices[v], directions.z);

	}

}

}
// end of namespace "render"

#endif
