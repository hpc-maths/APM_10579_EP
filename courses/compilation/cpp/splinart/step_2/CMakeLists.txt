cmake_minimum_required(VERSION 3.15)

project(generative_art CXX)

find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)
