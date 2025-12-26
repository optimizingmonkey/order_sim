cmake_minimum_required(VERSION 3.10)
project(quant_sim)

# Set C++20 standard (essential for high-perf features)
set(CMAKE_CXX_STANDARD 20)

# Tell CMake where to find your code
add_executable(sim_engine src/main.cpp)
