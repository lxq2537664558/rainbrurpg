cmake_minimum_required (VERSION 2.8)
project (rainbrurpg)

message(STATUS "Configuring RainbruRPG...")
# set( CMAKE_VERBOSE_MAKEFILE on ) # To debug this file

option(BUILD_LOGGER_EXAMPLES "If we build logger examples binaries" OFF)
option(BUILD_LOGREADER "If we build the Qt-based logreader" OFF)

set(VERSION 0.0.5)
set(REVISION 248)

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
set(CLI_DEPS OGRE CEGUI CEGUI-OGRE OIS) # Client-only dependencies
pkg_check_modules(CLI REQUIRED ${CLI_DEPS})
set(BOOST_COMPONENTS system filesystem program_options thread graph
  unit_test_framework)
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
pkg_check_modules(GUILE REQUIRED guile-2.0)


# add the binary tree to the search path for include files
include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CLI_INCLUDE_DIRS}
  ${GUILE_INCLUDE_DIRS}
  src/logger
  src/logger/examples
  )

FILE(GLOB logger-src "${CMAKE_SOURCE_DIR}/src/logger/*.cpp")
add_library(rainbrurpg-logger ${logger-src})

FILE(GLOB services-src "${CMAKE_SOURCE_DIR}/services/src/*.cpp")
add_library(rainbrurpg-services ${services-src})
target_link_libraries(rainbrurpg-services
  rainbrurpg-logger
  ${GUILE_LIBRARIES}
)

FILE(GLOB client-src "${CMAKE_SOURCE_DIR}/client/src/*.cpp")
add_executable(rainbrurpg-client ${client-src})
target_link_libraries(rainbrurpg-client
  rainbrurpg-logger
  rainbrurpg-services
  ${CLI_LIBRARIES}
  ${Boost_LIBRARIES}
)

FILE(GLOB server-src "${CMAKE_SOURCE_DIR}/server/src/*.cpp")
add_executable(rainbrurpg-server ${server-src})
target_link_libraries(rainbrurpg-server
  rainbrurpg-logger
  rainbrurpg-services
  ${Boost_LIBRARIES}
)

# Conditional building

## Loger examples
if(BUILD_LOGGER_EXAMPLES)
  FILE(GLOB logger-examples-src "${CMAKE_SOURCE_DIR}/src/logger/examples/*.cpp")
  add_executable(rainbrurpg-logger-example ${logger-examples-src})
  target_link_libraries(rainbrurpg-logger-example
    rainbrurpg-logger
    ${Boost_LIBRARIES}
    )
  target_link_libraries(rainbrurpg-logger-example rainbrurpg-logger)
endif(BUILD_LOGGER_EXAMPLES)

if(BUILD_LOGREADER)
  find_program (UIC NAMES rbuic4)
  add_custom_command(OUTPUT MainWindow_ui.rb
    COMMAND ${UIC} MainWindow.ui -o MainWindow_ui.rb
    DEPENDS ${CMAKE_SOURCE_DIR}/src/logger/tools/logreader/MainWindow.ui
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/logger/tools/logreader/
    COMMENT "Generating ruby sources from .ui file"
    )
  add_custom_target(logreader ALL DEPENDS MainWindow_ui.rb)
endif(BUILD_LOGREADER)