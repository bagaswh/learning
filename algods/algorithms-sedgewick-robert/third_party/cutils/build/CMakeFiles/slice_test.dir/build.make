# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/bagaswh/gammix-large/code/mine/c-toolbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/bagaswh/gammix-large/code/mine/c-toolbox/build

# Include any dependencies generated for this target.
include CMakeFiles/slice_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/slice_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/slice_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/slice_test.dir/flags.make

CMakeFiles/slice_test.dir/codegen:
.PHONY : CMakeFiles/slice_test.dir/codegen

CMakeFiles/slice_test.dir/slice_test.c.o: CMakeFiles/slice_test.dir/flags.make
CMakeFiles/slice_test.dir/slice_test.c.o: /media/bagaswh/gammix-large/code/mine/c-toolbox/slice_test.c
CMakeFiles/slice_test.dir/slice_test.c.o: CMakeFiles/slice_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/bagaswh/gammix-large/code/mine/c-toolbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/slice_test.dir/slice_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/slice_test.dir/slice_test.c.o -MF CMakeFiles/slice_test.dir/slice_test.c.o.d -o CMakeFiles/slice_test.dir/slice_test.c.o -c /media/bagaswh/gammix-large/code/mine/c-toolbox/slice_test.c

CMakeFiles/slice_test.dir/slice_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/slice_test.dir/slice_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/bagaswh/gammix-large/code/mine/c-toolbox/slice_test.c > CMakeFiles/slice_test.dir/slice_test.c.i

CMakeFiles/slice_test.dir/slice_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/slice_test.dir/slice_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/bagaswh/gammix-large/code/mine/c-toolbox/slice_test.c -o CMakeFiles/slice_test.dir/slice_test.c.s

# Object files for target slice_test
slice_test_OBJECTS = \
"CMakeFiles/slice_test.dir/slice_test.c.o"

# External object files for target slice_test
slice_test_EXTERNAL_OBJECTS =

slice_test: CMakeFiles/slice_test.dir/slice_test.c.o
slice_test: CMakeFiles/slice_test.dir/build.make
slice_test: CMakeFiles/slice_test.dir/compiler_depend.ts
slice_test: libslice.a
slice_test: libunity.a
slice_test: CMakeFiles/slice_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/media/bagaswh/gammix-large/code/mine/c-toolbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable slice_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slice_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/slice_test.dir/build: slice_test
.PHONY : CMakeFiles/slice_test.dir/build

CMakeFiles/slice_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/slice_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/slice_test.dir/clean

CMakeFiles/slice_test.dir/depend:
	cd /media/bagaswh/gammix-large/code/mine/c-toolbox/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/bagaswh/gammix-large/code/mine/c-toolbox /media/bagaswh/gammix-large/code/mine/c-toolbox /media/bagaswh/gammix-large/code/mine/c-toolbox/build /media/bagaswh/gammix-large/code/mine/c-toolbox/build /media/bagaswh/gammix-large/code/mine/c-toolbox/build/CMakeFiles/slice_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/slice_test.dir/depend

