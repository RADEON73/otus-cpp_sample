cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(LIBRARY_VERSION 0.0.${PATCH_VERSION})

project(Library VERSION ${LIBRARY_VERSION})

configure_file(
	version.h.in 
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

add_library(lib lib.cpp lib.h)

set_target_properties(lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(lib PRIVATE
        /W4
    )
else ()
    target_compile_options(lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_include_directories(lib PRIVATE 
	${CMAKE_CURRENT_BINARY_DIR}
)