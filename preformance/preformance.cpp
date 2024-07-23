
#pragma once 

#ifndef PREFORMANCE_CPP 
#define PREFORMANCE_CPP 

#include "preformance.hpp"

namespace preformance {

	bool init() {
		timeBeginPeriod(1); // s
		return true;
	}

	// TODO 
	void join_threads() {

	}

	void destroy() {
		timeEndPeriod(1);
		join_threads();
	}

}
// end : namespace preformance

#endif 
