
/*
	here all the functions/threads/variables related to 
	calculating preformance and doing work related to 
	preformance .
*/

#pragma once 

#ifndef PREFORMANCE_HPP 
#define PREFORMANCE_HPP 

#include <Windows.h>

#include "types.hpp"
#include "configs.hpp"
#include "timer.hpp"
#include "global.hpp"


namespace preformance {

	// setup threads/values/...
	bool init();

	void destroy();

	// to join all the threads create here
	void join_threads();

}
// end : namespace preformance 

#endif
