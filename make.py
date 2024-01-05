
#############################################
#
# this file act like Makefile to build the project
# usage example : python make.py action compiler_name
#
#############################################

import os
import sys
import platform
import subprocess
import shutil

# just a structer to hold "folder name" and target files inside it
class folder :
    def __init__(self, folder_name , folder_files = [] ):
        self.folder = folder_name
        self.files  = folder_files
#######################


# to check if file exist
def is_file_exist( file_name ):

    if not ( os.path.exists(file_name ) ) :
        print( error , f"file {file_name} not found !" )
        return 0
    else : 
        return 1
#######################

# to check multiple files if exist in the same place
def is_files_exist( files_names ):

    for file_name in files_names :
       if( is_file_exist( file_name ) == 0 ) :
           return 0

    return 1
#######################

# to check if folder is exist
def is_folder_exist( folder_path ) :
       
    if not ( os.path.exists(folder_path) ) :
        print( error , f"folder {folder_path} not found !" )
        return 0
    else :
        return 1
#######################

def build( ) : # action
    
    if ( is_file_exist("main.cpp") == 0 ) :
        return 0

    if( is_folder_exist( window.folder ) == 0 or is_files_exist( window.files ) == 0 ) :
        return 0

    if( is_folder_exist( math.folder ) == 0 or is_files_exist( math.files ) == 0 ) :
        return 0

    if not ( os.path.exists("build") ) :
        os.mkdir("build")
    

    try : # try to compile and link the project source code

        files = [ 
            { "inp" : "main.cpp" , "out" : "build/main.o" },
            { "inp" : "window/window.cpp" , "out" : "build/window.o" } ,
        ]

        # compiling

        for file in files  :
            compiler_process = subprocess.Popen( [ compiler , file["inp"] , "-c" , "-o" , file["out"] , "-D" , "UNICODE" , "-D" , "_UNICODE"] , shell=True )
            # wait for the compiler process to done
            stream = compiler_process.communicate()[0] 
            compiler_output = compiler_process.returncode

        if( compiler_output == 0 ) : # success message
            print(f"compiling pass using { compiler } for { platform.processor() }")  
        else : 
            return 1 


        # linking

        linking_request = [ compiler ]

        for file in files  :
            linking_request.append( file["out"] )

        linking_request.append( "-o" )
        linking_request.append( "build/software_renderer.exe" )

        compiler_process = subprocess.Popen( linking_request )

        if( compiler_output == 0 ) : # success message
            print(f"linking pass using { compiler } for { platform.processor() }")    
        else :
            return 1

    except FileNotFoundError as err: 

        print( error , f"compiler {compiler} not found in your computer !" )
        return 1

    
    return 0

#######################

def clean( ) : # action

    if( is_folder_exist("build") ) :

        try: # cleaning
            shutil.rmtree("build")
            os.mkdir("build")

        except OSError as err :
            print(error , err , "while preforming cleaning !")
            return 1

    print("cleaning build outputs")

    return 0
#######################


def rebuild( ) : # action
    
    clean()
    build()

#######################

def run( ) :
    pass

#######################


def help( ) : # action

    print("")
    print("make.py file act like Makefile , you can build,clean,... the project")
    print("usage : python make.py action compiler_name args")
    
    print("")
    print("actions list : ")
    print("build   : 'compile&link' the project and put the output in 'build' folder")
    print("clean   : clean the build output")
    print("rebuild : clean and build from the project from scratch")
    
    print("")
    print("example : python make.py build g++")
    print("example : python make.py clean")
#######################


# - a few global variables 

debug=False

compiler    = None
action      = None
action_args = None

error="[BUILD ERROR]"

if( debug ) :
    compiler    = input("compiler : ")
    action      = input("action : ")
    action_args = input("args : ")

else : 
    action      = sys.argv[1] if( len(sys.argv)-1 >= 1 ) else "help"
    compiler    = sys.argv[2] if( len(sys.argv)-1 >= 2 ) else "g++"
    action_args = sys.argv[3] if( len(sys.argv)-1 >= 3 ) else " "


# out current folders and it's inside files


math   = folder( "math"   , ["math/math.hpp" , "math/math.cpp"] )
window = folder( "window" , ["window/window.hpp" , "window/window.cpp"] )


# main entry point of the build script
def main( ) : 

    if( action ==  "build" ) : 
        build( )
        return 0

    if( action == "rebuild" ) : 
        rebuild( )
        return 0

    if( action == "clean" ) : 
        clean( )
        return 0

    if( action == "help" ): 
        help( )
        return 0

    return 0
#######################


main()

