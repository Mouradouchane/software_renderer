
#pragma once 

#include "configs.hpp"

#ifndef CONFIGS_CPP
#define CONFIGS_CPP

namespace global {

	bool running = true;

	std::string error_title = "SR - error";
	std::string warn_title  = "SR - warning";
	std::string info_title  = "SR - info";

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
		100, // h
	};

}
// end : namespace global

namespace config {

	uint16_t max_fps = 30;
	std::string max_fps_str = std::to_string(max_fps);
	
	bool draw_fps_info = true;
	uint8_t projection_type = PERSPECTIVE_PROJECTION;
	uint8_t rendering_style = WIRE_FRAME;

	bool   draw_vertices  = true;
	scolor vertices_color = {  0,255,255,255};
	scolor wire_color     = {255,255,255,255};

}
// end : namespace configs

#endif