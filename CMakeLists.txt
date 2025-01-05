cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
#set(CMAKE_TOOLCHAIN_FILE E:/vcpkg/scripts/buildsystems/vcpkg.cmake)

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

#if(TEST_BOOST)
#	add_subdirectory(tests/boost_test)
#endif()

#if(TEST_GOOGLE)
#	add_subdirectory(tests/google_test)
#endif()

if(TEST_BOOST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(boost_test_version tests/boost_test/boost_test_version.cpp)

    set_target_properties(boost_test_version PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(boost_test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(boost_test_version
        ${Boost_LIBRARIES}
        lib
    )
	
	target_include_directories(boost_test_version PRIVATE
		${CMAKE_SOURCE_DIR}/lib
	)
	enable_testing()
    add_test(boost_test_version boost_test_version)
endif()

if(TEST_GOOGLE)
	if(POLICY CMP0135)
	cmake_policy(SET CMP0135 NEW)
	set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
	endif()
	
	find_package(GTest CONFIG REQUIRED)
	add_executable(google_test_version tests/google_test/google_test_version.cpp)
	
	set_target_properties(google_test_version PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )
	
    target_link_libraries(google_test_version PRIVATE 
	GTest::gtest 
	GTest::gtest_main
	)
	target_link_libraries(google_test_version PUBLIC 
	lib
	)
	target_include_directories(google_test_version PRIVATE
	${CMAKE_SOURCE_DIR}/lib
	)
	enable_testing()
	add_test(google_test_version google_test_version)
endif()

#Запаковка релиза
install(TARGETS console RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)