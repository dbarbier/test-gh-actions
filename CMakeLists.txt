cmake_minimum_required(VERSION 3.13)

project(main LANGUAGES CXX)

add_executable(main main.cpp f.cpp)
find_package(MPI REQUIRED)
target_link_libraries(main PRIVATE MPI::MPI_CXX)

include(CTest)
enable_testing()
add_test (
    NAME example_main
    COMMAND ${MPIEXEC_EXECUTABLE} -n 1 $<TARGET_FILE:main>
)

install(TARGETS main)
