project(lap1d)

add_executable(main main.cpp src/dense.cpp src/csr.cpp src/cg.cpp)
target_include_directories(main PUBLIC "include/")