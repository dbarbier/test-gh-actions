cmake_minimum_required(VERSION 3.14)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

project(foo_doc NONE)

include(UseLATEX.cmake)

find_package(Doxygen)

file(GLOB_RECURSE tex_files
     RELATIVE ${PROJECT_SOURCE_DIR}
     *.tex)

file(GLOB_RECURSE image_dirs
     LIST_DIRECTORIES true
     RELATIVE ${PROJECT_SOURCE_DIR}
     img)

add_latex_document(foo.tex
     INPUTS ${num_schemes_files}
     FORCE_PDF
     USE_NOMENCL
     EXCLUDE_FROM_ALL
)

add_custom_target(tech-doc ALL DEPENDS foo_pdf)
