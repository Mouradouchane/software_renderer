
#pragma once 

#ifndef PREFORMANCE_CPP 
#define PREFORMANCE_CPP 

#include "preformance.hpp"

namespace preformance {

	timer main_timer;

	uint32_t taken_time  = 0;
	uint32_t render_time = 0;
	uint32_t input_time  = 0; 
	uint32_t os_time     = 0;  

	uint16_t   total_fps = 0;
	std::mutex total_fps_guard;

	uint16_t frames_counter = 0;
	float32  frame_time = 1000 / ((config::max_fps != 0) ? config::max_fps : 1);
	
	std::thread total_fps_update_thread;

void total_fps_updater() {
	/*
	static ms time_to_sleep(1000);
	std::this_thread::sleep_for(time_to_sleep);

	while (global::running && config::draw_fps_info) {

		if ( total_fps_guard.try_lock() ) {
			total_fps = frames_counter;
			frames_counter = 0;

			total_fps_guard.unlock();
		}

		std::this_thread::sleep_for(time_to_sleep);
	}
	*/
}

bool init() {

	try {
		total_fps_update_thread = std::thread(total_fps_updater);
		return true;
	}
	catch (std::exception& err) {
		return false;
	}

}

void join_threads() {

	if ( total_fps_update_thread.joinable() ) {
		total_fps_update_thread.join();
	}
}

void destroy() {

	join_threads();
}

}
// end : namespace preformance

#endif 
