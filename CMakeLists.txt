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

include_directories(${PROJECT_SOURCE_DIR})

if(MSVC)
    message("MSVC :3")
    add_compile_options(/MT /EHa /O2)
else()
    message("probably GCC :3")
    add_compile_options(-static-libgcc -static-libstdc++ -O3) 
endif()

file(GLOB SOURCES "*.cpp")
add_executable(easypt ${SOURCES}) 
add_library(console SHARED library/console/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp asyncTasks.cpp)
add_library(system SHARED library/system/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp asyncTasks.cpp)
add_library(time SHARED library/time/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp asyncTasks.cpp)
add_library(docs SHARED library/docs/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp asyncTasks.cpp)
add_library(file SHARED library/file/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp asyncTasks.cpp)
add_library(memory SHARED library/memory/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp asyncTasks.cpp)
add_library(math SHARED library/math/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp asyncTasks.cpp)
#add_library(devices SHARED library/devices/main.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp asyncTasks.cpp)
add_library(nativeInterface SHARED library/nativeInterface/main.cpp library/nativeInterface/interface.cpp exception.cpp name.cpp nobject.cpp IO.cpp Common.cpp osDependent.cpp asyncTasks.cpp)

configure_file(library/network/network.ez ${CMAKE_BINARY_DIR}/network.ez COPYONLY)
configure_file(library/compression/compression.ez ${CMAKE_BINARY_DIR}/compression.ez COPYONLY)
configure_file(library/utility/utility.ez ${CMAKE_BINARY_DIR}/utility.ez COPYONLY)
configure_file(library/algorithm/algorithm.ez ${CMAKE_BINARY_DIR}/algorithm.ez COPYONLY)

if("${CMAKE_SYSTEM}" MATCHES "Linux")
    message("LINUX :3")
endif()

find_package(Threads REQUIRED)
target_link_libraries(easypt Threads::Threads)
target_link_libraries(console Threads::Threads)
target_link_libraries(system Threads::Threads)
target_link_libraries(time Threads::Threads)
target_link_libraries(docs Threads::Threads)
target_link_libraries(file Threads::Threads)
target_link_libraries(memory Threads::Threads)
target_link_libraries(math Threads::Threads)
#target_link_libraries(devices Threads::Threads)
target_link_libraries(nativeInterface Threads::Threads)

#find_package(X11 REQUIRED)
#target_link_libraries(devices ${X11_LIBRARIES})

target_include_directories(nativeInterface PUBLIC thirdparty/tinycc)

if(MSVC)
    target_link_libraries(nativeInterface thirdparty/tinycc/win32/libtcc)
    file(COPY thirdparty/tinycc/libtcc.dll DESTINATION ${CMAKE_BINARY_DIR})
else()
    target_link_libraries(easypt stdc++fs)
    target_link_libraries(easypt dl)
    target_link_libraries(nativeInterface ${CMAKE_SOURCE_DIR}/thirdparty/tinycc/libtcc.so)
    target_link_libraries(nativeInterface stdc++fs)
    target_link_libraries(nativeInterface dl)
    file(COPY thirdparty/tinycc/libtcc.so DESTINATION ${CMAKE_BINARY_DIR})
endif()

file(COPY thirdparty/tinycc/include DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB LIBS_A "thirdparty/tinycc/lib/*.a")
file(GLOB LIBS_DEF "thirdparty/tinycc/lib/*.def")
file(GLOB LIBS "thirdparty/tinycc/*.a")
file(COPY ${LIBS} ${LIBS_A} ${LIBS_DEF} DESTINATION ${CMAKE_BINARY_DIR}/lib)
file(COPY library/nativeInterface/interface.h DESTINATION ${CMAKE_BINARY_DIR}/include)

