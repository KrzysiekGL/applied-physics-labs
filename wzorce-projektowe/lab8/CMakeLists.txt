cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MVVM)

# GLFW
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfw)

# Dear ImGui
file(GLOB IMGUI_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/backends/*opengl3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/backends/*glfw.cpp
)
add_library(imgui ${IMGUI_SRCS})
target_include_directories(imgui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/backends
)
target_link_libraries(imgui PUBLIC
  glfw
)

# Memento hello
file(GLOB_RECURSE MEMENTO_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memento/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memento/*.cpp
)
add_executable(hello-memento ${MEMENTO_SRCS})

# OpenGL
include(FindOpenGL)

# libmemento
Add_library(memento
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memento/CareTaker.cc
)
target_include_directories(memento PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memento
)

# The app - Command and Memento
file(GLOB_RECURSE APP_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.cpp
)
add_executable(app ${APP_SRCS})
target_link_libraries(app PRIVATE
  ${OPENGL_LIBRARIES}
  imgui
  memento
)
