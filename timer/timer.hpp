
#pragma once 

#ifndef TIMER_HPP
#define TIMER_HPP

#include "../types/types.hpp"

class timer {

private :

	bool working = false;

	hr_time_point s; // start time
	hr_time_point e; // end time

	uint32_t taken_time; // taken time between s -> e

public :

	// constructor
	timer() = default;

	// destructor
	~timer() = default;

	// method's
	void start();
	uint32_t stop();
	uint32_t taken_time_to_this_point();

};
// end : class timer 

#endif
