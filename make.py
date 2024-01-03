
# make.py compiler action action_args

import os
import sys
import platform
import subprocess

class folder :
    def __init__(self, folder_name , folder_files = [] ):
        self.folder = folder_name
        self.files  = folder_files

def check_file( file_name ):

    if not ( os.path.exists(file_name ) ) :
        print( error , f"file {file_name} not found !" )
        return 0
    else : 
        return 1

def check_files( files_names ):

    for file_name in files_names :
       if( check_file( file_name ) == 0 ) :
           return 0

    return 1

def check_folder( folder_path ) :
       
    if not ( os.path.exists(folder_path) ) :
        print( error , f"folder {folder_path} not found !" )
        return 0
    else :
        return 1
    


def build( ) :
    
    if ( check_file("main.cpp") == 0 ) :
        return 0

    if( check_folder( window.folder ) == 0 or check_files( window.files ) == 0) :
        return 0


    if( check_folder( math.folder ) == 0 or check_files( math.files ) == 0) :
        return 0

    if not ( os.path.exists("build") ) :
        os.mkdir("build")
    

    try :

        if( subprocess.Popen([compiler , f"{os.path.abspath( os.getcwd() )}\main.cpp" + " -c " ]) == 0 ) :
            print(f"compiling using { compiler } for { platform.processor() }")    



    except FileNotFoundError as err:
        
        print( error , f"compiler {compiler} not found in your computer !" )
        return 1

    
    return 0


def rebuild( ) :
    pass

def clean( ) :
    pass 

def help( ) : 
    pass



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
    compiler    = sys.argv[1] if( len(sys.argv)-1 >= 1 ) else "gcc"
    action      = sys.argv[2] if( len(sys.argv)-1 >= 2 ) else "help"
    action_args = sys.argv[3] if( len(sys.argv)-1 >= 3 ) else " "

math   = folder( "math"   , ["math/math.hpp" , "math/math.cpp"] )
window = folder( "window" , ["window/window.hpp" , "window/window.cpp"] )

def main( ) : 

    if( action ==  "build" ) : 
        build( )
        return 0

    if( action == "rebuild") : 
        rebuild( )
        return 0

    if( action == "clean" ) : 
        clean( )
        return 0

    if( action == "help" ): 
        help( )
        return 0

    return 0


main()

