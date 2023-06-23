workspace "qbRayTracepm"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

SDL2_DIR = "external/SDL"
GLM_DIR = "external/glm"
SPDLOG_DIR = "external/spdlog"
--FMT_DIR = "external/fmt"


IncludeDir = {
   spdlog = "%{SPDLOG_DIR}/include",
   --fmt = "%{FMT_DIR}/include",
   SDL2 = "%{SDL2_DIR}/include"
}

LibraryDir = {
   SDL2 = "%{SDL2_DIR}/lib/x64"
}

Library = {
   SDL2 = "%{LibraryDir.SDL2}/SDL2.lib",
   SDL2main = "%{LibraryDir.SDL2}/SDL2main.lib"
}

project "qbRayTracepm"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h","src/**.hpp", "src/**.cpp" }

   includedirs {
      "%{IncludeDir.SDL2}",
      "%{IncludeDir.spdlog}",
--      "%{IncludeDir.fmt}"
   }
   links {
        "%{Library.SDL2}",
         "%{Library.SDL2main}"
   }
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"

   filter "configurations:Debug"
      defines { "WL_DEBUG", "SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG" }
      runtime "Debug"
      inlining "Auto"
      symbols "On"


   filter "configurations:Release"
      defines { "WL_RELEASE", "SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE" }
      runtime "Release"
      optimize "On"
      inlining "Auto"
      symbols "On"
      flags { "LinkTimeOptimization", "MultiProcessorCompile"} 

   filter "configurations:Dist"
      defines { "WL_DIST", "SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE" }
      runtime "Release"
      optimize "On"
      inlining "Auto"
      symbols "Off"
      omitframepointer "On"
      flags { "LinkTimeOptimization", "MultiProcessorCompile", "NoBufferSecurityCheck", "NoIncrementalLink" }
