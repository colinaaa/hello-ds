include_directories(${CMAKE_SOURCE_DIR}/include/lab/1)

aux_source_directory(. lab1TestSrc)

add_library(objlab1Test OBJECT ${lab1TestSrc})

target_link_libraries(objlab1Test Catch2::Catch2)

