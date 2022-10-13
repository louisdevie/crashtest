cmake_minimum_required(VERSION 3.10)

project(CrashTest VERSION 0.0.1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(tests)