
#pragma once 

#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include "../types/types.hpp"
#include "../files/s_files.hpp"



mesh* parse_obj(char* file_data, uint32_t size);

#endif
