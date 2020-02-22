aux_source_directory(. projectASTSRC)
include_directories(${CMAKE_SOURCE_DIR}/include/project/AST)

add_library(projectAST STATIC ${projectASTSRC})
