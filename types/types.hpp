
/*
	==============================
	all the types defined here
	==============================
*/

#pragma once 

#ifndef TYPES_HPP
#define TYPES_HPP

#ifndef EXTERNAL_HEADERS_TYPES
#define EXTERNAL_HEADERS_TYPES

#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <initializer_list>

#include <windows.h>

#include "../macros/macros.hpp"
#endif


/*
	=================================================
	================ standard types =================
	=================================================
*/

typedef float        float32 , *ptr_float32;
typedef double       float64 , *ptr_float64;
typedef long double  float96 , *ptr_float96;

#if TARGET_ARCH == 32
	#define sfloat float32
#else 
	#define sfloat float64
#endif

typedef struct transform {
	sfloat x = 0; 
	sfloat y = 0;
	sfloat z = 0;
	
	sfloat xr = 0;
	sfloat yr = 0;
	sfloat zr = 0;
};

class matrix {

public:
	sfloat* memory = nullptr; // matrix memory as 1d
	uint16_t w = 0;
	uint16_t h = 0;
	uint32_t size = 0;

	// constructor's
	matrix(uint16_t rows_len = 1, uint16_t columns_len = 1);

	// destructor
	~matrix();

	// methods & operators
	bool set(uint16_t row, uint16_t column, sfloat value);
	sfloat get(uint16_t row , uint16_t column);

};

/*
	==========================================================
	======================== colors ==========================
	==========================================================
*/

typedef struct rgb8 {
	uint8_t r = 0; // red
	uint8_t g = 0; // green
	uint8_t b = 0; // blue
};

typedef struct rgb16 {
	uint16_t r = 0; // red
	uint16_t g = 0; // green
	uint16_t b = 0; // blue
};

typedef struct rgb32 {
	uint32_t r = 0; // red
	uint32_t g = 0; // green
	uint32_t b = 0; // blue
};

typedef struct rgba8 {
	uint8_t r = 0; // red
	uint8_t g = 0; // green
	uint8_t b = 0; // blue
	uint8_t a = UINT8_MAX; // alpha 
};

typedef struct rgba16 {
	uint16_t r = 0;    // red
	uint16_t g = 0;    // green
	uint16_t b = 0;    // blue
	uint16_t a = UINT16_MAX;  // alpha 
};

typedef struct rgba32 {
	uint32_t r = 0; // red
	uint32_t g = 0; // green
	uint32_t b = 0; // blue
	uint32_t a = UINT32_MAX; // alpha 
};

typedef struct bgr8 {
	uint8_t b = 0; // blue
	uint8_t g = 0; // green
	uint8_t r = 0; // red
};

typedef struct bgra8 {
	uint8_t b = 0; // blue
	uint8_t g = 0; // green
	uint8_t r = 0; // red
	uint8_t a = UINT8_MAX; // alpha 
};

// standard type color
typedef bgra8 scolor;

rgb8   create_rgb8  (uint8_t  red, uint8_t  green, uint8_t  blue);
rgb16  create_rgb16 (uint16_t red, uint16_t green, uint16_t blue);
rgb32  create_rgb32 (uint32_t red, uint32_t green, uint32_t blue);

rgba8  create_rgba8 (uint8_t  red, uint8_t  green, uint8_t  blue, uint8_t  alpha = UINT8_MAX);
rgba16 create_rgba16(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha = UINT16_MAX);
rgba32 create_rgba32(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha = UINT32_MAX);

bgr8   create_bgr8 (uint8_t red, uint8_t green, uint8_t blue);
bgra8  create_bgra8(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = UINT8_MAX);

bgra8  random_bgra8 (bool random_alpha = false);
scolor random_scolor(bool random_alpha = false);

/*
	===================================================
	==================== vector's =====================
	===================================================
*/

typedef struct vec2d {
	sfloat x = 0;
	sfloat y = 0;
};

typedef struct vec3d {
	sfloat x = 0;
	sfloat y = 0;
	sfloat z = 1;
	sfloat w = 1;
}; 

typedef struct frustum {
	sfloat n = 0;
	sfloat f = 0;
	sfloat l = 0;
	sfloat r = 0;
	sfloat t = 0;
	sfloat b = 0;
};

vec2d create_vec2d(sfloat x=0, sfloat y=0);
vec3d create_vec3d(sfloat x=0, sfloat y=0, sfloat z=1, sfloat w=1);


/*
	=================================================
	=================== buffers =====================
	=================================================
*/

template<typename type> class buffer {

public:

	uint16_t x = 0;
	uint16_t y = 0;

	uint16_t height = 1;
	uint16_t width  = 1;

	uint32_t size = 0;
	type*  memory = nullptr;


	// constructor's

	buffer(
		uint16_t x = 0, uint16_t y = 0,
		uint16_t width = 1, uint16_t height = 1
	) {

		this->x = x;
		this->y = y;

		this->height = height;
		this->width  = width;

		this->size = width * height;

		this->memory = new type[this->size];

	}

	// destructor
	~buffer() {

		if (this->memory != nullptr) {
			delete[] this->memory;
			this->memory = nullptr;
		}

	}

	void set(uint16_t X, uint16_t Y, type const& new_value) {
		this->memory[width * Y + X] = new_value;
	}

	type get(uint16_t X, uint16_t Y) {
		return this->memory[width * Y + X];
	}

	void fill(type& value) {

		uint32_t Y = 0;
		for (uint16_t y = 0; y < this->height; y += 1) {
			Y = this->width * y;
			for (uint16_t x = 0; x < this->width; x += 1) {
				this->memory[Y + x] = value;
			}
		}
		// memset(this->memory, value, this->size * sizeof(type));
	}

	/* be carefull ! */
	type& operator[] (uint32_t direct_index) {
		return this->memory[direct_index];
	}

};

// 2d sample
template<typename type> struct sample {
	sfloat x = 0;
	sfloat y = 0;
	type   value;
};

/*
	=================================================
	====================== lines ====================
	=================================================
*/

class line2d {

public:
	vec2d points[2];

	// constructor's
	line2d();
	line2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2  // point 2
	);
	line2d(vec2d const& point_1, vec2d const& point_2);

	// destructor
	~line2d() = default;

};
// end : class line2d 

class line3d {

public:
	vec3d points[2];

	// constructor's
	line3d();
	line3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2  // point 2
	);
	line3d(
		vec3d const& point_1, vec3d const& point_2
	);

	// destructor
	~line3d() = default;

};
// end : class line3d

/*
	===================================================
	====================== triangles ==================
	===================================================
*/

class triangle2d {

public:

	vec2d points[3];

	// constructor's
	triangle2d();

	triangle2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2, // point 2  
		sfloat x3, sfloat y3  // point 3
	);

	triangle2d(
		vec2d const& point_1,
		vec2d const& point_2,
		vec2d const& point_3
	);

	// destructor
	~triangle2d() = default;

};
// end : class triangle2d

class triangle3d {

public:

	vec3d points[3];

	// constructor's
	triangle3d();

	triangle3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2, // point 2
		sfloat x3, sfloat y3, sfloat z3  // point 3
	);

	triangle3d(
		vec3d const& point_1,
		vec3d const& point_2,
		vec3d const& point_3
	);

	// destructor
	~triangle3d() = default;

};
// end : class triangle3d

typedef struct indxs{
	uint32_t v  = NULL;
	uint32_t vt = NULL;
	uint32_t n  = NULL;
};

class face3 { // triangle face

public:
	indxs a = { NULL };
	indxs b = { NULL };
	indxs c = { NULL };

	// constructor's
	face3() = default;
	face3(indxs const& a, indxs const& b, indxs const& c);
	
	// destructor
	~face3() = default;

	// operators
	indxs& operator[](char vertex_name);
	indxs& operator[](uint8_t vertex_index);

};

class face4 : public face3 { // quad face

public:
	indxs d = { NULL };

	face4() = default;
	face4(
		indxs const& vertex_a, indxs const& vertex_b, 
		indxs const& vertex_c, indxs const& vertex_d
	);

	~face4() = default;

	indxs& operator[](char vertex_name);
	indxs& operator[](uint8_t vertex_index);

};

// textuer coordinates 2d texture
typedef struct vec_uv {
	sfloat u = 0;
	sfloat v = 0;
};

// textuer coordinates 3d texture
typedef struct vec_uvw {
	sfloat u = 0;
	sfloat v = 0;
	sfloat w = 0;
};

/*
	===========================================
	=================== mesh ==================
	===========================================
*/
class mesh {

public:
	// vertices
	std::vector<vec3d>  v;

	// faces
	std::vector<face3>  f;

	// normals
	std::vector<vec3d>  n;

	// texture coordinates
	std::vector<vec_uv> vt;

	// for testing only
	std::vector<scolor> c;

	// constructor's
	mesh() = default;

	mesh(
		std::vector<vec3d>& vertices
	);

	mesh(
		std::vector<vec3d>& vertices,
		std::vector<face3>& faces
	);

	mesh(
		std::vector<vec3d>& vertices,
		std::vector<face3>& faces,
		std::vector<vec3d>& normals
	);

	mesh(
		std::vector<vec3d>& vertices, 
		std::vector<face3>& faces,
		std::vector<vec3d>& normals, 
		std::vector<vec_uv>& texture_coordinates
	);

	// destructor
	~mesh();

	// static function
	static void move_mesh(mesh* source, mesh* destination);
	static void copy_mesh(mesh* source, mesh* destination);

};


/*
	=================================================
	============= time/chrono types =================
	=================================================
*/

typedef std::chrono::high_resolution_clock hr_clock;
typedef std::chrono::system_clock sys_clock;
typedef std::chrono::steady_clock steady_clock;

typedef std::chrono::milliseconds ms;
typedef std::chrono::seconds sec;

typedef hr_clock::time_point     hr_time_point;
typedef sys_clock::time_point    sc_time_point;
typedef steady_clock::time_point st_time_point;

typedef std::chrono::duration<sfloat,ms>   sfloat_duration;
typedef std::chrono::duration<uint32_t,ms> uint32_t_duration;

#endif
