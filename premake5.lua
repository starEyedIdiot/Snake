workspace "Snake"
   configurations { "Debug", "Release" }
   	architecture "x64"

project "Snake"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "main.cpp" }
   
   -- INCLUDES
   includedirs
   {
		"ext/raylib/include"
   }
   
   -- LINKING
   libdirs
   {
		"ext/raylib/lib"
   }
   links 
   {
		"raylib",
		"winmm"
	}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"