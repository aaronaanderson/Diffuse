# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.8.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.8.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sphere/code/Anderson/Diffuse/allolib/cmake/single_file

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sphere/code/Anderson/Diffuse/build/main/Release

# Utility rule file for main_run_debug.

# Include the progress variables for this target.
include CMakeFiles/main_run_debug.dir/progress.make

CMakeFiles/main_run_debug: /Users/sphere/code/Anderson/Diffuse/bin/main
	cd /Users/sphere/code/Anderson/Diffuse/bin && lldb -o\ run ./maind

main_run_debug: CMakeFiles/main_run_debug
main_run_debug: CMakeFiles/main_run_debug.dir/build.make

.PHONY : main_run_debug

# Rule to build all files generated by this target.
CMakeFiles/main_run_debug.dir/build: main_run_debug

.PHONY : CMakeFiles/main_run_debug.dir/build

CMakeFiles/main_run_debug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_run_debug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_run_debug.dir/clean

CMakeFiles/main_run_debug.dir/depend:
	cd /Users/sphere/code/Anderson/Diffuse/build/main/Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sphere/code/Anderson/Diffuse/allolib/cmake/single_file /Users/sphere/code/Anderson/Diffuse/allolib/cmake/single_file /Users/sphere/code/Anderson/Diffuse/build/main/Release /Users/sphere/code/Anderson/Diffuse/build/main/Release /Users/sphere/code/Anderson/Diffuse/build/main/Release/CMakeFiles/main_run_debug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main_run_debug.dir/depend

