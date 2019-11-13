include_directories (${CMAKE_SOURCE_DIR}/src)
add_subdirectory(lab/1)
add_subdirectory(lab/2)
add_subdirectory(lab/3)
#aux_source_directory(lab/1 lab1Test)
# aux_source_directory(lab/2 lab2Test)
add_executable (Test main.cc)

target_link_libraries(Test Catch2::Catch2 objlab1Test objlab2Test objlab3Test)

