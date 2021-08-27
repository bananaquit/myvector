cmake_minimum_required(VERSION 3.10)

# set the project name
project(MyVector VERSION 0.1)

# Configure a header file to pass the version number to the source code
configure_file(config.hpp.in config.hpp)

target_include_directories(MyVector PUBLIC "${PROJECT_BINARY_DIR}")

# add the executable
add_executable(Test test.cxx)
