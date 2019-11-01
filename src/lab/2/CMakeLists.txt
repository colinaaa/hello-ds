include_directories(${CMAKE_SOURCE_DIR}/include/lab/2)
aux_source_directory(. lab2Src)

add_library(lab2Template OBJECT ${lab2Src})

