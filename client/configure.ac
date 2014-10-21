dnl Process this file with autoconf to produce a configure script.

AC_INIT([rainbrurpg-client], [0.0.0-2], [rainbru@users.sourceforge.net])
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE


dnl create a config.h file (Automake will add -DHAVE_CONFIG_H)
AM_CONFIG_HEADER(config.h)

AC_SUBST(VERSION)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

AC_CANONICAL_HOST

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_CXX

dnl Checks for libraries.
PKG_CHECK_MODULES([DEPS], 
  [OGRE >= 1.6 OIS >= 1.3 CEGUI-0 CEGUI-0-OGRE rainbrurpg-logger])

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

AC_OUTPUT(Makefile		\
  src/Makefile			\
  media/Makefile		\
  media/cegui-orig/Makefile	\
  media/layouts/Makefile	\
  \
  client.lsm client.spec)
