
/*

	all the "global variables/functions" is here

*/

#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#include "global.hpp"
#include "configs.hpp"

// we need it for window time-api 
#pragma comment(lib, "winmm.lib")

bool g_running = true;

// TODO : move them to renderer
std::vector<mesh*>* g_meshes  = nullptr;
std::vector<mesh*>* g_pmeshes = nullptr;

std::initializer_list<std::string> meshes_paths = {
	"models/teapot.obj",
	/*
	"models/stanford-bunny.obj",
	"models/test.obj",
	*/
};

timer main_timer;

uint32_t total_taken_time = 0;
uint32_t render_time = 0;
uint32_t input_time = 0;
uint32_t os_time = 0;

hr_time_point fps_update_time = hr_clock::now();
hr_time_point fps_next_update_time = hr_clock::now();

uint16_t fps = 0;
uint16_t frames = 0;
uint32_t frame_time = 1000 / ((config::max_fps != 0) ? config::max_fps : 1);

std::string error_title = "error";
std::string warn_title  = "warning";
std::string info_title  = "info";

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

#endif
