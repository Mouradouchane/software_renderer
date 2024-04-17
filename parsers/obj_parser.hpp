
#pragma once 

#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include "../types/types.hpp"
#include "../files/s_files.hpp"

namespace parser {

// function to generate mesh from "wavefront obj"
// https://en.wikipedia.org/wiki/Wavefront_.obj_file
mesh* obj(char* obj_data, uint32_t size);

}
// end of namespace parser

// function to generate mesh from any of the supported 3d file format  
mesh* create_mesh(char* model_data, uint8_t model_format, uint32_t data_size);

#endif
