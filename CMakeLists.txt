cmake_minimum_required(VERSION 3.2.0)

project(Optional C CXX)

set(target_name "optional")

# Target Names
set(backend "${target_name}")
set(app "${target_name}_app")
set(tests "${target_name}_unit_tests")


#################
#### Source Files

set(
    backend_sources

    # Headers
    src/backend/account.h
    src/backend/oauth.h
    src/backend/rest.h
    src/backend/symbol.h

    # Source
    src/backend/account.cpp
    src/backend/oauth.cpp
    src/backend/rest.cpp
    src/backend/symbol.cpp
)

set(
    app_sources

    # Headers
    src/app/display.h

    # Sources
    src/app/display.cpp
    src/app/main.cpp
)

set(
    tests_sources

    tests/account_tests.cpp
    tests/oauth_tests.cpp
    tests/rest_tests.cpp
)


#######################
#### Required Libraries

# rapidjson located locally.
include_directories("${CMAKE_SOURCE_DIR}/external_libraries")

find_package(Curses REQUIRED)
if (Curses_FOUND)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

find_package(CURL REQUIRED)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
endif()

set(
    common_libs

    ${CMAKE_THREAD_LIBS_INIT}
    ${CURSES_LIBRARIES}
    ${CURL_LIBRARIES}
)


######################
#### Google Test Setup
#
# Downloads GTest from Google at configure time, and builds it at
# project compile time in the build directory. 

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/tests")
include(GoogleTest)


#################
#### Build Config

set(CMAKE_CXX_STANDARD 17)

add_library(
    ${backend}
    STATIC

    ${backend_sources}
)

add_executable(
    ${app}

    ${app_sources}
)

target_include_directories(
	${app} PUBLIC

	${CMAKE_SOURCE_DIR}/src/backend
)

target_link_libraries(
    ${app}

    ${common_libs}
    ${backend}
    ${ui}
)


#################
#### Tests Config

add_executable(
    ${tests}

    ${tests_sources}
)

target_include_directories(
	${tests} PUBLIC

	${CMAKE_SOURCE_DIR}/src/backend
)

target_link_libraries(
    ${tests}

    gtest_main
    ${common_libs}
    ${backend}
)

