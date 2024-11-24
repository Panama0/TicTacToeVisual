workspace "TicTacToeVisual"
    configurations {"Debug", "Release"}
    architecture "x64"
    location "./"

    project "TicTacToeVisual"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        targetdir "%{wks.location}/bin/"
        objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}"
        
        includedirs {"%{wks.location}/lib/**"}
        libdirs { "%{wks.location}/lib/sfml/lib", "%{wks.location}/bin/ImGui", "%{wks.location}/bin/SFML"}

        location "%{wks.location}"
        files {
            "%{prj.location}/src/**.h","%{prj.location}/src/**.cpp", "%{prj.location}/src/**.hpp"
        }

        filter "configurations:Debug"
            defines {"DEBUG","_DEBUG"}
            symbols "On"
            links { "sfml-graphics-d","sfml-system-d","sfml-window-d","opengl32.lib", "ImGui.lib" }
        filter{}

        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "On"
            links { "sfml-graphics","sfml-system","sfml-window","opengl32.lib", "ImGui.lib" }
        filter{}

	
	project "ImGui"
		kind "StaticLib"
		language "C++"

		targetdir "%{wks.location}/bin/ImGui"
		objdir "%{wks.location}/bin/obj/ImGui/%{cfg.buildcfg}"

		includedirs {"%{wks.location}/lib/**"}

		location "%{wks.location}/lib/imgui"
        files {
            "%{prj.location}/**.h","%{prj.location}/**.cpp"
        }
		
		filter "configurations:Debug"
            defines {"DEBUG","_DEBUG"}
            symbols "On"
        filter{}

		filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "On"
        filter{}