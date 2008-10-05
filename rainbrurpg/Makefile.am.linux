# To make the HTML version of the texinfo help
# You need the texinfo package

# The sources
SUBDIRS = common maincore ogreGui client

# The data files
SUBDIRS+= config data media mapdata

# Bug ?
# RainbruRPG.html

if BUILD_LIB_DESIGN
  SUBDIRS+=design
endif

if RB_OPTION_EDITOR_FLAGS
  SUBDIRS+=editor
endif

if RB_OPTION_SERVER_FLAGS
  SUBDIRS+=server
endif

if RB_OPTION_TOOLS_FLAGS
  SUBDIRS+=tools
endif

if RB_OPTION_TESTS_FLAGS
  SUBDIRS+=tests
endif

if RB_OPTION_EXAMPLES_FLAGS
  SUBDIRS+=examples
endif

if RB_OPTION_TAPI_FLAGS
  SUBDIRS+=terminalapi
endif

if RB_OPTION_ALL_FLAGS
  SUBDIRS+=terminalapi editor server tools tests examples
endif 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = terminalapi-1.0.pc

EXTRA_DIST=RainbruRPG.lsm.in  \
	   RainbruRPG.texinfo \
	   RainbruRPG.spec.in \
	   Doxyfile

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = RainbruRPG.texinfo
RainbruRPG_TEXINFOS = gpl.texinfo

#  install the man pages
man_MANS=RainbruRPG.6        \
	 RainbruRPG-server.6 \
	 RainbruRPG-editor.6
