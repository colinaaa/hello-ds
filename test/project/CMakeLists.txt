aux_source_directory(. projectTestSrc)

add_library(objProjectTest OBJECT ${projectTestSrc})
include_directories(${CMAKE_SOURCE_DIR}/include/project)

target_link_libraries(objProjectTest Catch2::Catch2)
target_link_libraries(objProjectTest nlohmann_json::nlohmann_json)
target_link_libraries(objProjectTest fmt::fmt)
target_link_libraries(objProjectTest projectParser)
target_link_libraries(objProjectTest magic_enum)
