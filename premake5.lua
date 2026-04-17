workspace "Snake"
   configurations { "Debug", "Release" }
	architecture "x64"

project "Snake"
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
		"raylib"
	}

	filter "system:windows" 
		links "winmm"
		filter "configurations:Release"
			linkoptions { "/ENTRY:mainCRTStartup" }

   filter "configurations:Debug"
	  defines { "DEBUG" }
	  kind "ConsoleApp"
	  symbols "On"

   filter "configurations:Release"
	  defines { "NDEBUG" }
	  kind "WindowedApp"
	  optimize "On"