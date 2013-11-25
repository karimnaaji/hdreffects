cmake_minimum_required(VERSION 2.8)
project(HDR)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -g -O0")

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
find_package(GLFW REQUIRED)

if(APPLE)
	find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    
    list(APPEND GLFW_LIBRARY ${COCOA_FRAMEWORK}
                             ${IOKIT_FRAMEWORK}
                             ${CORE_FOUNDATION_FRAMEWORK})
endif()

#link c library
set(LIB_C lib)
include_directories(${LIB_C})
add_library(rgbe ${LIB_C}/rgbe.c)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

add_executable(hdr.out ${SOURCES})

target_link_libraries(hdr.out rgbe ${OPENGL_LIBRARIES} ${GLFW_LIBRARY} ${GLEW_LIBRARY})
