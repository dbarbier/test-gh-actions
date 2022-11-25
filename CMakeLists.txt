cmake_minimum_required(VERSION 3.13)

project(main LANGUAGES CXX)

add_executable(main main.cpp f.cpp)
try_compile(SIZE_T_UNALIASED ${CMAKE_CURRENT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/unaliased_size_t.cxx OUTPUT_VARIABLE out)
message(STATUS "SIZE_T_UNALIASED = ${SIZE_T_UNALIASED}")
message(STATUS "${out}")
if (SIZE_T_UNALIASED)
        target_compile_definitions(main PRIVATE SIZE_T_UNALIASED)
endif (SIZE_T_UNALIASED)

find_package(MPI REQUIRED)
target_link_libraries(main PRIVATE MPI::MPI_CXX)

include(CTest)
enable_testing()
add_test (
    NAME example_main
    COMMAND ${MPIEXEC_EXECUTABLE} -n 1 $<TARGET_FILE:main>
)

message(STATUS "CMAKE_SIZEOF_VOID_P = ${CMAKE_SIZEOF_VOID_P}")

install(TARGETS main)
