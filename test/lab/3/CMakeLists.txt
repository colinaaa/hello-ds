include_directories(${CMAKE_SOURCE_DIR}/include/lab/3)

aux_source_directory(. lab3TestSrc)

add_library(objlab3Test OBJECT ${lab3TestSrc})

target_link_libraries(objlab3Test Catch2::Catch2)

