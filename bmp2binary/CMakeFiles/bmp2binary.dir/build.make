# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 2.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "c:\Program Files (x86)\CMake 2.8\bin\cmake.exe"

# The command to remove a file.
RM = "c:\Program Files (x86)\CMake 2.8\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "c:\Program Files (x86)\CMake 2.8\bin\cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Coding\reconstruct\bmp2binary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\reconstruct\bmp2binary

# Include any dependencies generated for this target.
include CMakeFiles/bmp2binary.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bmp2binary.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bmp2binary.dir/flags.make

CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj: CMakeFiles/bmp2binary.dir/flags.make
CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj: CMakeFiles/bmp2binary.dir/includes_CXX.rsp
CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj: bmp2binary.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\Coding\reconstruct\bmp2binary\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\bmp2binary.dir\bmp2binary.cpp.obj -c D:\Coding\reconstruct\bmp2binary\bmp2binary.cpp

CMakeFiles/bmp2binary.dir/bmp2binary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bmp2binary.dir/bmp2binary.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\Coding\reconstruct\bmp2binary\bmp2binary.cpp > CMakeFiles\bmp2binary.dir\bmp2binary.cpp.i

CMakeFiles/bmp2binary.dir/bmp2binary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bmp2binary.dir/bmp2binary.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\Coding\reconstruct\bmp2binary\bmp2binary.cpp -o CMakeFiles\bmp2binary.dir\bmp2binary.cpp.s

CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.requires:
.PHONY : CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.requires

CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.provides: CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.requires
	$(MAKE) -f CMakeFiles\bmp2binary.dir\build.make CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.provides.build
.PHONY : CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.provides

CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.provides.build: CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj

# Object files for target bmp2binary
bmp2binary_OBJECTS = \
"CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj"

# External object files for target bmp2binary
bmp2binary_EXTERNAL_OBJECTS =

bmp2binary.exe: CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj
bmp2binary.exe: CMakeFiles/bmp2binary.dir/build.make
bmp2binary.exe: CMakeFiles/bmp2binary.dir/objects1.rsp
bmp2binary.exe: CMakeFiles/bmp2binary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bmp2binary.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bmp2binary.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bmp2binary.dir/build: bmp2binary.exe
.PHONY : CMakeFiles/bmp2binary.dir/build

CMakeFiles/bmp2binary.dir/requires: CMakeFiles/bmp2binary.dir/bmp2binary.cpp.obj.requires
.PHONY : CMakeFiles/bmp2binary.dir/requires

CMakeFiles/bmp2binary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bmp2binary.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bmp2binary.dir/clean

CMakeFiles/bmp2binary.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\reconstruct\bmp2binary D:\Coding\reconstruct\bmp2binary D:\Coding\reconstruct\bmp2binary D:\Coding\reconstruct\bmp2binary D:\Coding\reconstruct\bmp2binary\CMakeFiles\bmp2binary.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bmp2binary.dir/depend

