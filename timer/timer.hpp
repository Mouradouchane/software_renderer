
#pragma once 
#include "../types/types.hpp"

#ifndef CHRONO_H
#define CHRONO_H
	#include <chrono>
#endif

#ifndef TIMER_HPP
#define TIMER_HPP

typedef std::chrono::high_resolution_clock hr_clock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<sfloat> fsec;

class timer {

private :
	bool working = false;
	hr_clock::time_point s; // start time
	hr_clock::time_point e; // end time
	uint32_t last_duration_ms = 0; // ellapse time in ms

public:
	// constructor
	timer() = default;

	// destructor
	~timer() = default;

	// method's
	void start();
	uint32_t stop();
	uint32_t time_here();

};

#endif
