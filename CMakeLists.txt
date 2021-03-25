cmake_minimum_required(VERSION 3.16)
project(tlpi-test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_subdirectory(Tlpi)
list(APPEND EXTRA_LIBS Tlpi)

add_executable(${PROJECT_NAME} fileio/copy.c)

target_link_libraries(${PROJECT_NAME} PUBLIC Tlpi)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR})
