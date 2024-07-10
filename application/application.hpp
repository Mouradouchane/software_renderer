
#pragma once 

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifndef UNICODE
#define UNICODE
#endif

#include <cstdint>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <initializer_list>

#include "../types/types.hpp"
#include "../timer/timer.hpp"
#include "../preformance/preformance.hpp"
#include "../global/global.hpp"
#include "../configs/configs.hpp"
#include "../render/render.hpp"

#include "../macros/macros.hpp"
#include "../window/window.hpp"

namespace application {
	
	uint32_t init(HINSTANCE h_instance, int n_cmd_show);

	void run();
	
	void clean();

}

#endif
