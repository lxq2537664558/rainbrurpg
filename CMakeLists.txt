cmake_minimum_required (VERSION 2.8)
project (rainbrurpg)
message(STATUS "Configuring RainbruRPG...")

# Generate config file
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )

INCLUDE(GNUInstallDirs)
INCLUDE(FindPkgConfig)

# Enables C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Check dependencies
set(CLI_DEPS OGRE CEGUI CEGUI-OGRE) # Client-only dependencies
pkg_check_modules(CLI REQUIRED "${CLI_DEPS}")

# add the binary tree to the search path for include files
include_directories(
  ${PROJECT_BINARY_DIR}
  ${CLI_CFLAGS}
  )

FILE(GLOB logger-src "${CMAKE_SOURCE_DIR}/logger/src/*.cpp")
add_library(rainbrurpg-logger ${logger-src})

FILE(GLOB client-src "${CMAKE_SOURCE_DIR}/client/src/*.cpp")
add_executable(rainbrurpg-client ${client-src})

#add_executable(rainbrurpg client)
