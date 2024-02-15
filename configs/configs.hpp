
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

	extern uint8_t time_bais;
	extern float32 taken_time;

	extern uint16_t   fps; // last counted fps
	extern std::mutex fps_guard;

	extern uint16_t		frames; // frames counter
	extern float32		frame_time; // time per frame
	
	extern std::string	fps_msg;
	extern RECT			fps_msg_rect;

	extern std::string  loop_msg;
	extern RECT			loop_msg_rect;

	// update fps each 1000ms
	extern std::thread fps_update_thread;
	void fps_update_worker();

}
// end : namespace global

namespace config{
	
	extern uint16_t max_fps; // max frames per sec
	extern bool draw_fps_info;

} 
// end : namespace configs

#endif
