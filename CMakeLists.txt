cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(heapm C)

file(GLOB SOURCES "src/*.c")
add_library(heapm STATIC ${SOURCES})

target_include_directories(heapm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

