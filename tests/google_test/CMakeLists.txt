cmake_minimum_required(VERSION 3.12)

project(google_test)

if(POLICY CMP0135)
cmake_policy(SET CMP0135 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()
	
find_package(GTest CONFIG REQUIRED)
add_executable(google_test_version google_test_version.cpp)
	
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