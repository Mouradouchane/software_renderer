
/*
	all the needed includes for main.cpp
*/

#pragma once 

#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#ifndef UNICODE
#define UNICODE
#endif

#ifndef MUTEX_H
#define MUTEX_H
	#include <mutex>
#endif

#ifndef THREAD_H
#define THREAD_H
	#include <thread>
#endif

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <windows.h>
#endif

#ifndef STRING_H
#define STRING_H
	#include <string>
#endif

#include "types/types.hpp"
#include "timer/timer.hpp"
#include "configs/configs.hpp"
#include "preformance/preformance.hpp"
#include "window/window.hpp"
#include "render/render.hpp"

#endif