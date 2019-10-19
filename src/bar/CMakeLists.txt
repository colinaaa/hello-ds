aux_source_directory(. Bar)
add_library(bar SHARED ${Bar})
target_link_libraries(bar Catch2::Catch2 GSL)
