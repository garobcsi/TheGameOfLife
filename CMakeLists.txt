cmake_minimum_required(VERSION 3.26)
project(TheGameOfLife C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} c)
if(LINUX)
    message(STATUS "Linking Math Library")
    target_link_libraries(${PROJECT_NAME} m)
endif ()
add_subdirectory(src)
