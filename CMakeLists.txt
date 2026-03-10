cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

#set the production build ON or OFF
set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC) # if visual studio
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug")
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
else()
	add_link_options(-static-libstdc++ -static-libgcc)
	add_compile_options(-mavx2 -mfma)#make sure SIMD optimizations take place, but
endif()

# Ensure Raylib is built as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static libraries" FORCE)

project(TerrariaClone)

#add Raylib, and other lib if needed
add_subdirectory(thirdparty/raylib-5.0)
add_subdirectory(thirdparty/imgui-docking)
add_subdirectory(thirdparty/rlimgui)
add_subdirectory(thirdparty/FastNoiseSIMD)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of the exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources")

	# remove the options to debug asserts
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

#add the source files to the executables
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

# tell the compiler to not create the console if we are in a production build

if(MSVC) # if vs compiler
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	if(PRODUCTION_BUILD)
		#remove the console
		set_target_properties("${CMAKE_PROJECT_NAME}"
		PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	endif()

elseif(MINGW) # Windows / MinGW GCC/Glang
	if(PRODUCTION_BUILD)
		#remove the console on windows under MinGW
		target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -mwindows)
	endif()

elseif(APPLE OR UNIX) #macOS / Linux
	if(PRODUCTION_BUILD)
		target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
	endif()
endif()

#tell cmake to include all the headers files in src
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/gameLayer")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/platform")

#Link Raylib lib statically, and other if needed
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static imgui rlimgui fastNoiseSIMD)