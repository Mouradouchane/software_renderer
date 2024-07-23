
#pragma once 

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifndef UNICODE
#define UNICODE
#endif

#include <cstdint>
#include <string>
#include <vector>
#include <initializer_list>
//#include <mutex>
//#include <thread>

#include "macros.hpp"
#include "global.hpp"
#include "configs.hpp"

#include "preformance.hpp"
#include "types.hpp"
#include "timer.hpp"
#include "render.hpp"
#include "window.hpp"

namespace application {
	
	uint32_t init(HINSTANCE h_instance, int n_cmd_show);

	void run();
	
	void clean();

}

#endif
