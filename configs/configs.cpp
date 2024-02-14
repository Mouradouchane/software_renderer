
#pragma once 

#include "configs.hpp"

#ifndef CONFIGS_CPP
#define CONFIGS_CPP

namespace global {

	bool running = true;
	
	std::atomic<uint16_t> fps = 0;
	uint16_t frames = 0;
	float32  frame_time = 1000 / config::max_fps;
	std::string fps_msg = "FPS : \0";
	
	RECT fps_msg_rect = { 
		10,  // x
		20,  // y
		100, // w
		100  // h
	};
} 
// end : namespace global

namespace config {

	uint16_t max_fps = 30;
	std::string str_max_fps = std::to_string(max_fps);

}
// end : namespace configs

#endif