cmake_minimum_required(VERSION 3.14)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

project(Foo
        VERSION 0.0.1
        DESCRIPTION "N"
        LANGUAGES CXX)

option (ENABLE_DOC "Generate html documentation" ON)

enable_testing()

include(FetchContent)
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
        json
        # Upstream repository is huge https://github.com/nlohmann/json
        # This one is optimized for FetchContent
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG b48095ee99aff048dc4760dd644b848bc1e6f0c3) # commit for v3.10.4

message(STATUS "before FetchContent_MakeAvailable")
FetchContent_MakeAvailable(json)
message(STATUS "after FetchContent_MakeAvailable")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929) # commit for release-1.11.0

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
#  GTest may need pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE unittest_files ${CMAKE_CURRENT_SOURCE_DIR}/tests/*_test.cpp)
add_executable(unittests tests/maintest.cpp ${unittest_files})
target_compile_features(unittests PRIVATE cxx_std_11)
target_link_libraries(unittests GTest::gtest GTest::gtest_main Threads::Threads)

add_test(NAME unittests COMMAND unittests)


if(ENABLE_DOC)
	add_subdirectory(doc)
endif(ENABLE_DOC)
