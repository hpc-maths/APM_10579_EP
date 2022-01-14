cmake_minimum_required(VERSION 3.18)

PROJECT(RNN)

set(RNN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${RNN_INCLUDE_DIR})
set (HEADERS
    include/rnn/io.hpp
)

add_subdirectory(demos)