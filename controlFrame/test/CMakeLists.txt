

add_executable(test1 test.cpp)
target_link_libraries(test1 test_src jsoncpp zmq pthread)