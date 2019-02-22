cmake_minimum_required(VERSION 3.2.0)

project(Optional C CXX)

set(target_name "optional")
set(tests_name "${target_name}_unit_tests")


#################
#### Source Files

set(
    headers

    src/oauth.h
    src/account.h
    src/display.h
)

set(
    sources

    src/main.cpp
    src/oauth.cpp
    src/account.cpp
    src/display.cpp
)

set(
    tests_sources

    tests/oauth_tests.cpp
)


#######################
#### Required Libraries

find_package(Curses REQUIRED)
if (Curses_FOUND)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

find_package(Threads REQUIRED)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIR})
endif()

#find_package(Curl REQUIRED) ugh this doesn't work


######################
#### Google Test Setup
#
# Downloads GTest from Google at configure time, and builds it at
# project compile time in the build directory. 
#
# (You should really be doing out-of-source builds if you're not already.)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/tests")
include(GoogleTest)


#################
#### Build Config

set(CMAKE_CXX_STANDARD 14)

add_executable(
    ${target_name}

    ${headers}
    ${sources}
)

target_link_libraries(
    ${target_name}

    ${CMAKE_THREAD_LIBS_INIT}
    ${CURSES_LIBRARIES}
    ${BOOST_LIBRARIES}
)


#################
#### Tests Config

add_executable(
    ${tests_name}

    ${tests_sources}
)

target_link_libraries(
    ${tests_name}

    gtest_main
)

