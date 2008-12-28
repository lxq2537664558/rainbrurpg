# The design lib is shared by editor and server
# it is linked with Qt and libmagic
#
# This library is built only if Editor or Server are built
#
lib_LTLIBRARIES = librainbrurpg-design.la

librainbrurpg_design.adir=.

h_sources =filetypeguesser.h		\
	   helpviewer.h			\
	   filepreview.h

cc_sources=filetypeguesser.cpp		\
	   helpviewer.cpp		\
	   filepreview.cpp		\
	   \
	   moc_helpviewer.cpp		\
	   moc_filepreview.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_DESIGN_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)/common 		\
	   -I/usr/include/qt4/QtGui 		\
	   -I/usr/include/qt4 			\
	   -I/usr/include/qt4/QtCore 		\
	   -I/usr/include/qt4/Qt3Support	\
	   -DQT_QT3SUPPORT_LIB -DQT3_SUPPORT	\
	   $(OGRE_CFLAGS)

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc-qt4 $< -o $@

librainbrurpg_design_la_SOURCES= $(h_sources) $(cc_sources)
librainbrurpg_design_la_LIBADD= -lrainbrurpg-common		\
				-lQtCore 			\
				-lQtGui 			\
				-lQt3Support

librainbrurpg_design_la_LDFLAGS= \
  $(SHARED_FLAG) 		 		\
  -version-info $(DESIGN_LIBRARY_VERSION) 	\
  -L$(top_srcdir)/common/.libs 			\
  -Wl,--rpath -Wl,$(top_srcdir)/common/.libs 	\
  $(OGRE_LIBS)

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(filter moc_%.cpp,$(librainbrurpg_design_la_SOURCES=)) resources.cpp
