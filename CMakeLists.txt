cmake_minimum_required(VERSION 3.10)
# Set the project name
project(Section_1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the compiling mode flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s")
# Include the current directory for header files
include_directories(include)
# Add the executable
add_executable(main src/main.c src/array_functions.c)
