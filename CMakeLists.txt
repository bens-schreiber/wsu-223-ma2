cmake_minimum_required(VERSION 3.10)
project(pa1-223)
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES src/*.cpp)

foreach(SOURCE ${SOURCES})
    message("Found source file: ${SOURCE}")
endforeach()

add_executable(ma2 ${SOURCES})