cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

if (DEFINED ENV{USE_VCPKG_TOOLCHAIN} AND "$ENV{USE_VCPKG_TOOLCHAIN}" STREQUAL "1")
    set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(HelloWorld VERSION ${PROJECT_VERSION})

option(TEST_BOOST "Whether to build Boost test" ON)
option(TEST_GOOGLE "Whether to build Google test" ON)

configure_file(
	version.h.in 
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

include_directories(HelloWorld PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(lib)
add_subdirectory(src)

if(TEST_BOOST)
	add_subdirectory(tests/boost_test)
endif()

if(TEST_GOOGLE)
	add_subdirectory(tests/google_test)
endif()

#Запаковка релиза
install(TARGETS console RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(TEST_BOOST)
	enable_testing()
	add_test(boost_test_version tests/boost_test/boost_test_version)
endif()

if(TEST_GOOGLE)
	enable_testing()
	add_test(google_test_version tests/google_test/google_test_version)
endif()