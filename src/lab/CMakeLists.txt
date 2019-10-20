add_subdirectory(1)

include_directories(${CMAKE_SOURCE_DIR}/include/lab)
include_directories(${CMAKE_SOURCE_DIR}/include/lab/1)

add_executable(main main.cc ListImpl.cc)

target_link_libraries(main Catch2::Catch2)

set_target_properties(main 
    PROPERTIES OUTPUT_NAME 
    "${CMAKE_SOURCE_DIR}/main.out"
)