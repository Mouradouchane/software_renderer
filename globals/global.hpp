
/*

	all the global "variables / functions" should be here
	
*/

#pragma once

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <string>
#include <windows.h>

#include "types.hpp"
#include "timer.hpp"
#include "configs.hpp"

/*
	=================================
          	global variables
	=================================
*/ 

extern std::vector<mesh*>* g_meshes;
extern std::vector<mesh*>* g_pmeshes; // projected meshes

extern bool g_running;

extern std::string g_models_path;
extern std::initializer_list<std::string> g_obj_files_list;

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

extern std::string error_title;
extern std::string warn_title;
extern std::string info_title;

extern std::string fps_msg;
extern RECT		   fps_msg_rect;

extern std::string loop_msg;
extern RECT		   loop_msg_rect;


/*
	=================================
			global functions
	=================================
*/

std::string get_last_error_window();

void show_error(std::string const& title, std::string const& message, bool sound = true);

void show_warn(std::string const& title, std::string const& message, bool sound = true);

#endif
