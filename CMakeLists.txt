cmake_minimum_required(VERSION 3.12)
project(hello-ds)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(libc++ REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -g -O1")

SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG_INIT} --coverage -O0")
SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")

set(CMAKE_CXX_FLAGS_VALGRIND "${CMAKE_CXX_FLAGS_DEBUG_INIT} -O0")
if(DEFINED ENV{CI})
include_directories(SYSTEM /usr/include/c++/8)
else()
include_directories(SYSTEM /usr/lib/llvm-9/include/c++/v1 /usr/include/c++/v1)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi -lc++")
add_compile_options("-stdlib=libc++")
endif()

add_subdirectory(lib/Catch2)


add_subdirectory (src) 

add_subdirectory (test)
