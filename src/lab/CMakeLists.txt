add_subdirectory(1)
add_subdirectory(2)
add_subdirectory(3)
add_subdirectory(4)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include/lab)
include_directories(${CMAKE_SOURCE_DIR}/include/lab/4)

add_executable(main main.cc ListImpl.cc)


set_target_properties(main 
    PROPERTIES OUTPUT_NAME 
    "${CMAKE_SOURCE_DIR}/build/main.out"
)
