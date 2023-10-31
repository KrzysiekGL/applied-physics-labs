# hello world
file(GLOB HELLO_WORLD_SRCS hello_world/*.cc)
add_executable(hello_world ${HELLO_WORLD_SRCS})
target_link_libraries(hello_world ${OpenCV_LIBS})

