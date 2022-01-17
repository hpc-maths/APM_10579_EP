add_library(art core.cpp shape.cpp spline.cpp)
target_include_directories(art PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(art ${OpenCV_LIBS})
