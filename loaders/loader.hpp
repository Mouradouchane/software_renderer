
#pragma once

#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include "global.hpp"
#include "types.hpp"

namespace loader{

	int8_t load_models();

	int8_t load_obj_file(std::string const& file_name , mesh* destination);

	/*
		TODO : in futuer :)

		int8_t load_textuer_bitmap(std::string const& file_name);
		int8_t load_mtl(std::string const& file_name);
		int8_t load_png(std::string const& file_name);
		int8_t load_fbx(std::string const& file_name);
	*/
}

#endif
