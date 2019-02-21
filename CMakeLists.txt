cmake_minimum_required(VERSION 3.9.0)

project(Optional)
set(target_name "optional")

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
IF (Curses_FOUND)
include_directories(${CURSES_INCLUDE_DIR})
endif()

# enable when start using boost
#find_package(Boost REQUIRED)
#IF (Boost_FOUND)
#include_directories(${BOOST_INCLUDE_DIR})
#endif()

set(sources

	src/main.cpp
	src/oauth.cpp
	src/account.cpp
	src/display.cpp
)

add_executable (${target_name} ${sources})
target_link_libraries(${target_name} ${CURSES_LIBRARIES} ${BOOST_LIBRARIES}) 

