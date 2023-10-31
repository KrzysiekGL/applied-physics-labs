# OpenCV project build toolchain
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(image_processing_with_opencv VERSION 0.1)

# OpenCV managed by the OS
# because it doesn't work with FetchContent or any other civilized integrated means of handling it
find_package(OpenCV REQUIRED)

# Project's executables
add_subdirectory(src)

