cmake_minimum_required(VERSION 3.23.0)

project(programming-tasks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/out)
#set(CMAKE_FILES_DIRECTORY ${PROJECT_SOURCE_DIR}/build/out)

add_subdirectory(src/stack)
add_subdirectory(src/reverse-words-order)