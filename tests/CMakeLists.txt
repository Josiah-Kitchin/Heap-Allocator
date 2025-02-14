cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(test_heapm C)

file(GLOB SOURCES "../src/*.c")
file(GLOB TEST_SOURCES "./*.c")
add_executable(test_heapm ${SOURCES} ${TEST_SOURCES})

target_include_directories(test_heapm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    /usr/include/criterion
)

target_link_libraries(test_heapm PRIVATE -lcriterion)

