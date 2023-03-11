cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Obserwator)

file(GLOB SRCS *.cc)
add_executable(obserwator ${SRCS})
