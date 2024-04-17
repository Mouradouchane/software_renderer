
/*
	here all the configs
*/

#pragma once

#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "../includes.hpp"

// program config
namespace config {

	extern uint16_t max_fps;
	extern bool draw_fps_info;

	extern uint8_t projection_type;
	extern uint8_t rendering_style;

	extern bool   draw_vertices;
	extern scolor vertices_color;
	extern scolor wire_color;

} 

#endif
