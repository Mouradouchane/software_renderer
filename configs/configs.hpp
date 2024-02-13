
/*
	here all global variables and ,
	configs namespace contains few variables 
	act like application setting
*/

#pragma once

#ifndef CONFIGS_HPP
#define CONFIGS_HPP

// namespace for all global variables
namespace global {

	extern bool running;
	extern uint16_t fps;
	extern uint16_t idle_time;

}
// end : namespace global

namespace config{
	
	extern uint16_t max_fps;


} 
// end : namespace configs

#endif
