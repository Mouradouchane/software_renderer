
/*
	here all the global variables and configs
*/

#pragma once

#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <Windows.h>
#endif

#include "../macros/macros.hpp"
#include "../types/types.hpp"

// program global variables
namespace global {

	extern bool running; 

	extern std::string error_title;
	extern std::string warn_title;
	extern std::string info_title;

	extern std::string	fps_msg;
	extern RECT			fps_msg_rect;

	extern std::string  loop_msg;
	extern RECT			loop_msg_rect;

}

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
