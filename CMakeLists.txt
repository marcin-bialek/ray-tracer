cmake_minimum_required(VERSION 3.16.3)

project(ray-tracer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRCS src/*.cc)

add_executable(${PROJECT_NAME} ${SRCS})
