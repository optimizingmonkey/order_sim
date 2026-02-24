cmake_minimum_required(VERSION 3.10)
project(QuantSim)

# Use C++20 for performance features like '[[likely]]' and 'std::span'
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Include the 'include' directory so the compiler can find engine.hpp
include_directories(include)

# 2. Gather all source files
file(GLOB SOURCES "src/*.cpp")

# 3. Create the executable named 'sim_engine'
add_executable(sim_engine ${SOURCES})

# 4. Optional: Enable optimizations for 'Release' builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
