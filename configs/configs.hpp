
/*
	here all global variables and ,
	configs namespace contains few variables 
	act like application setting
*/

#pragma once

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <Windows.h>
#endif

#include "../types/types.hpp"

#ifndef CONFIGS_HPP
#define CONFIGS_HPP

// namespace for all global variables
namespace global {

	extern bool running; 
	
	extern std::atomic<uint16_t> fps; // last counted fps

	extern uint16_t		frames; // frames counter
	extern float32		frame_time; // time per frame
	extern std::string	fps_msg;
	extern RECT			fps_msg_rect;

}
// end : namespace global

namespace config{
	
	extern uint16_t max_fps; // max frames per sec

} 
// end : namespace configs

#endif
