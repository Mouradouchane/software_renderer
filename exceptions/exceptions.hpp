
#pragma once

#include <string>

#ifndef UNICODE
	#define UNICODE
#endif

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <windows.h>
#endif

#ifndef EXCEPTION_HPP

#define EXCEPTION_HPP

namespace exceptions {
	
	std::string get_last_error_window();

	void show_error(std::string const& title, std::string const& message , bool sound = true);
	void show_warn (std::string const& title, std::string const& message , bool sound = true);

}

#endif