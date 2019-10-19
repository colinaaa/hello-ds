cmake_minimum_required(VERSION 3.12)
project(luogu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(libc++ REQUIRED)

if(DEFINED ENV{CI})
include_directories(SYSTEM /usr/include/c++/8)
else()
include_directories(SYSTEM /usr/lib/llvm-9/include/c++/v1 /usr/include/c++/v1)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi -lc++")
add_compile_options("-stdlib=libc++")
endif()

add_subdirectory(lib/gsl)
add_subdirectory(lib/Catch2)


add_subdirectory (src) 

add_subdirectory (test)
