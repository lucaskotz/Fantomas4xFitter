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
include pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/compiler_depend.make

# Include the progress variables for this target.
include pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/progress.make

# Include the compile flags for this target's objects.
include pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/flags.make

pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o: pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/flags.make
pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o: ../pdfdecomps/LHAPDF/LHAPDFDecomposition.cc
pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o: pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o -MF CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o.d -o CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o -c /users/olness/git/fantomas/lucas/Fantomas4xFitter/pdfdecomps/LHAPDF/LHAPDFDecomposition.cc

pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.i"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/olness/git/fantomas/lucas/Fantomas4xFitter/pdfdecomps/LHAPDF/LHAPDFDecomposition.cc > CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.i

pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.s"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF && /usr/bin/X11/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/olness/git/fantomas/lucas/Fantomas4xFitter/pdfdecomps/LHAPDF/LHAPDFDecomposition.cc -o CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.s

# Object files for target pdfdecompLHAPDF
pdfdecompLHAPDF_OBJECTS = \
"CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o"

# External object files for target pdfdecompLHAPDF
pdfdecompLHAPDF_EXTERNAL_OBJECTS =

pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/LHAPDFDecomposition.cc.o
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/build.make
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: src/libxfitter.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /usr/local/lib/libLHAPDF.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libCore.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libCore.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libImt.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libRIO.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libNet.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libHist.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGraf.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGraf3d.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libGpad.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libROOTDataFrame.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libTree.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libTreePlayer.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libRint.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libPostscript.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMatrix.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libPhysics.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMathCore.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libThread.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libMultiProc.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: /users/olness/root/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4/lib/libROOTVecOps.so
pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so: pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/olness/git/fantomas/lucas/Fantomas4xFitter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libpdfdecompLHAPDF.so"
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdfdecompLHAPDF.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/build: pdfdecomps/LHAPDF/libpdfdecompLHAPDF.so
.PHONY : pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/build

pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/clean:
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF && $(CMAKE_COMMAND) -P CMakeFiles/pdfdecompLHAPDF.dir/cmake_clean.cmake
.PHONY : pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/clean

pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/depend:
	cd /users/olness/git/fantomas/lucas/Fantomas4xFitter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/olness/git/fantomas/lucas/Fantomas4xFitter /users/olness/git/fantomas/lucas/Fantomas4xFitter/pdfdecomps/LHAPDF /users/olness/git/fantomas/lucas/Fantomas4xFitter/build /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF /users/olness/git/fantomas/lucas/Fantomas4xFitter/build/pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pdfdecomps/LHAPDF/CMakeFiles/pdfdecompLHAPDF.dir/depend
