cmake_minimum_required(VERSION 3.10)

project(Obserwator)

file(GLOB SRCS *.cc)
add_executable(obserwator ${SRCS})
