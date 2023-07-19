cmake_minimum_required (VERSION 3.13)
project (trace LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options (
	-Wall
	)

add_link_options (
	#
	)

include_directories	(
	${PROJECT_SOURCE_DIR}
	)

add_library ( trace SHARED
	trace.c
	)

add_library ( trace_helper SHARED
	trace_helper.cpp
	)

add_executable ( main
	main.c
	)
target_link_libraries( main
	trace
	pthread
	)

add_executable ( main_cpp
	main.cpp
	)
target_link_libraries( main_cpp
	trace_helper
	trace
	pthread
	)

