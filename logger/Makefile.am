SUBDIRS= po src

ACLOCAL_AMFLAGS = -I m4

#  install the man pages
man_MANS = logger.1
EXTRA_DIST = config.rpath m4/ChangeLog logger.lsm.in system.h aclocal.m4 \
	gettext.h logger.1

#  uncomment the following if logger requires the math library
#logger_LDADD=-lm

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = logger.texinfo
logger_TEXINFOS = gpl.texinfo

# pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = rainbrurpg-logger.pc
