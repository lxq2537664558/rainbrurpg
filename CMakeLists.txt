cmake_minimum_required (VERSION 2.6)
project (rainbrurpg)
message(STATUS "Configuring RainbruRPG...")

# Generate config file
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )

include(GNUInstallDirs)

# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

FILE(GLOB logger-src "${CMAKE_SOURCE_DIR}/logger/src/*.cpp")
add_library(MathFunctions ${logger-src})

FILE(GLOB client-src "${CMAKE_SOURCE_DIR}/client/src/*.cpp")
add_executable(rainbrurpg-client ${client-src})

#add_executable(rainbrurpg client)
