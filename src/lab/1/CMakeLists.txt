aux_source_directory(. lab1Src)
include_directories(${CMAKE_SOURCE_DIR}/include/lab/1)

add_library(liblab1 SHARED ${lab1Src})
target_link_libraries(liblab1 Catch2::Catch2 GSL)
