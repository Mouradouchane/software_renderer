
#pragma once

#ifndef TIMER_CPP
#define TIMER_CPP

#include "timer.hpp"

void timer::start() {
	this->working = true;
	this->s = hr_clock::now();
}

uint32_t timer::stop() {
	this->e = hr_clock::now();
	this->working = false;

	return (uint32_t)std::chrono::duration_cast<ms>(e - s).count();
}

uint32_t timer::taken_time_to_this_point() {
	if (this->working == false) return 0;
	
	this->e = hr_clock::now();   
	return (uint32_t)std::chrono::duration_cast<ms>(e - s).count();
}

#endif
