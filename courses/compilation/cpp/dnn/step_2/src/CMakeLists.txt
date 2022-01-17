add_library(dnn activation.cpp propagation.cpp testing_and_training.cpp weights.cpp)
target_include_directories(dnn PUBLIC ${CMAKE_SOURCE_DIR}/include)