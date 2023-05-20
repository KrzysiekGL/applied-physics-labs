cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MVVM)

# GLFW
add_subdirectory(./third-party/glfw)

# Dear ImGui
file(GLOB IMGUI_SRCS
  ./third-party/imgui/*.cpp
  ./third-party/imgui/backends/*opengl3.cpp
  ./third-party/imgui/backends/*glfw.cpp
)
add_library(imgui ${IMGUI_SRCS})
target_include_directories(imgui PUBLIC
  ${glfw_INCLUDE_DIRS}
  ./third-party/imgui
  ./third-party/imgui/backends
)
target_link_libraries(imgui PUBLIC
  glfw
)

# Memento hello
file(GLOB_RECURSE MEMENTO_SRCS
  ./src/memento/*.cc
  ./src/memento/*.cpp
)
add_executable(hello-memento ${MEMENTO_SRCS})

# OpenGL
include(FindOpenGL)

# The app - Command and Memento
file(GLOB_RECURSE APP_SRCS
  ./src/app/*.cc
  ./src/app/*.cpp
)
add_executable(app ${APP_SRCS})
target_include_directories(app PRIVATE
  ${OPENGL_INCLUDE_DIR}
  ${imgui_INCLUDE_DIRS}
)
target_link_libraries(app PRIVATE
  ${OPENGL_LIBRARIES}
  imgui
)
