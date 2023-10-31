# hello world
file(GLOB HELLO_WORLD_SRCS hello_world/*.cc)
add_executable(hello_world ${HELLO_WORLD_SRCS})
target_link_libraries(hello_world ${OpenCV_LIBS})

# camera capture
file(GLOB CAMERA_CAPTURE_SRCS camera_capture/*.cc)
add_executable(camera_capture ${CAMERA_CAPTURE_SRCS})
target_link_libraries(camera_capture ${OpenCV_LIBS})
