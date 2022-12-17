cmake_minimum_required(VERSION 3.16)
project(PROJECT_NAME)

include_directories(src)
aux_source_directory(src SRC)

add_compile_options(-std=c17 -O3)

link_libraries(m)
add_library(rf src/rf.c)

add_executable(a3 src/a3.c)
target_link_libraries(a3 rf)

add_executable(sort src/sort.c)
target_link_libraries(sort rf)