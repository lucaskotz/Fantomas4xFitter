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
include reactions/CIJET/CMakeFiles/reactionCIJET.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include reactions/CIJET/CMakeFiles/reactionCIJET.dir/compiler_depend.make

# Include the progress variables for this target.
include reactions/CIJET/CMakeFiles/reactionCIJET.dir/progress.make

# Include the compile flags for this target's objects.
include reactions/CIJET/CMakeFiles/reactionCIJET.dir/flags.make

reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o: reactions/CIJET/CMakeFiles/reactionCIJET.dir/flags.make
reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o: ../reactions/CIJET/ReactionCIJET.cc
reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o: reactions/CIJET/CMakeFiles/reactionCIJET.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o -MF CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o.d -o CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o -c /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/ReactionCIJET.cc

reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.i"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/ReactionCIJET.cc > CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.i

reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.s"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/ReactionCIJET.cc -o CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.s

reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o: reactions/CIJET/CMakeFiles/reactionCIJET.dir/flags.make
reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o: ../reactions/CIJET/CIJETReader.cc
reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o: reactions/CIJET/CMakeFiles/reactionCIJET.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o -MF CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o.d -o CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o -c /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/CIJETReader.cc

reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reactionCIJET.dir/CIJETReader.cc.i"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/CIJETReader.cc > CMakeFiles/reactionCIJET.dir/CIJETReader.cc.i

reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reactionCIJET.dir/CIJETReader.cc.s"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/CIJETReader.cc -o CMakeFiles/reactionCIJET.dir/CIJETReader.cc.s

reactions/CIJET/CMakeFiles/reactionCIJET.dir/cijet.f.o: reactions/CIJET/CMakeFiles/reactionCIJET.dir/flags.make
reactions/CIJET/CMakeFiles/reactionCIJET.dir/cijet.f.o: ../reactions/CIJET/cijet.f
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building Fortran object reactions/CIJET/CMakeFiles/reactionCIJET.dir/cijet.f.o"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/cijet.f -o CMakeFiles/reactionCIJET.dir/cijet.f.o

reactions/CIJET/CMakeFiles/reactionCIJET.dir/cijet.f.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/reactionCIJET.dir/cijet.f.i"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/cijet.f > CMakeFiles/reactionCIJET.dir/cijet.f.i

reactions/CIJET/CMakeFiles/reactionCIJET.dir/cijet.f.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/reactionCIJET.dir/cijet.f.s"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && /usr/bin/X11/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET/cijet.f -o CMakeFiles/reactionCIJET.dir/cijet.f.s

# Object files for target reactionCIJET
reactionCIJET_OBJECTS = \
"CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o" \
"CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o" \
"CMakeFiles/reactionCIJET.dir/cijet.f.o"

# External object files for target reactionCIJET
reactionCIJET_EXTERNAL_OBJECTS =

reactions/CIJET/libreactionCIJET.so: reactions/CIJET/CMakeFiles/reactionCIJET.dir/ReactionCIJET.cc.o
reactions/CIJET/libreactionCIJET.so: reactions/CIJET/CMakeFiles/reactionCIJET.dir/CIJETReader.cc.o
reactions/CIJET/libreactionCIJET.so: reactions/CIJET/CMakeFiles/reactionCIJET.dir/cijet.f.o
reactions/CIJET/libreactionCIJET.so: reactions/CIJET/CMakeFiles/reactionCIJET.dir/build.make
reactions/CIJET/libreactionCIJET.so: src/libxfitter.so
reactions/CIJET/libreactionCIJET.so: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libCore.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libCore.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libImt.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libRIO.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libNet.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libHist.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGraf.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGraf3d.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGpad.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libROOTDataFrame.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libTree.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libTreePlayer.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libRint.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libPostscript.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMatrix.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libPhysics.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMathCore.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libThread.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMultiProc.so
reactions/CIJET/libreactionCIJET.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libROOTVecOps.so
reactions/CIJET/libreactionCIJET.so: reactions/CIJET/CMakeFiles/reactionCIJET.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared module libreactionCIJET.so"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reactionCIJET.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
reactions/CIJET/CMakeFiles/reactionCIJET.dir/build: reactions/CIJET/libreactionCIJET.so
.PHONY : reactions/CIJET/CMakeFiles/reactionCIJET.dir/build

reactions/CIJET/CMakeFiles/reactionCIJET.dir/clean:
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET && $(CMAKE_COMMAND) -P CMakeFiles/reactionCIJET.dir/cmake_clean.cmake
.PHONY : reactions/CIJET/CMakeFiles/reactionCIJET.dir/clean

reactions/CIJET/CMakeFiles/reactionCIJET.dir/depend:
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/olness/git/fantomas/lucas/Fantomas4xFitter /users/olness/git/fantomas/lucas/Fantomas4xFitter/reactions/CIJET /users/olness/git/fantomas/lucas/Fantomas4xFitter/build /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/reactions/CIJET/CMakeFiles/reactionCIJET.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : reactions/CIJET/CMakeFiles/reactionCIJET.dir/depend
