aux_source_directory(. lab1Src)
include_directories(${CMAKE_SOURCE_DIR}/include/lab/1)

add_library(lab1Template MODULE ${lab1Src})
