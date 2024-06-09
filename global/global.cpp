
/*

	all the "global variables/functions" is here

*/

#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#include "global.hpp"


bool running = true;

std::vector<mesh*>*   meshes = nullptr;
std::vector<mesh*>* p_meshes = nullptr;

std::initializer_list<std::string> models_path = {
	"models/teapot.obj",
	/*
	"models/stanford-bunny.obj",
	"models/test.obj",
	*/
};

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
