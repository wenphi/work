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
CMAKE_BINARY_DIR = /home/ywh/work/NContorol/build

# Include any dependencies generated for this target.
include testzmq/CMakeFiles/tzmqclient.dir/depend.make

# Include the progress variables for this target.
include testzmq/CMakeFiles/tzmqclient.dir/progress.make

# Include the compile flags for this target's objects.
include testzmq/CMakeFiles/tzmqclient.dir/flags.make

testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o: testzmq/CMakeFiles/tzmqclient.dir/flags.make
testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o: ../testzmq/tzmqClient.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ywh/work/NContorol/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o"
	cd /home/ywh/work/NContorol/build/testzmq && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o -c /home/ywh/work/NContorol/testzmq/tzmqClient.cpp

testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tzmqclient.dir/tzmqClient.cpp.i"
	cd /home/ywh/work/NContorol/build/testzmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ywh/work/NContorol/testzmq/tzmqClient.cpp > CMakeFiles/tzmqclient.dir/tzmqClient.cpp.i

testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tzmqclient.dir/tzmqClient.cpp.s"
	cd /home/ywh/work/NContorol/build/testzmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ywh/work/NContorol/testzmq/tzmqClient.cpp -o CMakeFiles/tzmqclient.dir/tzmqClient.cpp.s

testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.requires:
.PHONY : testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.requires

testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.provides: testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.requires
	$(MAKE) -f testzmq/CMakeFiles/tzmqclient.dir/build.make testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.provides.build
.PHONY : testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.provides

testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.provides.build: testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o

# Object files for target tzmqclient
tzmqclient_OBJECTS = \
"CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o"

# External object files for target tzmqclient
tzmqclient_EXTERNAL_OBJECTS =

testzmq/tzmqclient: testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o
testzmq/tzmqclient: testzmq/CMakeFiles/tzmqclient.dir/build.make
testzmq/tzmqclient: testzmq/CMakeFiles/tzmqclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tzmqclient"
	cd /home/ywh/work/NContorol/build/testzmq && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tzmqclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
testzmq/CMakeFiles/tzmqclient.dir/build: testzmq/tzmqclient
.PHONY : testzmq/CMakeFiles/tzmqclient.dir/build

testzmq/CMakeFiles/tzmqclient.dir/requires: testzmq/CMakeFiles/tzmqclient.dir/tzmqClient.cpp.o.requires
.PHONY : testzmq/CMakeFiles/tzmqclient.dir/requires

testzmq/CMakeFiles/tzmqclient.dir/clean:
	cd /home/ywh/work/NContorol/build/testzmq && $(CMAKE_COMMAND) -P CMakeFiles/tzmqclient.dir/cmake_clean.cmake
.PHONY : testzmq/CMakeFiles/tzmqclient.dir/clean

testzmq/CMakeFiles/tzmqclient.dir/depend:
	cd /home/ywh/work/NContorol/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ywh/work/NContorol /home/ywh/work/NContorol/testzmq /home/ywh/work/NContorol/build /home/ywh/work/NContorol/build/testzmq /home/ywh/work/NContorol/build/testzmq/CMakeFiles/tzmqclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testzmq/CMakeFiles/tzmqclient.dir/depend

