cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
#set(CMAKE_TOOLCHAIN_FILE E:/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(helloworld VERSION ${PROJECT_VESRION})

option(TEST_BOOST "Whether to build Boost test" ON)
option(TEST_GOOGLE "Whether to build Google test" ON)

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

set_target_properties(helloworld_cli helloworld PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

if(TEST_BOOST)
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
        helloworld
    )
endif()

if(TEST_GOOGLE)
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
	GTest::gmock 
	GTest::gmock_main
	)
	target_link_libraries(google_test_version PUBLIC 
	helloworld
	)
endif()

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    if(TEST_BOOST)
        target_compile_options(boost_test_version PRIVATE
            /W4
        )
    endif()
	if(TEST_GOOGLE)
        target_compile_options(google_test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(TEST_BOOST)
        target_compile_options(boost_test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
	if(TEST_GOOGLE)
        target_compile_options(google_test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(TEST_BOOST)
    enable_testing()
    add_test(boost_test_version boost_test_version)
endif()

if(TEST_GOOGLE)
    enable_testing()
	add_test(google_test_version google_test_version)
endif()