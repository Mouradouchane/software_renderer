
/*
	all the needed includes for main.cpp
*/

#pragma once 

#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#ifndef UNICODE
#define UNICODE
#endif

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <windows.h>
#endif

#ifndef TIME_H
#define TIME_H
	#include <time.h>
#endif

#ifndef CHRONO_H
#define CHRONO_H
	#include <chrono>
#endif

#include "configs/configs.hpp"
#include "types/types.hpp"
#include "window/window.hpp"
#include "render/render.hpp"

#endif