include_directories(${CMAKE_SOURCE_DIR}/include/lab/2)

aux_source_directory(. lab2TestSrc)

add_library(objlab2Test OBJECT ${lab2TestSrc})

target_link_libraries(objlab2Test Catch2::Catch2)

