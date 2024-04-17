
/*
	here all the included headers
	note : used in main.cpp and few other headers
*/

#pragma once 

#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#ifndef UNICODE
	#define UNICODE
#endif

#ifndef EXTERNAL_LIBS
#define EXTERNAL_LIBS

#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <initializer_list>

#include <windows.h>

#endif

#include "types/types.hpp"
#include "timer/timer.hpp"
#include "preformance/preformance.hpp"
#include "global/global.hpp"
#include "configs/configs.hpp"
#include "window/window.hpp"
#include "render/render.hpp"
#include "files/files.hpp"

#endif