
/*
	==============================
      all the types defined here
	==============================
*/

#pragma once 

#ifndef TYPES_HPP
#define TYPES_HPP

#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <initializer_list>

#include <windows.h>

#include "../macros/macros.hpp"

/*
	========================================
	================ types =================
	========================================
*/

// FLOATS
typedef float        float32 , *ptr_float32;
typedef double       float64 , *ptr_float64;
typedef long double  float96 , *ptr_float96;

#if TARGET_ARCH == 32
	#define sfloat float32
#else 
	#define sfloat float64
#endif

// COLORS
typedef struct rgb8  { uint8_t r = 0; uint8_t g = 0; uint8_t b = 0; };
typedef struct bgr8  { uint8_t b = 0; uint8_t g = 0; uint8_t r = 0; };
typedef struct rgba8 { uint8_t r = 0; uint8_t g = 0; uint8_t b = 0; uint8_t a = UINT8_MAX; };
typedef struct bgra8 { uint8_t b = 0; uint8_t g = 0; uint8_t r = 0; uint8_t a = UINT8_MAX; };
typedef bgra8 scolor;

// VECTORS
typedef struct vec2d { sfloat x = 0; sfloat y = 0; };
typedef struct vec3d { sfloat x = 0; sfloat y = 0; sfloat z = 0; sfloat w = 1};
typedef struct vec4d { sfloat x = 0; sfloat y = 0; sfloat z = 0; sfloat w = 1; };

// textuer coordinates 
typedef struct vec_uv { sfloat u = 0; sfloat v = 0; }; // 2D
typedef struct vec_uvw{ sfloat u = 0; sfloat v = 0; sfloat w = 0; }; // 3D

typedef struct indxs {
	uint32_t v  = NULL; // vectex index
	uint32_t vt = NULL; // textuer-coord index
	uint32_t n  = NULL; // normal index
};

// 3D frustum
typedef struct frustum {
	sfloat n = 0; sfloat f = 0; 
	sfloat l = 0; sfloat r = 0; 
	sfloat t = 0; sfloat b = 0;
};

// BUFFERS
template<typename type> class buffer;

// TIME
typedef std::chrono::high_resolution_clock hr_clock;
typedef std::chrono::system_clock sys_clock;
typedef std::chrono::steady_clock steady_clock;

typedef std::chrono::milliseconds ms;
typedef std::chrono::seconds sec;

typedef hr_clock::time_point     hr_time_point;
typedef sys_clock::time_point    sc_time_point;
typedef steady_clock::time_point st_time_point;

typedef std::chrono::duration<sfloat, ms>   sfloat_duration;
typedef std::chrono::duration<uint32_t, ms> uint32_t_duration;

/*
	===================================================
	===================================================
	===================================================
*/


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
	===========================================
	============= few methods =================
	===========================================
*/

rgb8  create_rgb8(uint8_t  red, uint8_t  green, uint8_t  blue);
rgba8 create_rgba8(uint8_t  red, uint8_t  green, uint8_t  blue, uint8_t  alpha = UINT8_MAX);

bgr8  create_bgr8(uint8_t red, uint8_t green, uint8_t blue);
bgra8 create_bgra8(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = UINT8_MAX);

vec2d create_vec2d(sfloat x = 0, sfloat y = 0);
vec3d create_vec3d(sfloat x = 0, sfloat y = 0, sfloat z = 1, sfloat w = 1);

bgra8  random_bgra8(bool random_alpha = false);
scolor random_scolor(bool random_alpha = false);

#endif
