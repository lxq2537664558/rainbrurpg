SUBDIRS=src

man_MANS = logger.1
EXTRA_DIST = system.h aclocal.m4

#  uncomment the following if logger requires the math library
#logger_LDADD=-lm

EXTRA_DIST=logger.lsm.in #NAME.texinfo logger.spec.in

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = logger.texinfo
logger_TEXINFOS = gpl.texinfo

#  install the man pages
man_MANS=logger.1

# pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = rainbrurpg-logger.pc
