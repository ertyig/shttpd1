# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\leechain\CLionProjects\shttpd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/shttpd.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/shttpd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shttpd.dir/flags.make

CMakeFiles/shttpd.dir/shttpd.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd.c.obj: ../shttpd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shttpd.dir/shttpd.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd.c

CMakeFiles/shttpd.dir/shttpd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd.c > CMakeFiles\shttpd.dir\shttpd.c.i

CMakeFiles/shttpd.dir/shttpd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd.c -o CMakeFiles\shttpd.dir\shttpd.c.s

CMakeFiles/shttpd.dir/shttpd_parameters.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_parameters.c.obj: ../shttpd_parameters.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shttpd.dir/shttpd_parameters.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_parameters.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_parameters.c

CMakeFiles/shttpd.dir/shttpd_parameters.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_parameters.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_parameters.c > CMakeFiles\shttpd.dir\shttpd_parameters.c.i

CMakeFiles/shttpd.dir/shttpd_parameters.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_parameters.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_parameters.c -o CMakeFiles\shttpd.dir\shttpd_parameters.c.s

CMakeFiles/shttpd.dir/shttpd_worker.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_worker.c.obj: ../shttpd_worker.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/shttpd.dir/shttpd_worker.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_worker.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_worker.c

CMakeFiles/shttpd.dir/shttpd_worker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_worker.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_worker.c > CMakeFiles\shttpd.dir\shttpd_worker.c.i

CMakeFiles/shttpd.dir/shttpd_worker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_worker.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_worker.c -o CMakeFiles\shttpd.dir\shttpd_worker.c.s

CMakeFiles/shttpd.dir/shttpd_cgi.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_cgi.c.obj: ../shttpd_cgi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/shttpd.dir/shttpd_cgi.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_cgi.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_cgi.c

CMakeFiles/shttpd.dir/shttpd_cgi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_cgi.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_cgi.c > CMakeFiles\shttpd.dir\shttpd_cgi.c.i

CMakeFiles/shttpd.dir/shttpd_cgi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_cgi.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_cgi.c -o CMakeFiles\shttpd.dir\shttpd_cgi.c.s

CMakeFiles/shttpd.dir/shttpd_error.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_error.c.obj: ../shttpd_error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/shttpd.dir/shttpd_error.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_error.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_error.c

CMakeFiles/shttpd.dir/shttpd_error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_error.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_error.c > CMakeFiles\shttpd.dir\shttpd_error.c.i

CMakeFiles/shttpd.dir/shttpd_error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_error.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_error.c -o CMakeFiles\shttpd.dir\shttpd_error.c.s

CMakeFiles/shttpd.dir/shttpd_request.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_request.c.obj: ../shttpd_request.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/shttpd.dir/shttpd_request.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_request.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_request.c

CMakeFiles/shttpd.dir/shttpd_request.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_request.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_request.c > CMakeFiles\shttpd.dir\shttpd_request.c.i

CMakeFiles/shttpd.dir/shttpd_request.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_request.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_request.c -o CMakeFiles\shttpd.dir\shttpd_request.c.s

CMakeFiles/shttpd.dir/shttpd_method.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_method.c.obj: ../shttpd_method.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/shttpd.dir/shttpd_method.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_method.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_method.c

CMakeFiles/shttpd.dir/shttpd_method.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_method.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_method.c > CMakeFiles\shttpd.dir\shttpd_method.c.i

CMakeFiles/shttpd.dir/shttpd_method.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_method.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_method.c -o CMakeFiles\shttpd.dir\shttpd_method.c.s

CMakeFiles/shttpd.dir/shttpd_mine.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_mine.c.obj: ../shttpd_mine.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/shttpd.dir/shttpd_mine.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_mine.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_mine.c

CMakeFiles/shttpd.dir/shttpd_mine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_mine.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_mine.c > CMakeFiles\shttpd.dir\shttpd_mine.c.i

CMakeFiles/shttpd.dir/shttpd_mine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_mine.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_mine.c -o CMakeFiles\shttpd.dir\shttpd_mine.c.s

CMakeFiles/shttpd.dir/shttpd_uri.c.obj: CMakeFiles/shttpd.dir/flags.make
CMakeFiles/shttpd.dir/shttpd_uri.c.obj: ../shttpd_uri.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/shttpd.dir/shttpd_uri.c.obj"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shttpd.dir\shttpd_uri.c.obj -c C:\Users\leechain\CLionProjects\shttpd\shttpd_uri.c

CMakeFiles/shttpd.dir/shttpd_uri.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shttpd.dir/shttpd_uri.c.i"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\leechain\CLionProjects\shttpd\shttpd_uri.c > CMakeFiles\shttpd.dir\shttpd_uri.c.i

CMakeFiles/shttpd.dir/shttpd_uri.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shttpd.dir/shttpd_uri.c.s"
	D:\Downloads\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\leechain\CLionProjects\shttpd\shttpd_uri.c -o CMakeFiles\shttpd.dir\shttpd_uri.c.s

# Object files for target shttpd
shttpd_OBJECTS = \
"CMakeFiles/shttpd.dir/shttpd.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_parameters.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_worker.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_cgi.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_error.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_request.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_method.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_mine.c.obj" \
"CMakeFiles/shttpd.dir/shttpd_uri.c.obj"

# External object files for target shttpd
shttpd_EXTERNAL_OBJECTS =

shttpd.exe: CMakeFiles/shttpd.dir/shttpd.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_parameters.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_worker.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_cgi.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_error.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_request.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_method.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_mine.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/shttpd_uri.c.obj
shttpd.exe: CMakeFiles/shttpd.dir/build.make
shttpd.exe: CMakeFiles/shttpd.dir/linklibs.rsp
shttpd.exe: CMakeFiles/shttpd.dir/objects1.rsp
shttpd.exe: CMakeFiles/shttpd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable shttpd.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\shttpd.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shttpd.dir/build: shttpd.exe
.PHONY : CMakeFiles/shttpd.dir/build

CMakeFiles/shttpd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\shttpd.dir\cmake_clean.cmake
.PHONY : CMakeFiles/shttpd.dir/clean

CMakeFiles/shttpd.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\leechain\CLionProjects\shttpd C:\Users\leechain\CLionProjects\shttpd C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug C:\Users\leechain\CLionProjects\shttpd\cmake-build-debug\CMakeFiles\shttpd.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shttpd.dir/depend

