
-- workspace/solution setup
workspace("workspace")
  
  configurations{ "Debug" , "Release" }


-- project setup
project("software_renderer")
  
  kind("WindowedApp")
  language "C++"
  targetdir "build/%{cfg.buildcfg}"
  files { "**.cpp" , "**.hpp" } 

  filter("configurations:Debug")
  defines { "DEBUG" }
  symbols("On")

  filter("configurations:Release")
  defines {"NDEBUG"}
  optimize "Off"

