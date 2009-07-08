cmake_minimum_required(VERSION 2.6)
project(texgen)

set(include_paths /usr/include/SDL /usr/include/GL)
include_directories( ${include_paths} )

set(src_files main.cpp sdlgl.cpp)
add_executable(texgen ${src_files})

set (link_libs GL GLEW SDL)
target_link_libraries(texgen ${link_libs})
