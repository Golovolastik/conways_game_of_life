# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "/Users/aleksejankovic/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/aleksejankovic/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/conways_game_of_life.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/conways_game_of_life.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conways_game_of_life.dir/flags.make

CMakeFiles/conways_game_of_life.dir/main.c.o: CMakeFiles/conways_game_of_life.dir/flags.make
CMakeFiles/conways_game_of_life.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/conways_game_of_life.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/conways_game_of_life.dir/main.c.o -c "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/main.c"

CMakeFiles/conways_game_of_life.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conways_game_of_life.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/main.c" > CMakeFiles/conways_game_of_life.dir/main.c.i

CMakeFiles/conways_game_of_life.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conways_game_of_life.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/main.c" -o CMakeFiles/conways_game_of_life.dir/main.c.s

CMakeFiles/conways_game_of_life.dir/functions.c.o: CMakeFiles/conways_game_of_life.dir/flags.make
CMakeFiles/conways_game_of_life.dir/functions.c.o: ../functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/conways_game_of_life.dir/functions.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/conways_game_of_life.dir/functions.c.o -c "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/functions.c"

CMakeFiles/conways_game_of_life.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conways_game_of_life.dir/functions.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/functions.c" > CMakeFiles/conways_game_of_life.dir/functions.c.i

CMakeFiles/conways_game_of_life.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conways_game_of_life.dir/functions.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/functions.c" -o CMakeFiles/conways_game_of_life.dir/functions.c.s

# Object files for target conways_game_of_life
conways_game_of_life_OBJECTS = \
"CMakeFiles/conways_game_of_life.dir/main.c.o" \
"CMakeFiles/conways_game_of_life.dir/functions.c.o"

# External object files for target conways_game_of_life
conways_game_of_life_EXTERNAL_OBJECTS =

conways_game_of_life: CMakeFiles/conways_game_of_life.dir/main.c.o
conways_game_of_life: CMakeFiles/conways_game_of_life.dir/functions.c.o
conways_game_of_life: CMakeFiles/conways_game_of_life.dir/build.make
conways_game_of_life: /opt/homebrew/lib/libpng.dylib
conways_game_of_life: CMakeFiles/conways_game_of_life.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable conways_game_of_life"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conways_game_of_life.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conways_game_of_life.dir/build: conways_game_of_life
.PHONY : CMakeFiles/conways_game_of_life.dir/build

CMakeFiles/conways_game_of_life.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conways_game_of_life.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conways_game_of_life.dir/clean

CMakeFiles/conways_game_of_life.dir/depend:
	cd "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life" "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life" "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug" "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug" "/Users/aleksejankovic/Desktop/Study/bsuir/2курс/Конструирование ПО/2sem/Курсач/main_work/conways_game_of_life/cmake-build-debug/CMakeFiles/conways_game_of_life.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/conways_game_of_life.dir/depend

