# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/bijanadmin/development/eye-tracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bijanadmin/development/eye-tracker

# Include any dependencies generated for this target.
include CMakeFiles/eye-tracker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eye-tracker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eye-tracker.dir/flags.make

CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o: CMakeFiles/eye-tracker.dir/flags.make
CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o: eye-tracker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bijanadmin/development/eye-tracker/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o -c /home/bijanadmin/development/eye-tracker/eye-tracker.cpp

CMakeFiles/eye-tracker.dir/eye-tracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eye-tracker.dir/eye-tracker.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bijanadmin/development/eye-tracker/eye-tracker.cpp > CMakeFiles/eye-tracker.dir/eye-tracker.cpp.i

CMakeFiles/eye-tracker.dir/eye-tracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eye-tracker.dir/eye-tracker.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bijanadmin/development/eye-tracker/eye-tracker.cpp -o CMakeFiles/eye-tracker.dir/eye-tracker.cpp.s

CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.requires:
.PHONY : CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.requires

CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.provides: CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.requires
	$(MAKE) -f CMakeFiles/eye-tracker.dir/build.make CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.provides.build
.PHONY : CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.provides

CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.provides.build: CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o

# Object files for target eye-tracker
eye__tracker_OBJECTS = \
"CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o"

# External object files for target eye-tracker
eye__tracker_EXTERNAL_OBJECTS =

eye-tracker: CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o
eye-tracker: CMakeFiles/eye-tracker.dir/build.make
eye-tracker: /usr/local/lib/libopencv_viz.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_videostab.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_video.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_ts.a
eye-tracker: /usr/local/lib/libopencv_superres.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_stitching.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_photo.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_ocl.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_objdetect.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_nonfree.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_ml.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_legacy.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_imgproc.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_highgui.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_gpu.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_flann.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_features2d.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_core.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_contrib.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_calib3d.so.2.4.9
eye-tracker: /usr/lib/libflycapture.so
eye-tracker: /usr/lib/i386-linux-gnu/libGLU.so
eye-tracker: /usr/lib/i386-linux-gnu/libGL.so
eye-tracker: /usr/lib/i386-linux-gnu/libSM.so
eye-tracker: /usr/lib/i386-linux-gnu/libICE.so
eye-tracker: /usr/lib/i386-linux-gnu/libX11.so
eye-tracker: /usr/lib/i386-linux-gnu/libXext.so
eye-tracker: /usr/local/lib/libopencv_nonfree.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_ocl.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_gpu.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_photo.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_objdetect.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_legacy.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_video.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_ml.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_calib3d.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_features2d.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_highgui.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_imgproc.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_flann.so.2.4.9
eye-tracker: /usr/local/lib/libopencv_core.so.2.4.9
eye-tracker: CMakeFiles/eye-tracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable eye-tracker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eye-tracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eye-tracker.dir/build: eye-tracker
.PHONY : CMakeFiles/eye-tracker.dir/build

CMakeFiles/eye-tracker.dir/requires: CMakeFiles/eye-tracker.dir/eye-tracker.cpp.o.requires
.PHONY : CMakeFiles/eye-tracker.dir/requires

CMakeFiles/eye-tracker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eye-tracker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eye-tracker.dir/clean

CMakeFiles/eye-tracker.dir/depend:
	cd /home/bijanadmin/development/eye-tracker && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bijanadmin/development/eye-tracker /home/bijanadmin/development/eye-tracker /home/bijanadmin/development/eye-tracker /home/bijanadmin/development/eye-tracker /home/bijanadmin/development/eye-tracker/CMakeFiles/eye-tracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eye-tracker.dir/depend

