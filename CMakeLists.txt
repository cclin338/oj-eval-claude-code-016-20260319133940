cmake_minimum_required(VERSION 3.10)
project(file_storage_bpt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -std=c++17")

# Create executable named 'code' as required
add_executable(code main.cpp)

# Optional: if you have more source files, add them here
# target_sources(code PRIVATE bpt.cpp file_storage.cpp)