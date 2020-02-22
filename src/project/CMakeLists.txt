add_subdirectory(Parser)
#add_subdirectory(AST)
include_directories(${CMAKE_SOURCE_DIR}/include/project)

add_executable(yacc main.cc)

target_link_libraries(yacc projectParser)



set_target_properties(yacc 
    PROPERTIES OUTPUT_NAME 
    "${CMAKE_SOURCE_DIR}/build/yacc.out"
)
