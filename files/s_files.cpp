
#ifndef S_FILES_LIB_CPP
#define S_FILES_LIB_CPP

#include "s_files.hpp"

uint32_t get_file_size(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    uint32_t sz= uint32_t(ftell(fp));
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

file s_files::read_from_file( 
    std::string const& file_path , bool read_as_binary 
){
    
    file file_object = {0};

    // try to open target file
    std::FILE* handle = nullptr; 
    handle = fopen(file_path.c_str() , ((read_as_binary) ? "rb" : "r"));

    // copy file data to buffer
    if(handle != nullptr) {
    
        file_object.size = uint32_t(get_file_size(handle));
        file_object.buffer = (void*)(new uint8_t[file_object.size]);

        uint32_t readed = fread(file_object.buffer, 1/*byte*/, file_object.size, handle);

        // close file after copying
        fclose(handle);
    }

    return file_object;
}

bool s_files::write_to_file(
    std::string const& file_path, void* buffer, uint32_t size, bool append
){
    
    // try to open file
    std::FILE* handle = nullptr;
    handle = fopen(file_path.c_str() , (append ? "a" : "w") );

    // try to write to file
    if(handle != nullptr) {
        // fwrite( const void* buffer, std::size_t size, std::size_t count, std::FILE* stream );
        size_t write_result = NULL;
        write_result = fwrite(buffer , 1 , size , handle);
        
        // close file after writing
        fclose(handle);
    
        return (write_result != NULL);
    }
    
    return false;
}

bool s_files::write_to_file(
    std::FILE* file_pointer, void* buffer, uint32_t size, bool append
){
    
    // try to write to file
    if(file_pointer != nullptr) {
        size_t write_result = NULL;
        write_result = fwrite(buffer , 1 , size , file_pointer);
        
        return (write_result != NULL);
    }
    
    return false;
}


std::FILE* s_files::open_file(std::string const& file_path , std::string const& permission){
     
    // try to open file
    std::FILE* handle = nullptr; 
    handle = fopen(file_path.c_str() , permission.c_str());

    return handle;
}

std::FILE* s_files::create_file(std::string const& file_path ){
     
    // try to open file
    std::FILE* handle = nullptr; 
    handle = fopen(file_path.c_str() , "w");

    return handle;
}

bool s_files::delete_file(std::string const& file_path){
    // int remove(const char *filename)
   return (remove(file_path.c_str()) == 0);
}

#endif
