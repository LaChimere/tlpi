cmake_minimum_required(VERSION 3.19)
project(tlpi-test C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)

add_subdirectory(Tlpi)
list(APPEND EXTRA_LIBS Tlpi)

add_compile_options(-Wall)

add_executable(${PROJECT_NAME} signals/nonreentrant.c)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Tlpi
        crypt
        pthread
        )
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR})
