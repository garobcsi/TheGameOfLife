cmake_minimum_required(VERSION 3.26)
project(TheGameOfLife C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)
if(LINUX)
    message(STATUS ">>> Linking Math Library")
target_link_libraries(${PROJECT_NAME} m)
endif ()
