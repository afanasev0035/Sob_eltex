# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c"

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_util_file.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_util_file.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_util_file.dir/flags.make

tests/CMakeFiles/test_util_file.dir/test_util_file.c.o: tests/CMakeFiles/test_util_file.dir/flags.make
tests/CMakeFiles/test_util_file.dir/test_util_file.c.o: tests/test_util_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_util_file.dir/test_util_file.c.o"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_util_file.dir/test_util_file.c.o   -c "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests/test_util_file.c"

tests/CMakeFiles/test_util_file.dir/test_util_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_util_file.dir/test_util_file.c.i"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests/test_util_file.c" > CMakeFiles/test_util_file.dir/test_util_file.c.i

tests/CMakeFiles/test_util_file.dir/test_util_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_util_file.dir/test_util_file.c.s"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests/test_util_file.c" -o CMakeFiles/test_util_file.dir/test_util_file.c.s

tests/CMakeFiles/test_util_file.dir/__/strerror_override.c.o: tests/CMakeFiles/test_util_file.dir/flags.make
tests/CMakeFiles/test_util_file.dir/__/strerror_override.c.o: strerror_override.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/test_util_file.dir/__/strerror_override.c.o"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_util_file.dir/__/strerror_override.c.o   -c "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/strerror_override.c"

tests/CMakeFiles/test_util_file.dir/__/strerror_override.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_util_file.dir/__/strerror_override.c.i"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/strerror_override.c" > CMakeFiles/test_util_file.dir/__/strerror_override.c.i

tests/CMakeFiles/test_util_file.dir/__/strerror_override.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_util_file.dir/__/strerror_override.c.s"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/strerror_override.c" -o CMakeFiles/test_util_file.dir/__/strerror_override.c.s

# Object files for target test_util_file
test_util_file_OBJECTS = \
"CMakeFiles/test_util_file.dir/test_util_file.c.o" \
"CMakeFiles/test_util_file.dir/__/strerror_override.c.o"

# External object files for target test_util_file
test_util_file_EXTERNAL_OBJECTS =

tests/test_util_file: tests/CMakeFiles/test_util_file.dir/test_util_file.c.o
tests/test_util_file: tests/CMakeFiles/test_util_file.dir/__/strerror_override.c.o
tests/test_util_file: tests/CMakeFiles/test_util_file.dir/build.make
tests/test_util_file: libjson-c.so.5.1.0
tests/test_util_file: tests/CMakeFiles/test_util_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable test_util_file"
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_util_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_util_file.dir/build: tests/test_util_file

.PHONY : tests/CMakeFiles/test_util_file.dir/build

tests/CMakeFiles/test_util_file.dir/clean:
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" && $(CMAKE_COMMAND) -P CMakeFiles/test_util_file.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_util_file.dir/clean

tests/CMakeFiles/test_util_file.dir/depend:
	cd "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c" "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c" "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests" "/home/ilya/Рабочий стол/eltex/Sob_eltex/lib/json-c/tests/CMakeFiles/test_util_file.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_util_file.dir/depend

