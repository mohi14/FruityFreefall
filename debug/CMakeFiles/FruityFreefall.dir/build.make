# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mohi/Developer/Projects/C++/FruityFreefall

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mohi/Developer/Projects/C++/FruityFreefall/debug

# Include any dependencies generated for this target.
include CMakeFiles/FruityFreefall.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FruityFreefall.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FruityFreefall.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FruityFreefall.dir/flags.make

CMakeFiles/FruityFreefall.dir/codegen:
.PHONY : CMakeFiles/FruityFreefall.dir/codegen

CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o: CMakeFiles/FruityFreefall.dir/flags.make
CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o: /Users/mohi/Developer/Projects/C++/FruityFreefall/src/core/GameManager.cpp
CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o: CMakeFiles/FruityFreefall.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mohi/Developer/Projects/C++/FruityFreefall/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o -MF CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o.d -o CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o -c /Users/mohi/Developer/Projects/C++/FruityFreefall/src/core/GameManager.cpp

CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mohi/Developer/Projects/C++/FruityFreefall/src/core/GameManager.cpp > CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.i

CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mohi/Developer/Projects/C++/FruityFreefall/src/core/GameManager.cpp -o CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.s

CMakeFiles/FruityFreefall.dir/src/main.cpp.o: CMakeFiles/FruityFreefall.dir/flags.make
CMakeFiles/FruityFreefall.dir/src/main.cpp.o: /Users/mohi/Developer/Projects/C++/FruityFreefall/src/main.cpp
CMakeFiles/FruityFreefall.dir/src/main.cpp.o: CMakeFiles/FruityFreefall.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mohi/Developer/Projects/C++/FruityFreefall/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FruityFreefall.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FruityFreefall.dir/src/main.cpp.o -MF CMakeFiles/FruityFreefall.dir/src/main.cpp.o.d -o CMakeFiles/FruityFreefall.dir/src/main.cpp.o -c /Users/mohi/Developer/Projects/C++/FruityFreefall/src/main.cpp

CMakeFiles/FruityFreefall.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/FruityFreefall.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mohi/Developer/Projects/C++/FruityFreefall/src/main.cpp > CMakeFiles/FruityFreefall.dir/src/main.cpp.i

CMakeFiles/FruityFreefall.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/FruityFreefall.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mohi/Developer/Projects/C++/FruityFreefall/src/main.cpp -o CMakeFiles/FruityFreefall.dir/src/main.cpp.s

# Object files for target FruityFreefall
FruityFreefall_OBJECTS = \
"CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o" \
"CMakeFiles/FruityFreefall.dir/src/main.cpp.o"

# External object files for target FruityFreefall
FruityFreefall_EXTERNAL_OBJECTS =

FruityFreefall: CMakeFiles/FruityFreefall.dir/src/core/GameManager.cpp.o
FruityFreefall: CMakeFiles/FruityFreefall.dir/src/main.cpp.o
FruityFreefall: CMakeFiles/FruityFreefall.dir/build.make
FruityFreefall: /opt/homebrew/lib/libsfml-graphics.3.0.1.dylib
FruityFreefall: /opt/homebrew/lib/libsfml-audio.3.0.1.dylib
FruityFreefall: /opt/homebrew/lib/libsfml-network.3.0.1.dylib
FruityFreefall: /opt/homebrew/lib/libsfml-window.3.0.1.dylib
FruityFreefall: /opt/homebrew/lib/libsfml-system.3.0.1.dylib
FruityFreefall: CMakeFiles/FruityFreefall.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mohi/Developer/Projects/C++/FruityFreefall/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable FruityFreefall"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FruityFreefall.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/bin/cmake -E copy_directory /Users/mohi/Developer/Projects/C++/FruityFreefall/assets /Users/mohi/Developer/Projects/C++/FruityFreefall/debug/assets

# Rule to build all files generated by this target.
CMakeFiles/FruityFreefall.dir/build: FruityFreefall
.PHONY : CMakeFiles/FruityFreefall.dir/build

CMakeFiles/FruityFreefall.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FruityFreefall.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FruityFreefall.dir/clean

CMakeFiles/FruityFreefall.dir/depend:
	cd /Users/mohi/Developer/Projects/C++/FruityFreefall/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mohi/Developer/Projects/C++/FruityFreefall /Users/mohi/Developer/Projects/C++/FruityFreefall /Users/mohi/Developer/Projects/C++/FruityFreefall/debug /Users/mohi/Developer/Projects/C++/FruityFreefall/debug /Users/mohi/Developer/Projects/C++/FruityFreefall/debug/CMakeFiles/FruityFreefall.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/FruityFreefall.dir/depend

