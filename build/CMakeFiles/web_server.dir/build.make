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
CMAKE_SOURCE_DIR = /home/ambitionyc/mything/create_my_sever/WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ambitionyc/mything/create_my_sever/WebServer/build

# Include any dependencies generated for this target.
include CMakeFiles/web_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/web_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/web_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/web_server.dir/flags.make

CMakeFiles/web_server.dir/main.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/main.o: ../main.cpp
CMakeFiles/web_server.dir/main.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/web_server.dir/main.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/main.o -MF CMakeFiles/web_server.dir/main.o.d -o CMakeFiles/web_server.dir/main.o -c /home/ambitionyc/mything/create_my_sever/WebServer/main.cpp

CMakeFiles/web_server.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/main.cpp > CMakeFiles/web_server.dir/main.i

CMakeFiles/web_server.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/main.cpp -o CMakeFiles/web_server.dir/main.s

CMakeFiles/web_server.dir/src/channel.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/channel.o: ../src/channel.cpp
CMakeFiles/web_server.dir/src/channel.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/web_server.dir/src/channel.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/channel.o -MF CMakeFiles/web_server.dir/src/channel.o.d -o CMakeFiles/web_server.dir/src/channel.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/channel.cpp

CMakeFiles/web_server.dir/src/channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/channel.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/channel.cpp > CMakeFiles/web_server.dir/src/channel.i

CMakeFiles/web_server.dir/src/channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/channel.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/channel.cpp -o CMakeFiles/web_server.dir/src/channel.s

CMakeFiles/web_server.dir/src/count_down_latch.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/count_down_latch.o: ../src/count_down_latch.cpp
CMakeFiles/web_server.dir/src/count_down_latch.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/web_server.dir/src/count_down_latch.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/count_down_latch.o -MF CMakeFiles/web_server.dir/src/count_down_latch.o.d -o CMakeFiles/web_server.dir/src/count_down_latch.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/count_down_latch.cpp

CMakeFiles/web_server.dir/src/count_down_latch.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/count_down_latch.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/count_down_latch.cpp > CMakeFiles/web_server.dir/src/count_down_latch.i

CMakeFiles/web_server.dir/src/count_down_latch.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/count_down_latch.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/count_down_latch.cpp -o CMakeFiles/web_server.dir/src/count_down_latch.s

CMakeFiles/web_server.dir/src/current_thread.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/current_thread.o: ../src/current_thread.cpp
CMakeFiles/web_server.dir/src/current_thread.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/web_server.dir/src/current_thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/current_thread.o -MF CMakeFiles/web_server.dir/src/current_thread.o.d -o CMakeFiles/web_server.dir/src/current_thread.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/current_thread.cpp

CMakeFiles/web_server.dir/src/current_thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/current_thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/current_thread.cpp > CMakeFiles/web_server.dir/src/current_thread.i

CMakeFiles/web_server.dir/src/current_thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/current_thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/current_thread.cpp -o CMakeFiles/web_server.dir/src/current_thread.s

CMakeFiles/web_server.dir/src/epoll.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/epoll.o: ../src/epoll.cpp
CMakeFiles/web_server.dir/src/epoll.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/web_server.dir/src/epoll.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/epoll.o -MF CMakeFiles/web_server.dir/src/epoll.o.d -o CMakeFiles/web_server.dir/src/epoll.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/epoll.cpp

CMakeFiles/web_server.dir/src/epoll.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/epoll.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/epoll.cpp > CMakeFiles/web_server.dir/src/epoll.i

CMakeFiles/web_server.dir/src/epoll.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/epoll.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/epoll.cpp -o CMakeFiles/web_server.dir/src/epoll.s

CMakeFiles/web_server.dir/src/eventloop.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/eventloop.o: ../src/eventloop.cpp
CMakeFiles/web_server.dir/src/eventloop.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/web_server.dir/src/eventloop.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/eventloop.o -MF CMakeFiles/web_server.dir/src/eventloop.o.d -o CMakeFiles/web_server.dir/src/eventloop.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop.cpp

CMakeFiles/web_server.dir/src/eventloop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/eventloop.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop.cpp > CMakeFiles/web_server.dir/src/eventloop.i

CMakeFiles/web_server.dir/src/eventloop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/eventloop.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop.cpp -o CMakeFiles/web_server.dir/src/eventloop.s

CMakeFiles/web_server.dir/src/eventloop_thread.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/eventloop_thread.o: ../src/eventloop_thread.cpp
CMakeFiles/web_server.dir/src/eventloop_thread.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/web_server.dir/src/eventloop_thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/eventloop_thread.o -MF CMakeFiles/web_server.dir/src/eventloop_thread.o.d -o CMakeFiles/web_server.dir/src/eventloop_thread.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop_thread.cpp

CMakeFiles/web_server.dir/src/eventloop_thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/eventloop_thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop_thread.cpp > CMakeFiles/web_server.dir/src/eventloop_thread.i

CMakeFiles/web_server.dir/src/eventloop_thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/eventloop_thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop_thread.cpp -o CMakeFiles/web_server.dir/src/eventloop_thread.s

CMakeFiles/web_server.dir/src/eventloop_thread_pool.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/eventloop_thread_pool.o: ../src/eventloop_thread_pool.cpp
CMakeFiles/web_server.dir/src/eventloop_thread_pool.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/web_server.dir/src/eventloop_thread_pool.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/eventloop_thread_pool.o -MF CMakeFiles/web_server.dir/src/eventloop_thread_pool.o.d -o CMakeFiles/web_server.dir/src/eventloop_thread_pool.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop_thread_pool.cpp

CMakeFiles/web_server.dir/src/eventloop_thread_pool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/eventloop_thread_pool.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop_thread_pool.cpp > CMakeFiles/web_server.dir/src/eventloop_thread_pool.i

CMakeFiles/web_server.dir/src/eventloop_thread_pool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/eventloop_thread_pool.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/eventloop_thread_pool.cpp -o CMakeFiles/web_server.dir/src/eventloop_thread_pool.s

CMakeFiles/web_server.dir/src/httpdata.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/httpdata.o: ../src/httpdata.cpp
CMakeFiles/web_server.dir/src/httpdata.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/web_server.dir/src/httpdata.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/httpdata.o -MF CMakeFiles/web_server.dir/src/httpdata.o.d -o CMakeFiles/web_server.dir/src/httpdata.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/httpdata.cpp

CMakeFiles/web_server.dir/src/httpdata.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/httpdata.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/httpdata.cpp > CMakeFiles/web_server.dir/src/httpdata.i

CMakeFiles/web_server.dir/src/httpdata.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/httpdata.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/httpdata.cpp -o CMakeFiles/web_server.dir/src/httpdata.s

CMakeFiles/web_server.dir/src/server.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/server.o: ../src/server.cpp
CMakeFiles/web_server.dir/src/server.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/web_server.dir/src/server.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/server.o -MF CMakeFiles/web_server.dir/src/server.o.d -o CMakeFiles/web_server.dir/src/server.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/server.cpp

CMakeFiles/web_server.dir/src/server.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/server.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/server.cpp > CMakeFiles/web_server.dir/src/server.i

CMakeFiles/web_server.dir/src/server.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/server.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/server.cpp -o CMakeFiles/web_server.dir/src/server.s

CMakeFiles/web_server.dir/src/thread.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/thread.o: ../src/thread.cpp
CMakeFiles/web_server.dir/src/thread.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/web_server.dir/src/thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/thread.o -MF CMakeFiles/web_server.dir/src/thread.o.d -o CMakeFiles/web_server.dir/src/thread.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/thread.cpp

CMakeFiles/web_server.dir/src/thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/thread.cpp > CMakeFiles/web_server.dir/src/thread.i

CMakeFiles/web_server.dir/src/thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/thread.cpp -o CMakeFiles/web_server.dir/src/thread.s

CMakeFiles/web_server.dir/src/timer_manager.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/timer_manager.o: ../src/timer_manager.cpp
CMakeFiles/web_server.dir/src/timer_manager.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/web_server.dir/src/timer_manager.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/timer_manager.o -MF CMakeFiles/web_server.dir/src/timer_manager.o.d -o CMakeFiles/web_server.dir/src/timer_manager.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/timer_manager.cpp

CMakeFiles/web_server.dir/src/timer_manager.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/timer_manager.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/timer_manager.cpp > CMakeFiles/web_server.dir/src/timer_manager.i

CMakeFiles/web_server.dir/src/timer_manager.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/timer_manager.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/timer_manager.cpp -o CMakeFiles/web_server.dir/src/timer_manager.s

CMakeFiles/web_server.dir/src/utility.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/src/utility.o: ../src/utility.cpp
CMakeFiles/web_server.dir/src/utility.o: CMakeFiles/web_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/web_server.dir/src/utility.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/web_server.dir/src/utility.o -MF CMakeFiles/web_server.dir/src/utility.o.d -o CMakeFiles/web_server.dir/src/utility.o -c /home/ambitionyc/mything/create_my_sever/WebServer/src/utility.cpp

CMakeFiles/web_server.dir/src/utility.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/src/utility.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ambitionyc/mything/create_my_sever/WebServer/src/utility.cpp > CMakeFiles/web_server.dir/src/utility.i

CMakeFiles/web_server.dir/src/utility.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/src/utility.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ambitionyc/mything/create_my_sever/WebServer/src/utility.cpp -o CMakeFiles/web_server.dir/src/utility.s

# Object files for target web_server
web_server_OBJECTS = \
"CMakeFiles/web_server.dir/main.o" \
"CMakeFiles/web_server.dir/src/channel.o" \
"CMakeFiles/web_server.dir/src/count_down_latch.o" \
"CMakeFiles/web_server.dir/src/current_thread.o" \
"CMakeFiles/web_server.dir/src/epoll.o" \
"CMakeFiles/web_server.dir/src/eventloop.o" \
"CMakeFiles/web_server.dir/src/eventloop_thread.o" \
"CMakeFiles/web_server.dir/src/eventloop_thread_pool.o" \
"CMakeFiles/web_server.dir/src/httpdata.o" \
"CMakeFiles/web_server.dir/src/server.o" \
"CMakeFiles/web_server.dir/src/thread.o" \
"CMakeFiles/web_server.dir/src/timer_manager.o" \
"CMakeFiles/web_server.dir/src/utility.o"

# External object files for target web_server
web_server_EXTERNAL_OBJECTS =

web_server: CMakeFiles/web_server.dir/main.o
web_server: CMakeFiles/web_server.dir/src/channel.o
web_server: CMakeFiles/web_server.dir/src/count_down_latch.o
web_server: CMakeFiles/web_server.dir/src/current_thread.o
web_server: CMakeFiles/web_server.dir/src/epoll.o
web_server: CMakeFiles/web_server.dir/src/eventloop.o
web_server: CMakeFiles/web_server.dir/src/eventloop_thread.o
web_server: CMakeFiles/web_server.dir/src/eventloop_thread_pool.o
web_server: CMakeFiles/web_server.dir/src/httpdata.o
web_server: CMakeFiles/web_server.dir/src/server.o
web_server: CMakeFiles/web_server.dir/src/thread.o
web_server: CMakeFiles/web_server.dir/src/timer_manager.o
web_server: CMakeFiles/web_server.dir/src/utility.o
web_server: CMakeFiles/web_server.dir/build.make
web_server: CMakeFiles/web_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable web_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/web_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/web_server.dir/build: web_server
.PHONY : CMakeFiles/web_server.dir/build

CMakeFiles/web_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/web_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/web_server.dir/clean

CMakeFiles/web_server.dir/depend:
	cd /home/ambitionyc/mything/create_my_sever/WebServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ambitionyc/mything/create_my_sever/WebServer /home/ambitionyc/mything/create_my_sever/WebServer /home/ambitionyc/mything/create_my_sever/WebServer/build /home/ambitionyc/mything/create_my_sever/WebServer/build /home/ambitionyc/mything/create_my_sever/WebServer/build/CMakeFiles/web_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/web_server.dir/depend
