cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MVVM)

include_directories(./src)

file(GLOB_RECURSE MEMENTO_SRCS ./src/memento/*.cc ./src/memento/*.cpp)
add_executable(hello-memento ${MEMENTO_SRCS})
