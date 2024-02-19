
#pragma once 

#ifndef PREFORMANCE_CPP 
#define PREFORMANCE_CPP 

#include "preformance.hpp"
#pragma comment(lib, "winmm.lib")

namespace preformance {

	timer main_timer;

	uint32_t total_taken_time = 0;
	uint32_t render_time = 0;
	uint32_t input_time  = 0;
	uint32_t os_time     = 0;

	hr_time_point fps_update_start_time = hr_clock::now();
	hr_time_point fps_update_end_time   = hr_clock::now();

	uint16_t fps = 0;
	uint16_t frames = 0;
	uint32_t frame_time = 1000 / ((config::max_fps != 0) ? config::max_fps : 1);
	
bool init() {
	timeBeginPeriod(1); // s
	return true;
}

void join_threads() {

}

void destroy() {
	timeEndPeriod(1);
	join_threads();
}

}
// end : namespace preformance

#endif 
