# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/darya/cxx_projects/parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/darya/cxx_projects/parser/build

# Include any dependencies generated for this target.
include CMakeFiles/URL_Parser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/URL_Parser.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/URL_Parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/URL_Parser.dir/flags.make

CMakeFiles/URL_Parser.dir/parser_test.cpp.o: CMakeFiles/URL_Parser.dir/flags.make
CMakeFiles/URL_Parser.dir/parser_test.cpp.o: ../parser_test.cpp
CMakeFiles/URL_Parser.dir/parser_test.cpp.o: CMakeFiles/URL_Parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/cxx_projects/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/URL_Parser.dir/parser_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/URL_Parser.dir/parser_test.cpp.o -MF CMakeFiles/URL_Parser.dir/parser_test.cpp.o.d -o CMakeFiles/URL_Parser.dir/parser_test.cpp.o -c /home/darya/cxx_projects/parser/parser_test.cpp

CMakeFiles/URL_Parser.dir/parser_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/URL_Parser.dir/parser_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/cxx_projects/parser/parser_test.cpp > CMakeFiles/URL_Parser.dir/parser_test.cpp.i

CMakeFiles/URL_Parser.dir/parser_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/URL_Parser.dir/parser_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/cxx_projects/parser/parser_test.cpp -o CMakeFiles/URL_Parser.dir/parser_test.cpp.s

CMakeFiles/URL_Parser.dir/parser.cpp.o: CMakeFiles/URL_Parser.dir/flags.make
CMakeFiles/URL_Parser.dir/parser.cpp.o: ../parser.cpp
CMakeFiles/URL_Parser.dir/parser.cpp.o: CMakeFiles/URL_Parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/cxx_projects/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/URL_Parser.dir/parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/URL_Parser.dir/parser.cpp.o -MF CMakeFiles/URL_Parser.dir/parser.cpp.o.d -o CMakeFiles/URL_Parser.dir/parser.cpp.o -c /home/darya/cxx_projects/parser/parser.cpp

CMakeFiles/URL_Parser.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/URL_Parser.dir/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/cxx_projects/parser/parser.cpp > CMakeFiles/URL_Parser.dir/parser.cpp.i

CMakeFiles/URL_Parser.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/URL_Parser.dir/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/cxx_projects/parser/parser.cpp -o CMakeFiles/URL_Parser.dir/parser.cpp.s

# Object files for target URL_Parser
URL_Parser_OBJECTS = \
"CMakeFiles/URL_Parser.dir/parser_test.cpp.o" \
"CMakeFiles/URL_Parser.dir/parser.cpp.o"

# External object files for target URL_Parser
URL_Parser_EXTERNAL_OBJECTS =

URL_Parser: CMakeFiles/URL_Parser.dir/parser_test.cpp.o
URL_Parser: CMakeFiles/URL_Parser.dir/parser.cpp.o
URL_Parser: CMakeFiles/URL_Parser.dir/build.make
URL_Parser: /usr/lib/x86_64-linux-gnu/libgtest.a
URL_Parser: CMakeFiles/URL_Parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/darya/cxx_projects/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable URL_Parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/URL_Parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/URL_Parser.dir/build: URL_Parser
.PHONY : CMakeFiles/URL_Parser.dir/build

CMakeFiles/URL_Parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/URL_Parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/URL_Parser.dir/clean

CMakeFiles/URL_Parser.dir/depend:
	cd /home/darya/cxx_projects/parser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/darya/cxx_projects/parser /home/darya/cxx_projects/parser /home/darya/cxx_projects/parser/build /home/darya/cxx_projects/parser/build /home/darya/cxx_projects/parser/build/CMakeFiles/URL_Parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/URL_Parser.dir/depend

