project(controlFrame)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")# add_subdirectory(libzmq)

# add_subdirectory(depend/jsoncpp)
# add_subdirectory(depend/zeromq/libzmq)
add_subdirectory(src)
add_subdirectory(test)
