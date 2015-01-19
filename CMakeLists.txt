cmake_minimum_required(VERSION 2.8)
project(HDR)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x -g -O0")

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

set(INCLUDE_DIRS "")
foreach(_headerFile ${HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list(APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(LIB lib)
include_directories(${LIB})
add_library(rgbe ${LIB}/rgbe.c)

add_subdirectory("${LIB}/glm")
add_subdirectory(${LIB}/glfw-3.0.3)
include_directories(${LIB}/glfw-3.0.3/include)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

add_executable(hdr.out ${SOURCES})

target_link_libraries(hdr.out glfw ${GLFW_LIBRARIES})
target_link_libraries(hdr.out rgbe ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
