add_library(art core.cpp shape.cpp spline.cpp)
target_include_directories(art PUBLIC ${CMAKE_SOURCE_DIR}/include)
