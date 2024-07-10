
#pragma once

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#ifndef UNICODE
	#define UNICODE
#endif

#include <string>
#include <windows.h>
	
std::string get_last_error_window();

void show_error(std::string const& title, std::string const& message , bool sound = true);

void  show_warn(std::string const& title, std::string const& message , bool sound = true);

#endif