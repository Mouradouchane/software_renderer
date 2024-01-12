
-- workspace/solution setup
workspace("workspace")
  
  configurations{ "Debug" , "Release" }
-- project setup
project("software_renderer")
  
  kind("WindowedApp")
  language "C++"

  targetdir("build/") -- exe output folder
  objdir("build/obj/") -- obj output folder
  
  files { "**.cpp" , "**.hpp" } 
  files { "sdl2/include/**" }

  links { "./sdl2/lib/x86/SDL2.lib" }

  filter("configurations:Debug")
  defines { "DEBUG" }
  symbols("On")

  filter("configurations:Release")
  defines {"NDEBUG"}
  optimize "Off"
 
  -- copy sdl2.dll to build folder
  if os.isdir("./build") then

     ok , err = os.copyfile( './sdl2/lib/x86/SDL2.dll' , './build/SDL2.dll' )

      if err == nil then 
        print("error while copying sdl2.dll to build folder !!!")
      end

  else 
    os.mkdir("build")
    rslt = os.copyfile('sdl2/lib/x86/SDL2.dll','build')
  end

