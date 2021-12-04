cmake_minimum_required(VERSION 3.13)

project(main LANGUAGES CXX)

find_package(HYPRE CONFIG)
if(NOT HYPRE_FOUND)
        include(FetchContent)
        if (CMAKE_VERSION VERSION_GREATER 3.18)
                FetchContent_Declare(
                        hyprepackage
                        GIT_REPOSITORY https://github.com/hypre-space/hypre
                        GIT_TAG v2.23.0
                        GIT_SHALLOW TRUE
                        SOURCE_SUBDIR src)
                FetchContent_MakeAvailable(hyprepackage)
        else(CMAKE_VERSION VERSION_GREATER 3.18)
                file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/FakeCMakeLists.txt "add_subdirectory(src)")
                FetchContent_Declare(
                        hyprepackage
                        GIT_REPOSITORY https://github.com/hypre-space/hypre
                        GIT_TAG v2.23.0
                        GIT_SHALLOW TRUE
                        PATCH_COMMAND COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/FakeCMakeLists.txt CMakeLists.txt
                )
                FetchContent_MakeAvailable(hyprepackage)
        endif(CMAKE_VERSION VERSION_GREATER 3.18)
        # HYPRE defines this target only when IMPORTED from a CONFIG file
        if(NOT TARGET HYPRE::HYPRE)
                add_library(HYPRE::HYPRE ALIAS HYPRE)
        endif(NOT TARGET HYPRE::HYPRE)
endif(NOT HYPRE_FOUND)

add_executable(main main.cpp f.cpp)
find_package(MPI REQUIRED)
target_link_libraries(main PRIVATE HYPRE::HYPRE MPI::MPI_CXX)

include(CTest)
enable_testing()
add_test (
    NAME example_main
    COMMAND ${MPIEXEC_EXECUTABLE} -n 1 $<TARGET_FILE:main>
)

install(TARGETS main)
