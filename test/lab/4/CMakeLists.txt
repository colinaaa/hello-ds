include_directories(${CMAKE_SOURCE_DIR}/include/lab/4)

aux_source_directory(. lab4TestSrc)

add_library(objlab4Test OBJECT ${lab4TestSrc})

target_link_libraries(objlab4Test Catch2::Catch2)

