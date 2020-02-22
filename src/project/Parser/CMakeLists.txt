aux_source_directory(. projectParserSRC)
include_directories(${CMAKE_SOURCE_DIR}/include/project/Parser)

add_library(projectParser STATIC ${projectParserSRC})
