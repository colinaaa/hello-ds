include_directories(${CMAKE_SOURCE_DIR}/include/lab/3)
aux_source_directory(. lab3Src)

add_library(lab3Template MODULE ${lab3Src})