
#pragma once 

#include "configs.hpp"

#ifndef CONFIGS_CPP
#define CONFIGS_CPP

namespace global {

	bool running = true;

	uint8_t time_bais = 5;//ms
	float32 taken_time = 0;

	uint16_t fps = 0;
	std::mutex fps_guard;

	uint16_t frames = 0;
	float32  frame_time = (float32)(1000 / config::max_fps);

	std::string fps_msg  = "FPS : ";
	std::string loop_msg = "LOOP TIME : ";
	
	RECT fps_msg_rect = { 
		10,  // x
		20,  // y
		400, // w
		50,  // h
	};

	RECT loop_msg_rect = {
		10,  // x
		40,  // y
		400, // w
		100,  // h
	};

	std::thread fps_update_thread;

void fps_update_worker() {

	while (global::running) {

		if (global::fps_guard.try_lock()) {
			global::fps = global::frames;
			global::frames = 0;

			global::fps_guard.unlock();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

}

}
// end : namespace global

namespace config {

	uint16_t max_fps = 20;
	bool draw_fps_info = true;
	
	std::string str_max_fps = std::to_string(max_fps);

}
// end : namespace configs

#endif