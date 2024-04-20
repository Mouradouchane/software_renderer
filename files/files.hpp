
#pragma once

#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <vector>
#include <initializer_list>
#include "../parsers/obj_parser.hpp"
#include "../types/types.hpp"
#include "s_files.hpp"

namespace files {

	/*
		function load a list of "3d models" from files
		and create meshes from them
	*/
	std::vector<mesh*>* load_3d_models(
		std::initializer_list<std::string> const& files
	);

	mesh* load_3d_model(std::string const& file_path);

}

#endif 