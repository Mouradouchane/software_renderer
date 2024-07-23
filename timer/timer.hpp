
#pragma once 

#ifndef TIMER_HPP
#define TIMER_HPP

#include "types.hpp"

// normal timer to calc taken time .
class timer {

private :

	bool working = false;

	hr_time_point s; // start time
	hr_time_point e; // end time

	uint32_t taken_time; // taken time between s -> e

public :

	 timer() = default;
	~timer() = default;

	// method's
	void start();
	uint32_t stop();
	uint32_t taken_time_to_this_point();

};
// end : class timer 

// spinner timer to do some work each time 
class periodic_timer {

private:
	ms cycle_time_ms = ms(1000);

	hr_time_point current_time = hr_clock::now();
	hr_time_point work_time = hr_clock::now() + cycle_time_ms;

public: 

	// constructor's
	periodic_timer() = default;
	periodic_timer(uint32_t time_in_ms);
	
	// destructor
	~periodic_timer() = default;

	// method's
	void update();
	bool is_time_for_work();

};

#endif
