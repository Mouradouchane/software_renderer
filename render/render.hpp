
/*
	in this file there is "render" function
	a function who responsible for call all 
	the rendering stage's .
*/

#include "../types/types.hpp"
#include "../math/math.hpp"
#include "../configs/configs.hpp"
#include "../window/window.hpp"
#include "../draw/draw.hpp"

#ifndef RENDER_HPP
#define RENDER_HPP

namespace renderer{

// main frame buffer we draw/raster in
extern buffer<rgba8>*frame_buffer;

bool init();
void destroy();

// raster generate buffer to screen buffer
bool raster();

bool render();

}

#endif
