
#pragma once

#ifndef TIMER_CPP
#define TIMER_CPP

#include "timer.hpp"

/*
	=================== timer class =================== 
*/
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

/*
	===================  periodic timer class ===================
*/

periodic_timer::periodic_timer(uint32_t time_in_ms)
	: cycle_time_ms{ time_in_ms },
	  current_time{ hr_clock::now() },
	  work_time{ hr_clock::now() + cycle_time_ms }
{ }

void periodic_timer::update() {
	this->current_time = hr_clock::now();
}
bool periodic_timer::is_time_for_work() {

	if (this->current_time < this->work_time)return false;
	else {
		this->work_time = hr_clock::now() + this->cycle_time_ms;
		return true;
	}
}


#endif

