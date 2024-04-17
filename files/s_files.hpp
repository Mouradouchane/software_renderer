
#ifndef S_FILES_LIB_HPP
#define S_FILES_LIB_HPP

#include <errno.h>
#include <stdio.h>
#include <cstdio>
#include <string>

typedef struct file {
    uint32_t size = 0;
    void*  buffer = nullptr;
};

// main namesapce =============================
namespace s_files{

    file read_from_file(std::string const& file_path, bool read_as_binary);
    std::FILE* open_file(std::string const& file_path , std::string const& permission);
    
    bool write_to_file(std::string const& file_path, void* buffer, uint32_t size, bool append);
    bool write_to_file(std::FILE* file_pointer, void* buffer, uint32_t size, bool append);
    
    std::FILE* create_file(std::string const& file_path);
    bool delete_file(std::string const& file_path);

}
// s_files namespace end =====================

#endif
