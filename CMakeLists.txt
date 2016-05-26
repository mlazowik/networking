cmake_minimum_required(VERSION 2.8)
project(networking)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/stream)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/io)

set(SOURCE_FILES
    networking/socket.cpp
    networking/socket.h)

add_library(networking ${SOURCE_FILES})

add_dependencies(networking io stream)

target_link_libraries(networking io stream)

target_include_directories(networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})