dnl Process this file with autoconf to produce a configure script.

AC_INIT(src/Logger.cpp)
dnl Every other copy of the package version number gets its value from here
AM_INIT_AUTOMAKE(logger, 0.0.0-9)
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.18) 

dnl create a config.h file (Automake will add -DHAVE_CONFIG_H)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST(VERSION)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

AC_CANONICAL_HOST

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL

dnl Check for external tools
RB_CHECK_RBUIC

dnl Checks for libraries.
RB_CHECK_BOOST_PROGRAM_OPTIONS
RB_CHECK_BOOST_FORMAT

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(unistd.h sys/param.h sys/time.h time.h sys/mkdev.h sys/sysmacros.h string.h memory.h fcntl.h dirent.h sys/ndir.h ndir.h alloca.h locale.h )

jm_CHECK_TYPE_STRUCT_UTIMBUF
AC_HEADER_MAJOR
AC_FUNC_ALLOCA
AC_STRUCT_TM
AC_STRUCT_ST_BLOCKS
AC_FUNC_CLOSEDIR_VOID
AC_CHECK_FUNCS(mkfifo)
AC_CHECK_FUNC(mknod)

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.

AC_OUTPUT([			\
  po/Makefile.in		\
  Makefile	       		\
  src/Makefile 	       		\
  src/tools/Makefile   		\
  src/examples/Makefile		\
  rainbrurpg-logger.lsm 	\
  rainbrurpg-logger.spec 	\
  rainbrurpg-logger.pc
])

echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE v$VERSION configuration summary"
echo "------------------------------------------------------------------------"
echo
echo "Tools:"
echo "  rbuic..........................${TOOL_RBUIC}"
