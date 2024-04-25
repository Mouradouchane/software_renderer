

#ifndef FILES_CPP
#define FILES_CPP

#include "files.hpp"

std::vector<mesh*>* files::load_3d_models(
	std::initializer_list <std::string> const& files
){

	std::vector<mesh*>* meshes = new std::vector<mesh*>;
	file current_file;

	for (std::string const& file : files) {
		
		// load data from file
		current_file = s_files::read_from_file(file, false);

		// create mesh from loaded data
		if (current_file.buffer != nullptr){

			meshes->push_back(
				parser::obj((char*)current_file.buffer, current_file.size)
			);
			
		}
		else {
			// log warning
		}

		// free loaded data from current_file
		if (current_file.buffer != nullptr) {
			delete[] current_file.buffer;
			current_file.buffer = nullptr;
		}

	}
	
	return meshes;
}

mesh* load_3d_model(std::string const& file_path) {

	file current_file = s_files::read_from_file(file_path, false);

	return parser::obj((char*)current_file.buffer, current_file.size);
}

#endif 