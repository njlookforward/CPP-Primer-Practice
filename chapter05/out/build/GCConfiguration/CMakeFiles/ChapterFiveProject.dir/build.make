# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\CPP_Primer_Project\chapter05

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration

# Include any dependencies generated for this target.
include CMakeFiles/ChapterFiveProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ChapterFiveProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ChapterFiveProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ChapterFiveProject.dir/flags.make

CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj: CMakeFiles/ChapterFiveProject.dir/flags.make
CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj: E:/CPP_Primer_Project/chapter05/ch05_main.cpp
CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj: CMakeFiles/ChapterFiveProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj -MF CMakeFiles\ChapterFiveProject.dir\ch05_main.cpp.obj.d -o CMakeFiles\ChapterFiveProject.dir\ch05_main.cpp.obj -c E:\CPP_Primer_Project\chapter05\ch05_main.cpp

CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CPP_Primer_Project\chapter05\ch05_main.cpp > CMakeFiles\ChapterFiveProject.dir\ch05_main.cpp.i

CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CPP_Primer_Project\chapter05\ch05_main.cpp -o CMakeFiles\ChapterFiveProject.dir\ch05_main.cpp.s

CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj: CMakeFiles/ChapterFiveProject.dir/flags.make
CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj: E:/CPP_Primer_Project/chapter05/Sales_item.cpp
CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj: CMakeFiles/ChapterFiveProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj -MF CMakeFiles\ChapterFiveProject.dir\Sales_item.cpp.obj.d -o CMakeFiles\ChapterFiveProject.dir\Sales_item.cpp.obj -c E:\CPP_Primer_Project\chapter05\Sales_item.cpp

CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CPP_Primer_Project\chapter05\Sales_item.cpp > CMakeFiles\ChapterFiveProject.dir\Sales_item.cpp.i

CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CPP_Primer_Project\chapter05\Sales_item.cpp -o CMakeFiles\ChapterFiveProject.dir\Sales_item.cpp.s

# Object files for target ChapterFiveProject
ChapterFiveProject_OBJECTS = \
"CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj" \
"CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj"

# External object files for target ChapterFiveProject
ChapterFiveProject_EXTERNAL_OBJECTS =

ChapterFiveProject.exe: CMakeFiles/ChapterFiveProject.dir/ch05_main.cpp.obj
ChapterFiveProject.exe: CMakeFiles/ChapterFiveProject.dir/Sales_item.cpp.obj
ChapterFiveProject.exe: CMakeFiles/ChapterFiveProject.dir/build.make
ChapterFiveProject.exe: CMakeFiles/ChapterFiveProject.dir/linkLibs.rsp
ChapterFiveProject.exe: CMakeFiles/ChapterFiveProject.dir/objects1.rsp
ChapterFiveProject.exe: CMakeFiles/ChapterFiveProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ChapterFiveProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ChapterFiveProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ChapterFiveProject.dir/build: ChapterFiveProject.exe
.PHONY : CMakeFiles/ChapterFiveProject.dir/build

CMakeFiles/ChapterFiveProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ChapterFiveProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ChapterFiveProject.dir/clean

CMakeFiles/ChapterFiveProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\CPP_Primer_Project\chapter05 E:\CPP_Primer_Project\chapter05 E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration E:\CPP_Primer_Project\chapter05\out\build\GCConfiguration\CMakeFiles\ChapterFiveProject.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ChapterFiveProject.dir/depend

