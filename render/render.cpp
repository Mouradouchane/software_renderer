

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

bool alloc_meshes_for_projection( std::vector<mesh*>* meshes_ );

bool init() {

	// allocate back-buffer
	back_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (back_buffer == nullptr) {
		exceptions::show_error(
			error_title, "failed to allocate memory for 'back buffer' !"
		);
		return false;
	}

	// allocate front-buffer
	front_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (front_buffer == nullptr) {
		exceptions::show_error(
			error_title, "failed to allocate memory for 'front buffer' !"
		);
		return false;
	}

	// allocate depth-buffer
	depth_buffer = new buffer<sfloat>(
		0, 0, window::width, window::height
	);

	if (depth_buffer == nullptr) {
		exceptions::show_error(
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

	// setup models
	meshes = files::load_3d_models(models_path);
	alloc_meshes_for_projection(meshes);

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

bool alloc_meshes_for_projection(std::vector<mesh*>* meshes_) {

	if (meshes_ == nullptr || meshes_->size() == 0) return false;

	// alloc vector for projection meshes
	p_meshes = new std::vector<mesh*>(meshes->size());
	mesh* pmodel;

	uint32_t p = 0;
	for (mesh* model : meshes[0]) {

		pmodel = new mesh(model->v,model->f,model->n,model->vt);
		pmodel->c = std::vector<scolor>(pmodel->f.size());
		
		for (uint32_t c  = 0; c < pmodel->c.size(); c++) {
			pmodel->c[c] = random_scolor();
		}
		

		*(p_meshes->begin() + p) = pmodel;
		p++;
	}

}

void to_world_space() {
	
	if (meshes != nullptr) {
		int32_t z = -9;
		float32 y = -1.5;
		
		for (uint32_t m = 0; m < meshes->size(); m++ ) {
			
			mesh* model = *(meshes->begin() + m);

			for (uint32_t i = 0; i < model->v.size(); i += 1) {
				model->v[i].z += z;
				model->v[i].y += y;
			}

		}

	}

}

void perspective_projection() {

	if (meshes != nullptr) {

		for (uint32_t m = 0; m < meshes->size(); m++) {

			mesh* model = *(meshes->begin() + m);
			mesh* pmodel = *(p_meshes->begin() + m);

			for (uint32_t i = 0; i < model->v.size(); i += 1) {

				// perspective transformation
				pmodel->v[i].x = model->v[i].x * perpsective_x_factor;
				pmodel->v[i].y = model->v[i].y * perspective_y_factor;
				pmodel->v[i].w = model->v[i].z;
				pmodel->v[i].z = model->v[i].z * z_factor + zn_factor;

				// perspective divide "go to NDC"
				if (pmodel->v[i].w != 0) {

					pmodel->v[i].x /= -pmodel->v[i].w;
					pmodel->v[i].y /= -pmodel->v[i].w;
					pmodel->v[i].z /= -pmodel->v[i].w;
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

if (p_meshes != nullptr) {

	for (uint32_t m = 0; m < p_meshes->size(); m++) {

		mesh* pmodel = *(p_meshes->begin() + m);

		for (uint32_t i = 0; i < pmodel->v.size(); i += 1){
			// x = x * w + (w/2);
			pmodel->v[i].x = pmodel->v[i].x * back_buffer->width + half_screen_width;
			pmodel->v[i].y = pmodel->v[i].y * back_buffer->height + half_screen_height;
		}

	}

}

}

void draw_fps_info() {

	fps_msg = "FPS : " + std::to_string(preformance::fps);

	DrawTextA(
		bitmap_hdc,
		fps_msg.c_str(),
		fps_msg.length(),
		&(fps_msg_rect),
		DT_LEFT
	);

	loop_msg = "LOOP TIME : " + std::to_string(preformance::total_taken_time) + "ms";

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
	for (uint32_t m = 0; m < p_meshes->size(); m++) {

		mesh* pmodel = *(p_meshes->begin() + m);
		vec3d v;

		for (uint32_t f = 0; f < pmodel->f.size(); f++ ) {

			draw::draw_line(
				pmodel->v[pmodel->f[f].a.v],
				pmodel->v[pmodel->f[f].b.v], 
				{ 255,0,255,255 }
			);
			draw::draw_line(
				pmodel->v[pmodel->f[f].a.v],
				pmodel->v[pmodel->f[f].c.v],
				{ 255,0,255,255 }
			);
			draw::draw_line(
				pmodel->v[pmodel->f[f].b.v],
				pmodel->v[pmodel->f[f].c.v],
				{ 255,0,255,255 }
			);
			/*
			v = pmodel->v[pmodel->f[f].a.v];
			draw::fill_circle(v.x, v.y, 1, scolor{ 255,255,0,255 });

			v = pmodel->v[pmodel->f[f].b.v];
			draw::fill_circle(v.x, v.y, 1, scolor{ 255,255,0,255 });
			
			v = pmodel->v[pmodel->f[f].c.v];
			draw::fill_circle(v.x, v.y, 1, scolor{ 255,255,0,255 });
			*/
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

bool interval_transform_test = false;
void render() {
	
	// transform models
	if (interval_transform_test) {
		if (meshes->size() != 0) {
			rotate_mesh(
				*(meshes->begin()), vec3d{0,0,0}, vec3d{ -0.01,0.02,0.03 }
			);
		}
	}

	// project models
	projection();

	// move projected models to screen space
	to_screen_space();

	// "draw or shade or ..." => projected models
	rasterization();

}

void rotate_mesh(
	mesh* model,
	vec3d const& rotate_point, // point to rotate around
	vec3d const& directions    // x,y,z rotation values
){

	for (uint32_t v = 0; v < model->v.size(); v++) {

		math::x_rotate(rotate_point, model->v[v], directions.x);
		math::y_rotate(rotate_point, model->v[v], directions.y);
		math::z_rotate(rotate_point, model->v[v], directions.z);

	}

}

}
// end of namespace "render"

#endif
