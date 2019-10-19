include_directories (${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)

add_executable (Test main.cc)

target_link_libraries(Test Catch2::Catch2 bar)

set_target_properties(Test 
    PROPERTIES OUTPUT_NAME 
    "${CMAKE_SOURCE_DIR}/build/test.out"
)
