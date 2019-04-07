cmake_minimum_required(VERSION 3.10)
project(easypt)

# Use c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Add DEBUG flag for debug compilations
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# Force MSVC to place artifacts where I want it
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

if(MSVC)
message("MSVC :3")
add_compile_options(/MT /EHa /O2)
else()
message("probably GCC :3")
add_compile_options(-static-libgcc -static-libstdc++ -O3) 
endif()

file(GLOB SOURCES "*.cpp")
add_executable(easypt ${SOURCES}) 
add_library(console SHARED library/console/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp SequentialTask.cpp)
add_library(system SHARED library/system/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp SequentialTask.cpp)
add_library(time SHARED library/time/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp SequentialTask.cpp)
add_library(docs SHARED library/docs/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp SequentialTask.cpp)
add_library(file SHARED library/file/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp SequentialTask.cpp)
add_library(memory SHARED library/memory/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp SequentialTask.cpp)
add_library(math SHARED library/math/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp SequentialTask.cpp)

configure_file(library/network/network.ez ${CMAKE_BINARY_DIR}/network.ez COPYONLY)
configure_file(library/compression/compression.ez ${CMAKE_BINARY_DIR}/compression.ez COPYONLY)
configure_file(library/utility/utility.ez ${CMAKE_BINARY_DIR}/utility.ez COPYONLY)
configure_file(library/algorithm/algorithm.ez ${CMAKE_BINARY_DIR}/algorithm.ez COPYONLY)

IF("${CMAKE_SYSTEM}" MATCHES "Linux")
message("LINUX :3")
target_link_libraries(easypt dl)
endif()
