include_directories(${CMAKE_SOURCE_DIR}/include/lab/4)
aux_source_directory(. lab4Src)

add_library(lab4Template MODULE ${lab4Src})
