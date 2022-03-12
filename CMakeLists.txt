cmake_minimum_required(VERSION 3.13)

project(main LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake")

set(FETCHCONTENT_QUIET FALSE CACHE BOOL "")

find_package(MPI MODULE COMPONENTS CXX)

# Eigen < 3.4.0 had some trouble with sparse matrices in row-major layout
# https://gitlab.com/libeigen/eigen/-/issues/1910
find_package(Eigen3 3.4.0 CONFIG)
if(NOT Eigen3_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		Eigen3
		GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git/
		GIT_TAG 3.4.0
	)

	FetchContent_MakeAvailable(Eigen3)
	if(NOT TARGET Eigen3::Eigen)
		add_library(Eigen3::Eigen ALIAS eigen)
	endif(NOT TARGET Eigen3::eigen)
endif(NOT Eigen3_FOUND)

# First look for HYPREConfig
unset(hypre_is_bigint)
find_package(HYPRE CONFIG)
if (NOT HYPRE_FOUND)
	# If not found, use cmake/FindHYPRE.cmake
	find_package(HYPRE)
	if(HYPRE_FOUND)
		message(STATUS "HYPRE found by cmake/FindHYPRE.cmake")
	else(HYPRE_FOUND)
		include(FetchContent)
		if (CMAKE_VERSION VERSION_GREATER 3.18)
			FetchContent_Declare(
				hyprepackage
				GIT_REPOSITORY https://github.com/hypre-space/hypre
				GIT_TAG v2.23.0
				SOURCE_SUBDIR src)
		else (CMAKE_VERSION VERSION_GREATER 3.18)
			file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/FakeCMakeLists.txt "add_subdirectory(src)")
			FetchContent_Declare(
				hyprepackage
				GIT_REPOSITORY https://github.com/hypre-space/hypre
				GIT_TAG v2.23.0
				PATCH_COMMAND COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/FakeCMakeLists.txt CMakeLists.txt)
		endif (CMAKE_VERSION VERSION_GREATER 3.18)

		set(HYPRE_ENABLE_BIGINT ON CACHE BOOL "" FORCE)
		set(hypre_is_bigint TRUE)

		FetchContent_MakeAvailable(hyprepackage)

		# https://github.com/hypre-space/hypre/issues/513
		file(REMOVE ${FETCHCONTENT_BASE_DIR}/hyprepackage-src/src/utilities/version)

		# https://github.com/hypre-space/hypre/pull/563
		if(NOT TARGET HYPRE::HYPRE)
			add_library(HYPRE::HYPRE ALIAS HYPRE)
		endif(NOT TARGET HYPRE::HYPRE)

	endif(HYPRE_FOUND)
endif(NOT HYPRE_FOUND)
if(NOT hypre_is_bigint)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/hypre_bigint.cxx "#include <HYPRE_config.h>\n#ifndef HYPRE_BIGINT\n#error HYPRE_BIGINT not defined\n#endif\nint main(int, char*[]) {return 0;}")
	try_compile(HYPRE_IS_BIGINT ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/hypre_bigint.cxx LINK_LIBRARIES HYPRE::HYPRE)
	if(NOT HYPRE_IS_BIGINT)
		message(FATAL_ERROR "HYPRE must be compiled with 64bit integers (BIGINT)")
	endif(NOT HYPRE_IS_BIGINT)
endif(NOT hypre_is_bigint)

add_executable(main main.cpp f.cpp)
find_package(MPI REQUIRED)
target_link_libraries(main PRIVATE MPI::MPI_CXX HYPRE::HYPRE Eigen3::Eigen)


include(CTest)
enable_testing()
add_test (
    NAME example_main
    COMMAND ${MPIEXEC_EXECUTABLE} -n 1 $<TARGET_FILE:main>
)

install(TARGETS main)
