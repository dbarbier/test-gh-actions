cmake_minimum_required(VERSION 3.14)


if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

project(Foo
        VERSION 0.0.1
        DESCRIPTION "N"
        LANGUAGES CXX)

option (ENABLE_DOC "Generate html documentation" ON)

if(ENABLE_DOC)
	add_subdirectory(doc)
endif(ENABLE_DOC)
