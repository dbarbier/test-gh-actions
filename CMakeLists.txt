cmake_minimum_required(VERSION 3.14)

project(test NONE)

include(UseLATEX.cmake)

file(GLOB_RECURSE latex_files
     RELATIVE ${PROJECT_SOURCE_DIR}
     *.tex)

add_latex_document(main.tex
	INPUTS ${latex_files}
	FORCE_PDF
	USE_NOMENCL
)
