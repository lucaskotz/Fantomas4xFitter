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
CMAKE_SOURCE_DIR = /users/olness/git/fantomas/lucas/Fantomas4xFitter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users/olness/git/fantomas/lucas/Fantomas4xFitter/build

# Include any dependencies generated for this target.
include reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/compiler_depend.make

# Include the progress variables for this target.
include reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/progress.make

# Include the compile flags for this target's objects.
include reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/flags.make

reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o: reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/flags.make
reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o: ../reactions/cbdiff/Reactioncbdiff.cc
reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o: reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o -MF CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o.d -o CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o -c /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/cbdiff/Reactioncbdiff.cc

reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.i"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/cbdiff/Reactioncbdiff.cc > CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.i

reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.s"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/cbdiff/Reactioncbdiff.cc -o CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.s

# Object files for target reactioncbdiff
reactioncbdiff_OBJECTS = \
"CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o"

# External object files for target reactioncbdiff
reactioncbdiff_EXTERNAL_OBJECTS =

reactions/cbdiff/libreactioncbdiff.so: reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/Reactioncbdiff.cc.o
reactions/cbdiff/libreactioncbdiff.so: reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/build.make
reactions/cbdiff/libreactioncbdiff.so: reactions/BaseHVQMNR/libreactionBaseHVQMNR.so
reactions/cbdiff/libreactioncbdiff.so: src/libxfitter.so
reactions/cbdiff/libreactioncbdiff.so: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libCore.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libCore.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libImt.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libRIO.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libNet.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libHist.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGraf.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGraf3d.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGpad.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libROOTDataFrame.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libTree.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libTreePlayer.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libRint.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libPostscript.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMatrix.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libPhysics.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMathCore.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libThread.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMultiProc.so
reactions/cbdiff/libreactioncbdiff.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libROOTVecOps.so
reactions/cbdiff/libreactioncbdiff.so: reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libreactioncbdiff.so"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reactioncbdiff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/build: reactions/cbdiff/libreactioncbdiff.so
.PHONY : reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/build

reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/clean:
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff && $(CMAKE_COMMAND) -P CMakeFiles/reactioncbdiff.dir/cmake_clean.cmake
.PHONY : reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/clean

reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/depend:
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/olness/git/fantomas/lucas/Fantomas4xFitter /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/cbdiff /users/olness/git/fantomas/lucas/Fantomas4xFitter/build /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : reactions/cbdiff/CMakeFiles/reactioncbdiff.dir/depend
