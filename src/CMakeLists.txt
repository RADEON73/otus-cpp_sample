cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(EXE_VERSION 0.0.${PATCH_VERSION})

project(ConsoleWindow VERSION ${EXE_VESRION})

#option(TEST_BOOST "Whether to build Boost test" ON)
#option(TEST_GOOGLE "Whether to build Google test" ON)

configure_file(
	version.h.in 
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

add_executable(console main.cpp)

set_target_properties(console PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(console PRIVATE
    lib
)
target_include_directories(console PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/lib
)

if (MSVC)
    target_compile_options(console PRIVATE
        /W4
    )
else ()
    target_compile_options(console PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()