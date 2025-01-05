cmake_minimum_required(VERSION 3.12)

project(boost_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(boost_test_version boost_test_version.cpp)

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