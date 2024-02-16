
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
	this->last_duration_ms = std::chrono::duration_cast<ms>(e-s).count();
	this->working = false;

	return this->last_duration_ms;
}

uint32_t timer::time_here() {
	if (this->working == false) return 0;

	this->e = hr_clock::now();   
	return this->last_duration_ms;
}

#endif
