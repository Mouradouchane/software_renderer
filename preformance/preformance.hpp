
/*
	here all the functions/threads/variables related to 
	calculating preformance and doing work related to 
	preformance .
*/

#pragma once 

#ifndef PREFORMANCE_HPP 
#define PREFORMANCE_HPP 

#ifndef WINDOW_H
#define WINDOW_H
	#include <Windows.h>
#endif

#include "../types/types.hpp"
#include "../configs/configs.hpp"
#include "../timer/timer.hpp"

namespace preformance {

	extern timer main_timer;

	extern uint32_t total_taken_time; // total taken time by all
	extern uint32_t render_time; // rendering time
	extern uint32_t input_time;  // os handling inputs time
	extern uint32_t os_time;     // os proc time

	// note : fps is a counter & not => "max fps"
	extern uint16_t fps;
	extern uint16_t frames; // frame's counter
	extern uint32_t frame_time; // needed time to compute 1 frame

	extern hr_time_point fps_update_time;
	extern hr_time_point fps_next_update_time;
	// setup threads/values/...
	bool init();

	void destroy();

	// to join all the threads create here
	void join_threads();
}
// end : namespace preformance 

#endif
