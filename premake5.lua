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
        libdirs { "%{wks.location}/lib/sfml/lib" }

        location "%{wks.location}"
        files {
            "%{prj.location}/src/**.h","%{prj.location}/src/**.cpp", "%{prj.location}/src/**.hpp"
            ,"%{prj.location}/src/imgui/**.h","%{prj.location}/lib/imgui/**.cpp"
        }

        filter "configurations:Debug"
            defines {"DEBUG","_DEBUG"}
            symbols "On"
            links { "sfml-graphics-d","sfml-system-d","sfml-window-d","opengl32.lib" }
        filter{}

        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "On"
            links { "sfml-graphics","sfml-system","sfml-window" }
        filter{}
