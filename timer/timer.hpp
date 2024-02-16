
#pragma once 

#ifndef TIMER_HPP
#define TIMER_HPP

#include "../types/types.hpp"

class timer {

private :

	bool working = false;
	hr_clock::time_point s; // start time
	hr_clock::time_point e; // end time
	uint32_t last_duration_ms = 0; // ellapse time in ms

public :

	// constructor
	timer() = default;

	// destructor
	~timer() = default;

	// method's
	void start();
	uint32_t stop();
	uint32_t time_here();

};
// end : class timer 

#endif
