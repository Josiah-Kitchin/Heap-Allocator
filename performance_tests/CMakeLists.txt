cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(perform_heapm C)

file(GLOB SOURCES "../src/*.c")
add_executable(perform_heapm ${SOURCES} "main.c")

target_include_directories(perform_heapm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")



