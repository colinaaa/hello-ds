add_subdirectory(Parser)
add_subdirectory(AST)
include_directories(${CMAKE_SOURCE_DIR}/include/project)

add_executable(tcc main.cc)

target_link_libraries(tcc fmt::fmt)
target_link_libraries(tcc projectParser)
target_link_libraries(tcc docopt)

set_target_properties(tcc
    PROPERTIES OUTPUT_NAME
    "${CMAKE_SOURCE_DIR}/build/tcc"
)
