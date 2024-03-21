cmake_minimum_required(VERSION 3.16.3)

project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)

find_package(ZLIB)

file(GLOB_RECURSE SRCS
  ${CMAKE_SOURCE_DIR}/src/*.cc
  ${CMAKE_SOURCE_DIR}/external/tinyxml2/tinyxml2.cc
  ${CMAKE_SOURCE_DIR}/external/spng/spng.c
)

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  ${CMAKE_SOURCE_DIR}/external
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)
