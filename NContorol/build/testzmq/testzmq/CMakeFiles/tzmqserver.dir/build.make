# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ywh/work/NContorol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ywh/work/NContorol/build/testzmq

# Include any dependencies generated for this target.
include testzmq/CMakeFiles/tzmqserver.dir/depend.make

# Include the progress variables for this target.
include testzmq/CMakeFiles/tzmqserver.dir/progress.make

# Include the compile flags for this target's objects.
include testzmq/CMakeFiles/tzmqserver.dir/flags.make

testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o: testzmq/CMakeFiles/tzmqserver.dir/flags.make
testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o: ../../testzmq/tzmqServer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ywh/work/NContorol/build/testzmq/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o"
	cd /home/ywh/work/NContorol/build/testzmq/testzmq && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o -c /home/ywh/work/NContorol/testzmq/tzmqServer.cpp

testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tzmqserver.dir/tzmqServer.cpp.i"
	cd /home/ywh/work/NContorol/build/testzmq/testzmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ywh/work/NContorol/testzmq/tzmqServer.cpp > CMakeFiles/tzmqserver.dir/tzmqServer.cpp.i

testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tzmqserver.dir/tzmqServer.cpp.s"
	cd /home/ywh/work/NContorol/build/testzmq/testzmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ywh/work/NContorol/testzmq/tzmqServer.cpp -o CMakeFiles/tzmqserver.dir/tzmqServer.cpp.s

testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.requires:
.PHONY : testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.requires

testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.provides: testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.requires
	$(MAKE) -f testzmq/CMakeFiles/tzmqserver.dir/build.make testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.provides.build
.PHONY : testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.provides

testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.provides.build: testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o

# Object files for target tzmqserver
tzmqserver_OBJECTS = \
"CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o"

# External object files for target tzmqserver
tzmqserver_EXTERNAL_OBJECTS =

testzmq/tzmqserver: testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o
testzmq/tzmqserver: testzmq/CMakeFiles/tzmqserver.dir/build.make
testzmq/tzmqserver: testzmq/CMakeFiles/tzmqserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tzmqserver"
	cd /home/ywh/work/NContorol/build/testzmq/testzmq && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tzmqserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
testzmq/CMakeFiles/tzmqserver.dir/build: testzmq/tzmqserver
.PHONY : testzmq/CMakeFiles/tzmqserver.dir/build

testzmq/CMakeFiles/tzmqserver.dir/requires: testzmq/CMakeFiles/tzmqserver.dir/tzmqServer.cpp.o.requires
.PHONY : testzmq/CMakeFiles/tzmqserver.dir/requires

testzmq/CMakeFiles/tzmqserver.dir/clean:
	cd /home/ywh/work/NContorol/build/testzmq/testzmq && $(CMAKE_COMMAND) -P CMakeFiles/tzmqserver.dir/cmake_clean.cmake
.PHONY : testzmq/CMakeFiles/tzmqserver.dir/clean

testzmq/CMakeFiles/tzmqserver.dir/depend:
	cd /home/ywh/work/NContorol/build/testzmq && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ywh/work/NContorol /home/ywh/work/NContorol/testzmq /home/ywh/work/NContorol/build/testzmq /home/ywh/work/NContorol/build/testzmq/testzmq /home/ywh/work/NContorol/build/testzmq/testzmq/CMakeFiles/tzmqserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testzmq/CMakeFiles/tzmqserver.dir/depend

