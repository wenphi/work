# arm编译
SET(CMAKE_SYSTEM_NAME Linux)

# 指定交叉编译器路径
# SET(CMAKE_C_COMPILER   /opt/gcc-arm-4.9/bin/arm-linux-gnueabihf-gcc)
# SET(CMAKE_CXX_COMPILER /opt/gcc-arm-4.9/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabihf-gcc-4.8)
SET(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++-4.8)





# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr/arm-linux-gnueabihf)

# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE armhf)

set(EMC_OS_ARM_LINUX true)
add_definitions(-DEMC_OS_ARM_LINUX)