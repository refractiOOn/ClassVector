# CMakeList.txt : CMake project for ClassVector, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)

set (CMAKE_CXX_STANDARD 20)

project ("ClassVector")

# Add source to this project's executable.
add_executable (ClassVector "main.cpp" "Vector.hpp" "Vector.ipp")

# TODO: Add tests and install targets if needed.
