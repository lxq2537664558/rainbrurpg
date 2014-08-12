#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_PREREQ([2.67])

AC_INIT([rainbrurpg-server], [0.0.0-0], [rainbru@users.sourceforge.net])
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER(config.h)
#AC_INIT(src/main.cpp)
#AM_INIT_AUTOMAKE(rainbrurpg-server,0.0.0-0,[rainbru@users.sourceforge.net])
#AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
PKG_CHECK_MODULES([LOG], [rainbrurpg-logger > 0])

AC_CHECK_LIB(readline, main, [], [
  echo "Error! You need to have libreadline installed."
  exit -1
])
AC_CHECK_LIB(history, main, [], [
  echo "Error! You need to have libreadline installed."
  exit -1
])

AC_CHECK_HEADER([readline/readline.h], [], [
  echo "Error! Cannot find the libreadline headers."
  exit -1
])

AC_LANG_CPLUSPLUS
AC_DEFINE([HAVE_ASIO], [], [Was Asio library found])
AC_CHECK_HEADER(asio.hpp, AC_DEFINE(HAVE_ASIO), 
   AC_MSG_ERROR([Can't find Asio library]))
    AC_CHECK_LIB(boost_filesystem, main, [], [
      echo "Error! You need to have Boost-filesystem installed."
      exit -1
    ])
    AC_CHECK_HEADER([boost/filesystem/path.hpp], [], [
      echo "Error! Cannot find the Boost-filesystem headers."
      exit -1
    ])
# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT([
  Makefile			\
  src/Makefile			\
  src/tools/Makefile		\
  src/tools/server_ctl/Makefile
])
