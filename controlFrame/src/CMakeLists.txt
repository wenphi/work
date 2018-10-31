include_directories(${CMAKE_HOME_DIRECTORY}/depend)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/base SRC_BASE)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/motion/kdl SRC_MOTION1)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/motion SRC_MOTION2)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/io SRC_IO)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/robotStateMechine SRC_RSB)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/hello SRC_HELLO)

set(SRC_ALL  ${SRC_BASE} ${SRC_MOTION1} ${SRC_MOTION2} ${SRC_RSB} ${SRC_IO} ${SRC_HELLO})
add_library(test_src STATIC ${SRC_ALL})