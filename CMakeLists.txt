cmake_minimum_required(VERSION 3.26)
project(TheGameOfLife C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)
if(NOT WIN32)
    message(STATUS "Linking Math Library")
    target_link_libraries(${PROJECT_NAME} m)
endif ()
add_subdirectory(src)

if(WIN32)
    target_compile_options(${PROJECT_NAME} PUBLIC /Wall /WX)
else ()
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror)
endif ()