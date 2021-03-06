cmake_minimum_required (VERSION 2.8)
project (rainbrurpg)

message(STATUS "Configuring RainbruRPG...")
# set( CMAKE_VERBOSE_MAKEFILE on ) # To debug this file

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Include git submodules
include("${PROJECT_SOURCE_DIR}/ext/librlgl/src/lib/CMakeLists.txt")

option(BUILD_LOGGER_EXAMPLES "If we build logger examples binaries" OFF)
option(BUILD_LOGREADER "If we build the Qt-based logreader" OFF)
option(BUILD_TESTS "Defines if we build unit tests" ON)

set(VERSION 0.0.5)
set(REVISION 255)

# Generate config file
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
  )

configure_file(
  "${PROJECT_SOURCE_DIR}/Doxyfile.in"
  "${PROJECT_SOURCE_DIR}/Doxyfile"
  )

INCLUDE(GNUInstallDirs)
INCLUDE(FindPkgConfig)
INCLUDE(FindGettext)
INCLUDE(FindGTest)

# Used to debug cmake variables
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

# Enables C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  # Disabling C++11 support for clang to avoid CI fails
#  if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#  else(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    message(STATUS "Disabling CXX11 support for clang.")
#  endif(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Handle gettext translations
SET(_potFile ${CMAKE_SOURCE_DIR}/po/${PROJECT_NAME}.pot)
find_program (XGETTEXT_CMD xgettext)
find_program (MSGMERGE_CMD msgmerge)
message(STATUS "Found xgettext executable at ${XGETTEXT_CMD}")
message(STATUS "Executing xgettext on ${CMAKE_SOURCE_DIR}/po/POTFILES.in")
ADD_CUSTOM_COMMAND(OUTPUT ${_potFile}
  COMMAND ${XGETTEXT_CMD} ${_xgettext_option_list} -o ${_potFile}
  --files-from=${CMAKE_SOURCE_DIR}/po/POTFILES.in
  --keyword=_
  --add-comments=TRANSLATORS
  DEPENDS ${CMAKE_SOURCE_DIR}/po/POTFILES.in
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Extract translatable messages to ${_potFile}"
)
ADD_CUSTOM_TARGET(pot_file ${_all} DEPENDS ${_potFile})

GETTEXT_CREATE_TRANSLATIONS("${CMAKE_SOURCE_DIR}/po/rainbrurpg-logger.pot" ALL
  "${CMAKE_SOURCE_DIR}/po/rainbrurpg-logger.pot")

# Check dependencies
set(CLI_DEPS OGRE CEGUI-0 CEGUI-0-OGRE OIS) # Client-only dependencies
pkg_check_modules(CLI REQUIRED ${CLI_DEPS})
set(BOOST_COMPONENTS system filesystem program_options thread graph regex)
if (BUILD_TESTS) 
  list(APPEND BOOST_COMPONENTS unit_test_framework)
endif()

find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
pkg_check_modules(GUILE REQUIRED guile-2.0)
find_package(Readline)

# Generate plugins.cfg from client's plugins.cfg.in
#  Here is call to `pkg-config --variable=plugindir OGRE` to get the plugins
#  directory variable
execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=plugindir OGRE
                        OUTPUT_VARIABLE _pkg_result
                        OUTPUT_STRIP_TRAILING_WHITESPACE)
set(OGRE_PLUGINDIR "${_pkg_result}")
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/src/client/plugins.cfg.in"
               "${CMAKE_BINARY_DIR}/plugins.cfg")

# Generate resources.cfg (actualy a simple copy without any substitution)
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/src/client/resources.cfg.in"
               "${CMAKE_BINARY_DIR}/resources.cfg")

# add the binary tree to the search path for include files
include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CLI_INCLUDE_DIRS}
  ${GUILE_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  src/logger
  src/server/lib
  ext/librlgl/src/lib
  )

# Individual libraries rules
# Defines sources (defined here because used by i18n)
set(logger-src
  src/logger/Logger.cpp
  src/logger/LoggerOutputYaml.cpp
  src/logger/LoggerOutput.cpp
  src/logger/ObjectAttribute.cpp
  src/logger/LoggerOutputFile.cpp
  src/logger/LoggerOutputTty.cpp
  src/logger/ObjectInspector.cpp)
add_library(rainbrurpg-logger SHARED ${logger-src})
target_link_libraries(rainbrurpg-logger
  ${Boost_LIBRARIES}
  )

# Serverlib library : shared by server and client
set(serverlib-src
  src/server/lib/Server.cpp
)
add_library(rainbrurpg-serverlib SHARED ${serverlib-src})
target_link_libraries(rainbrurpg-serverlib
  rainbrurpg-logger
  ${Boost_LIBRARIES}
  )

set(services-src
#  src/services/DependGraph.cpp # Just a test, contains a main() function
  src/services/main.cpp
#  src/services/depend-parser-test.cpp # another main function here
  )
add_library(rainbrurpg-services SHARED ${services-src})
target_link_libraries(rainbrurpg-services
  rainbrurpg-logger
  ${GUILE_LIBRARIES}
)

# Executables rules
set (client-src
  src/client/AnimatedImage.cpp
  src/client/CeguiDialog.cpp
  src/client/ConfirmationDialog.cpp
  src/client/Exception.cpp
  src/client/GameEngine.cpp
  src/client/GameState.cpp
  src/client/LoadingBar.cpp
  src/client/LocalTest.cpp
  src/client/MainMenu.cpp
  src/client/ModalDialog.cpp
  src/client/NyiDialog.cpp
  src/client/OgreCfgSaver.cpp
  src/client/ResolutionHandler.cpp
  src/client/StateManager.cpp
  src/client/StateSaver.cpp
  src/client/TempMessage.cpp
  src/client/WaitingCircle.cpp
  src/client/main.cpp
  )
add_executable(rainbrurpg-client ${client-src})
target_link_libraries(rainbrurpg-client
  rainbrurpg-logger
  rainbrurpg-services
  rainbrurpg-serverlib
  librlgl
  ${CLI_LIBRARIES}
  ${Boost_LIBRARIES}
  )

set (server-src
  src/server/main.cpp
  )
add_executable(rainbrurpg-server ${server-src})
target_link_libraries(rainbrurpg-server
  rainbrurpg-logger
  rainbrurpg-services
  librlgl
  ${Boost_LIBRARIES}
  )

set(server-ctl
  src/server/tools/server_ctl/CommandLine.cpp
  src/server/tools/server_ctl/main.cpp
  src/server/tools/server_ctl/ServerCommand.cpp
  )
add_executable(rainbrurpg-server-ctl ${server-ctl})
target_link_libraries(rainbrurpg-server-ctl
  rainbrurpg-logger
  rainbrurpg-services
  ${Boost_LIBRARIES} ${Readline_LIBRARY}
)

# Conditional building

## Logger examples
if(BUILD_LOGGER_EXAMPLES)
  set(logger-examples-src
    src/logger/examples/logger-test.cpp
    src/logger/examples/Point.cpp
    )
  add_executable(rainbrurpg-logger-example ${logger-examples-src})
  target_link_libraries(rainbrurpg-logger-example
    rainbrurpg-logger
    ${Boost_LIBRARIES}
    )
  target_link_libraries(rainbrurpg-logger-example rainbrurpg-logger)
endif(BUILD_LOGGER_EXAMPLES)

if(BUILD_LOGREADER)
  find_program (UIC NAMES rbuic4)
  message(STATUS "Found rbuic4 executable (${UIC})")
  if (UIC)
    add_custom_command(OUTPUT MainWindow_ui.rb
      COMMAND ${UIC} MainWindow.ui -o MainWindow_ui.rb
      DEPENDS ${CMAKE_SOURCE_DIR}/src/logger/tools/logreader/MainWindow.ui
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/logger/tools/logreader/
      COMMENT "Generating ruby sources from .ui file"
      )
    add_custom_target(logreader ALL DEPENDS MainWindow_ui.rb)
  else(UIC)
    message(FATAL_ERROR "The rbuic4 executable was not found, "
      "please verify your ruby-qt4 installation or disable "
      "BUILD_LOGREADER building.")
  endif(UIC)
endif(BUILD_LOGREADER)

if (BUILD_TESTS)
  # All files with the given pattern will be use as unit tests.
  # No main function/file needed.
  file(GLOB unittests-src src/*/*_Test.cpp)
  list(APPEND unittests-src src/tests.cpp)

  # Append some sources to fix undefined references but we need to remove
  # some main() to avoid multiple definitions
  list(REMOVE_ITEM client-src src/client/main.cpp)
  list(APPEND unittests-src ${client-src})
  list(APPEND unittests-src ${logger-src})
  
  add_executable(rainbrurpg-tests ${unittests-src})
  target_link_libraries(rainbrurpg-tests
    rainbrurpg-logger
    rainbrurpg-services
    rainbrurpg-serverlib
    librlgl
    ${CLI_LIBRARIES}
    ${GTEST_LIBRARIES}
    )
  IF(UNIX)
    ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) # Make Boost.Test generate a main()
  ENDIF(UNIX)
  add_custom_target(check COMMAND rainbrurpg-tests) # Add the `make check` cmd
endif()

# This is a fix for the GNU C __FILE__ thing :
#  __FILE__ shows the full path of the file, so the logger text output
#  is weird.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/src/,,$(abspath $<))\"'")

# Define a librlgl-related macro
# Should be ~/programmation/github.com/rainbrurpg/ext/librlgl/
set(RLGLDIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/librlgl)
add_definitions(-DROOTDIR="${RLGLDIR}")
