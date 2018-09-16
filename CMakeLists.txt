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
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  /MT /O2")
else()
message("probably GCC :3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -static-libgcc -static-libstdc++ -O3") 
endif()

file(GLOB SOURCES "*.cpp")
add_executable(easypt ${SOURCES}) 
add_library(console SHARED library/console/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp)
add_library(system SHARED library/system/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp)

if(LINUX)
message("LINUX GCC :3")
target_link_libraries(easypt dl)
endif()