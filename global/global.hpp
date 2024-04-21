
/*

	all the "global variables/functions" defined here
	
*/

#pragma once

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "../includes.hpp"


extern std::vector<mesh*>*   models;
extern std::vector<mesh*>* p_models; // where meshes get projected

extern std::initializer_list<std::string> models_path;

// main loop controller
extern bool running; 

extern std::string error_title;
extern std::string warn_title;
extern std::string info_title;

extern std::string fps_msg;
extern RECT		   fps_msg_rect;

extern std::string loop_msg;
extern RECT		   loop_msg_rect;


#endif