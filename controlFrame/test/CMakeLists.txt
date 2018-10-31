include_directories(${CMAKE_HOME_DIRECTORY}/depend/zeromq)
include_directories(${CMAKE_HOME_DIRECTORY}/depend)
include_directories(${CMAKE_HOME_DIRECTORY}/src)


if(EMC_OS_ARM_LINUX)
    link_directories(${CMAKE_HOME_DIRECTORY}/depend/zeromq/libzmq/build_arm/lib)
    link_directories(${CMAKE_HOME_DIRECTORY}/depend/jsoncpp/build_arm/src/lib_json)
    # add_executable(test1 test.cpp)
    # target_link_libraries(test1 test_src jsoncpp libzmq.so pthread)
    # add_executable(testMsg testmessage.cpp)
    # target_link_libraries(testMsg test_src jsoncpp zmq pthread)

    # add_executable(testClient0 testClient0.cpp)
    # target_link_libraries(testClient0 test_src jsoncpp zmq pthread)
    # add_executable(testClient1 testClient1.cpp)
    # target_link_libraries(testClient1 test_src jsoncpp zmq pthread)
    add_executable(testServer testServer.cpp)
    target_link_libraries(testServer test_src jsoncpp zmq pthread)
    # #hello
    # add_executable(testHello testHello.cpp)
    # target_link_libraries(testHello test_src jsoncpp zmq pthread)

else(EMC_OS_ARM_LINUX)
link_directories(${CMAKE_HOME_DIRECTORY}/depend/jsoncpp/build_x86/src/lib_json)
link_directories(${CMAKE_HOME_DIRECTORY}/depend/zeromq/libzmq/zmqlib)
    add_executable(test1 test.cpp)
    target_link_libraries(test1 test_src jsoncpp libzmq.so pthread)
    add_executable(testMsg testmessage.cpp)
    target_link_libraries(testMsg test_src jsoncpp zmq pthread)

    add_executable(testClient0 testClient0.cpp)
    target_link_libraries(testClient0 test_src jsoncpp zmq pthread)
    add_executable(testClient1 testClient1.cpp)
    target_link_libraries(testClient1 test_src jsoncpp zmq pthread)
    add_executable(testServer testServer.cpp)
    target_link_libraries(testServer test_src jsoncpp zmq pthread)

    #hello
    add_executable(testHello testHello.cpp)
    target_link_libraries(testHello test_src jsoncpp zmq pthread)
endif(EMC_OS_ARM_LINUX)

