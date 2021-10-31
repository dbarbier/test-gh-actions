cmake_minimum_required(VERSION 3.13)

project(main LANGUAGES CXX)

add_executable(main main.cpp f.cpp)

install(TARGETS main)
