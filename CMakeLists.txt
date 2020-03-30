cmake_minimum_required(VERSION 3.12)
project(hello-ds)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -g -Og")

SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG_INIT} --coverage -O0")
SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")

set(CMAKE_CXX_FLAGS_VALGRIND "${CMAKE_CXX_FLAGS_DEBUG_INIT} -O0")
if(DEFINED ENV{CI})
    include_directories(SYSTEM /usr/include/c++/8)
    set(CMAKE_CXX_FLAGS -stdlib=libc++)
    set(CMAKE_CXX_LINKER_FLAGS -stdlib=libc++)
else()
    # local dev
    if(CMAKE_BUILD_TYPE STREQUAL Coverage)
        if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
            add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
            message("compile with clang")
            add_link_options(-fprofile-instr-generate)
            #Uncomment in case of linker errors
            #link_libraries(clang_rt.profile-x86_64)
        elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            add_compile_options(--coverage)
            #Uncomment in case of linker errors
            #link_libraries(gcov)
        endif ()
    endif()
endif()


add_subdirectory(lib/Catch2)
add_subdirectory(lib/fmt)
add_subdirectory(lib/docopt.cpp)
add_subdirectory(lib/magic_enum)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(lib/json)

add_subdirectory (src)

add_subdirectory (test)
