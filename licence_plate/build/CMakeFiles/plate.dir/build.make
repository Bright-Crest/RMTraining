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
CMAKE_SOURCE_DIR = /home/rmv/VScode/RMTraining/licence_plate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rmv/VScode/RMTraining/licence_plate/build

# Include any dependencies generated for this target.
include CMakeFiles/plate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plate.dir/flags.make

CMakeFiles/plate.dir/main.cpp.o: CMakeFiles/plate.dir/flags.make
CMakeFiles/plate.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rmv/VScode/RMTraining/licence_plate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/plate.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plate.dir/main.cpp.o -c /home/rmv/VScode/RMTraining/licence_plate/main.cpp

CMakeFiles/plate.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plate.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rmv/VScode/RMTraining/licence_plate/main.cpp > CMakeFiles/plate.dir/main.cpp.i

CMakeFiles/plate.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plate.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rmv/VScode/RMTraining/licence_plate/main.cpp -o CMakeFiles/plate.dir/main.cpp.s

CMakeFiles/plate.dir/detector.cpp.o: CMakeFiles/plate.dir/flags.make
CMakeFiles/plate.dir/detector.cpp.o: ../detector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rmv/VScode/RMTraining/licence_plate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/plate.dir/detector.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plate.dir/detector.cpp.o -c /home/rmv/VScode/RMTraining/licence_plate/detector.cpp

CMakeFiles/plate.dir/detector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plate.dir/detector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rmv/VScode/RMTraining/licence_plate/detector.cpp > CMakeFiles/plate.dir/detector.cpp.i

CMakeFiles/plate.dir/detector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plate.dir/detector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rmv/VScode/RMTraining/licence_plate/detector.cpp -o CMakeFiles/plate.dir/detector.cpp.s

# Object files for target plate
plate_OBJECTS = \
"CMakeFiles/plate.dir/main.cpp.o" \
"CMakeFiles/plate.dir/detector.cpp.o"

# External object files for target plate
plate_EXTERNAL_OBJECTS =

plate: CMakeFiles/plate.dir/main.cpp.o
plate: CMakeFiles/plate.dir/detector.cpp.o
plate: CMakeFiles/plate.dir/build.make
plate: /usr/local/lib/libopencv_stitching.so.4.4.0
plate: /usr/local/lib/libopencv_alphamat.so.4.4.0
plate: /usr/local/lib/libopencv_aruco.so.4.4.0
plate: /usr/local/lib/libopencv_bgsegm.so.4.4.0
plate: /usr/local/lib/libopencv_bioinspired.so.4.4.0
plate: /usr/local/lib/libopencv_ccalib.so.4.4.0
plate: /usr/local/lib/libopencv_dnn_objdetect.so.4.4.0
plate: /usr/local/lib/libopencv_dnn_superres.so.4.4.0
plate: /usr/local/lib/libopencv_dpm.so.4.4.0
plate: /usr/local/lib/libopencv_face.so.4.4.0
plate: /usr/local/lib/libopencv_freetype.so.4.4.0
plate: /usr/local/lib/libopencv_fuzzy.so.4.4.0
plate: /usr/local/lib/libopencv_hfs.so.4.4.0
plate: /usr/local/lib/libopencv_img_hash.so.4.4.0
plate: /usr/local/lib/libopencv_intensity_transform.so.4.4.0
plate: /usr/local/lib/libopencv_line_descriptor.so.4.4.0
plate: /usr/local/lib/libopencv_quality.so.4.4.0
plate: /usr/local/lib/libopencv_rapid.so.4.4.0
plate: /usr/local/lib/libopencv_reg.so.4.4.0
plate: /usr/local/lib/libopencv_rgbd.so.4.4.0
plate: /usr/local/lib/libopencv_saliency.so.4.4.0
plate: /usr/local/lib/libopencv_sfm.so.4.4.0
plate: /usr/local/lib/libopencv_stereo.so.4.4.0
plate: /usr/local/lib/libopencv_structured_light.so.4.4.0
plate: /usr/local/lib/libopencv_superres.so.4.4.0
plate: /usr/local/lib/libopencv_surface_matching.so.4.4.0
plate: /usr/local/lib/libopencv_tracking.so.4.4.0
plate: /usr/local/lib/libopencv_videostab.so.4.4.0
plate: /usr/local/lib/libopencv_xfeatures2d.so.4.4.0
plate: /usr/local/lib/libopencv_xobjdetect.so.4.4.0
plate: /usr/local/lib/libopencv_xphoto.so.4.4.0
plate: /usr/local/lib/libopencv_highgui.so.4.4.0
plate: /usr/local/lib/libopencv_shape.so.4.4.0
plate: /usr/local/lib/libopencv_datasets.so.4.4.0
plate: /usr/local/lib/libopencv_plot.so.4.4.0
plate: /usr/local/lib/libopencv_text.so.4.4.0
plate: /usr/local/lib/libopencv_dnn.so.4.4.0
plate: /usr/local/lib/libopencv_ml.so.4.4.0
plate: /usr/local/lib/libopencv_phase_unwrapping.so.4.4.0
plate: /usr/local/lib/libopencv_optflow.so.4.4.0
plate: /usr/local/lib/libopencv_ximgproc.so.4.4.0
plate: /usr/local/lib/libopencv_video.so.4.4.0
plate: /usr/local/lib/libopencv_videoio.so.4.4.0
plate: /usr/local/lib/libopencv_imgcodecs.so.4.4.0
plate: /usr/local/lib/libopencv_objdetect.so.4.4.0
plate: /usr/local/lib/libopencv_calib3d.so.4.4.0
plate: /usr/local/lib/libopencv_features2d.so.4.4.0
plate: /usr/local/lib/libopencv_flann.so.4.4.0
plate: /usr/local/lib/libopencv_photo.so.4.4.0
plate: /usr/local/lib/libopencv_imgproc.so.4.4.0
plate: /usr/local/lib/libopencv_core.so.4.4.0
plate: CMakeFiles/plate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rmv/VScode/RMTraining/licence_plate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable plate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plate.dir/build: plate

.PHONY : CMakeFiles/plate.dir/build

CMakeFiles/plate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plate.dir/clean

CMakeFiles/plate.dir/depend:
	cd /home/rmv/VScode/RMTraining/licence_plate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rmv/VScode/RMTraining/licence_plate /home/rmv/VScode/RMTraining/licence_plate /home/rmv/VScode/RMTraining/licence_plate/build /home/rmv/VScode/RMTraining/licence_plate/build /home/rmv/VScode/RMTraining/licence_plate/build/CMakeFiles/plate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plate.dir/depend

