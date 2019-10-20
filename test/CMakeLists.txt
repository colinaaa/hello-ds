include_directories (${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include/lab/1)

aux_source_directory(lab/1 lab1Test)
add_executable (Test main.cc ${lab1Test})

target_link_libraries(Test Catch2::Catch2 liblab1)

set_target_properties(Test 
    PROPERTIES OUTPUT_NAME 
    "${CMAKE_SOURCE_DIR}/build/test.out"
)
