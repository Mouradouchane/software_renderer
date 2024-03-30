
/*
	here all global variables and "configs/settings"
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

// namespace for all global variables
namespace global {

	extern std::string error_title;
	extern std::string warn_title;
	extern std::string info_title;

	extern bool running; 

	extern std::string	fps_msg;
	extern RECT			fps_msg_rect;

	extern std::string  loop_msg;
	extern RECT			loop_msg_rect;

}

namespace config {
	
	extern uint16_t max_fps; // max frames per sec
	extern bool draw_fps_info;

	extern uint8_t projection_type;
	extern uint8_t rendering_style;

} 

#endif
