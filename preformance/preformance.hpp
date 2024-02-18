
/*
	here all the functions/threads/variables related to 
	calculating preformance and doing work related to 
	preformance .
*/

#pragma once 

#ifndef PREFORMANCE_HPP 
#define PREFORMANCE_HPP 

#include "../types/types.hpp"
#include "../configs/configs.hpp"
#include "../timer/timer.hpp"

namespace preformance {

	extern timer main_timer;

	extern uint32_t taken_time; // total taken time by all
	extern uint32_t render_time; // rendering time
	extern uint32_t input_time; // os handling inputs time
	extern uint32_t os_time;    // os proc time

	// note ! "total_fps" is shared between threads
	extern uint16_t   total_fps;
	extern std::mutex total_fps_guard; 

	extern uint16_t frames_counter;
	extern float32  frame_time;

	// thread for updating "total_fps" each 1000ms
	extern std::thread total_fps_update_thread;
	void total_fps_updater();

	// setup threads/values/...
	bool init();

	void destroy();

	// to join all the threads create here
	void join_threads();
}
// end : namespace preformance 

#endif
