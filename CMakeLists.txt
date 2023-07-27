cmake_minimum_required(VERSION 2.6)
project(texgen)

set(CMAKE_VERBOSE_MAKEFILE on)

set(include_paths /usr/include/SDL2 /usr/include/GL)
include_directories( ${include_paths} )

set(src_files simplegenemutate.cpp main.cpp sdlgl.cpp simplegene.cpp simplefitness.cpp image.cpp
		util.cpp random.cpp)
add_executable(texgen ${src_files})

set (link_libs GL GLEW SDL2 m)
target_link_libraries(texgen ${link_libs})
