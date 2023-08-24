cmake_minimum_required(VERSION 3.0)
project(pybind)
add_subdirectory(pybind11) #adding the directory
pybind11_add_module(tester tester.cpp) #cmake function loaded from the directory