cmake_minimum_required(VERSION 3.14)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

project(Foo
        VERSION 0.0.1
        DESCRIPTION "N"
        LANGUAGES CXX)

option (ENABLE_DOC "Generate html documentation" ON)

include(FetchContent)
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
        json
        # Upstream repository is huge https://github.com/nlohmann/json
        # This one is optimized for FetchContent
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.10.4)

FetchContent_MakeAvailable(json)

if(ENABLE_DOC)
	add_subdirectory(doc)
endif(ENABLE_DOC)
