add_library(Tlpi get_num.c error_functions.c)
target_include_directories(Tlpi
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})