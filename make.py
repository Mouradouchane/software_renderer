
import sys
import platform

# make.py action action_args

compiler="gcc"
error="[BUILD ERROR]"

def build( ) :
    
    print(f"compiling using { compiler } for { platform.processor() }")    

    return 0

def rebuild( ) :
    pass

def clean( ) :
    pass 

def help( ) : 
    pass

def main( ) :

    action = sys.argv[1]

    if( action ==  "build" ) : 
        build( )

    if( action == "rebuild") : 
        rebuild( )

    if( action == "clean" ) : 
        clean( )

    if( action == "help" ): 
        help( )

main()


