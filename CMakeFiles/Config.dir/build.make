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
CMAKE_SOURCE_DIR = /home/sergey/Config

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sergey/Config

# Include any dependencies generated for this target.
include CMakeFiles/Config.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Config.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Config.dir/flags.make

CMakeFiles/Config.dir/main.cpp.o: CMakeFiles/Config.dir/flags.make
CMakeFiles/Config.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sergey/Config/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Config.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Config.dir/main.cpp.o -c /home/sergey/Config/main.cpp

CMakeFiles/Config.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Config.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sergey/Config/main.cpp > CMakeFiles/Config.dir/main.cpp.i

CMakeFiles/Config.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Config.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sergey/Config/main.cpp -o CMakeFiles/Config.dir/main.cpp.s

# Object files for target Config
Config_OBJECTS = \
"CMakeFiles/Config.dir/main.cpp.o"

# External object files for target Config
Config_EXTERNAL_OBJECTS =

Config: CMakeFiles/Config.dir/main.cpp.o
Config: CMakeFiles/Config.dir/build.make
Config: CMakeFiles/Config.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sergey/Config/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Config"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Config.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Config.dir/build: Config

.PHONY : CMakeFiles/Config.dir/build

CMakeFiles/Config.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Config.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Config.dir/clean

CMakeFiles/Config.dir/depend:
	cd /home/sergey/Config && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sergey/Config /home/sergey/Config /home/sergey/Config /home/sergey/Config /home/sergey/Config/CMakeFiles/Config.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Config.dir/depend
