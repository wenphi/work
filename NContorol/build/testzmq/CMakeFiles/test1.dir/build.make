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
include testzmq/CMakeFiles/test1.dir/depend.make

# Include the progress variables for this target.
include testzmq/CMakeFiles/test1.dir/progress.make

# Include the compile flags for this target's objects.
include testzmq/CMakeFiles/test1.dir/flags.make

testzmq/CMakeFiles/test1.dir/test1.cpp.o: testzmq/CMakeFiles/test1.dir/flags.make
testzmq/CMakeFiles/test1.dir/test1.cpp.o: ../testzmq/test1.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ywh/work/NContorol/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object testzmq/CMakeFiles/test1.dir/test1.cpp.o"
	cd /home/ywh/work/NContorol/build/testzmq && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test1.dir/test1.cpp.o -c /home/ywh/work/NContorol/testzmq/test1.cpp

testzmq/CMakeFiles/test1.dir/test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/test1.cpp.i"
	cd /home/ywh/work/NContorol/build/testzmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ywh/work/NContorol/testzmq/test1.cpp > CMakeFiles/test1.dir/test1.cpp.i

testzmq/CMakeFiles/test1.dir/test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/test1.cpp.s"
	cd /home/ywh/work/NContorol/build/testzmq && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ywh/work/NContorol/testzmq/test1.cpp -o CMakeFiles/test1.dir/test1.cpp.s

testzmq/CMakeFiles/test1.dir/test1.cpp.o.requires:
.PHONY : testzmq/CMakeFiles/test1.dir/test1.cpp.o.requires

testzmq/CMakeFiles/test1.dir/test1.cpp.o.provides: testzmq/CMakeFiles/test1.dir/test1.cpp.o.requires
	$(MAKE) -f testzmq/CMakeFiles/test1.dir/build.make testzmq/CMakeFiles/test1.dir/test1.cpp.o.provides.build
.PHONY : testzmq/CMakeFiles/test1.dir/test1.cpp.o.provides

testzmq/CMakeFiles/test1.dir/test1.cpp.o.provides.build: testzmq/CMakeFiles/test1.dir/test1.cpp.o

# Object files for target test1
test1_OBJECTS = \
"CMakeFiles/test1.dir/test1.cpp.o"

# External object files for target test1
test1_EXTERNAL_OBJECTS =

testzmq/test1: testzmq/CMakeFiles/test1.dir/test1.cpp.o
testzmq/test1: testzmq/CMakeFiles/test1.dir/build.make
testzmq/test1: testzmq/CMakeFiles/test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test1"
	cd /home/ywh/work/NContorol/build/testzmq && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
testzmq/CMakeFiles/test1.dir/build: testzmq/test1
.PHONY : testzmq/CMakeFiles/test1.dir/build

testzmq/CMakeFiles/test1.dir/requires: testzmq/CMakeFiles/test1.dir/test1.cpp.o.requires
.PHONY : testzmq/CMakeFiles/test1.dir/requires

testzmq/CMakeFiles/test1.dir/clean:
	cd /home/ywh/work/NContorol/build/testzmq && $(CMAKE_COMMAND) -P CMakeFiles/test1.dir/cmake_clean.cmake
.PHONY : testzmq/CMakeFiles/test1.dir/clean

testzmq/CMakeFiles/test1.dir/depend:
	cd /home/ywh/work/NContorol/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ywh/work/NContorol /home/ywh/work/NContorol/testzmq /home/ywh/work/NContorol/build /home/ywh/work/NContorol/build/testzmq /home/ywh/work/NContorol/build/testzmq/CMakeFiles/test1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testzmq/CMakeFiles/test1.dir/depend

