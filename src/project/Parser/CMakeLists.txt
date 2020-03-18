aux_source_directory(. projectParserSRC)
include_directories(${CMAKE_SOURCE_DIR}/include/project/Parser)
include_directories(${CMAKE_SOURCE_DIR}/include/project)

add_library(projectParser STATIC ${projectParserSRC})
target_link_libraries(projectParser projectAST)
target_link_libraries(projectParser magic_enum)
