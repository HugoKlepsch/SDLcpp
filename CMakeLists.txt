cmake_minimum_required(VERSION 3.7)
project(SDLcpp)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDLcpp_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${SDLcpp_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    message("found sdl2")
endif (SDL2_FOUND)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDLcpp main.cpp sdlWrapper.cpp)
message("SDL library: " ${SDL2_LIBRARIES})
message("SDL include path: " ${SDL2_INCLUDE_DIRS})
target_link_libraries(SDLcpp SDL2)

install(TARGETS SDLcpp RUNTIME DESTINATION ${BIN_DIR})
