
-- workspace/solution setup
workspace("workspace") 
  configurations{ "Debug" , "Release" }
  bindirs("$(SolutionDir)build")

-- project setup
project("software_renderer")
  
  kind("WindowedApp")
  language "C++"
  
  targetdir("build/") -- exe output folder
  objdir("build/obj/") -- obj output folder
  
  files { "**.cpp" , "**.hpp" } 

  filter("configurations:Debug")
  defines { "DEBUG" }
  symbols("On")

  filter("configurations:Release")
  defines {"NDEBUG"}
  optimize "Off"
 
