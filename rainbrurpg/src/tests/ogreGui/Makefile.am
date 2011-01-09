# The final program is called "ogregui2-tests"
bin_PROGRAMS = ogregui2-tests individual-fontmanager

ogregui2_tests_LDADD = -L$(top_srcdir)/src/common/.libs			\
			 -lrainbrurpg-common 				\
			-L$(top_srcdir)/src/ogreGui/.libs		\
			 -lrainbrurpg-ogregui				\
			-L$(top_srcdir)/src/maincore/.libs		\
			 -lrainbrurpg-core				\
			 $(GNET_LIBS)					\
			 $(RPG_LIB_ADD)					\
			 $(CPPUNIT_LIBS)				\
			 $(SIGC_LIBS)					\
	   		-lcppunit					\
			$(top_srcdir)/src/testHelpers/libtesthelpers.la

INCLUDES = -I$(top_srcdir)/src/common/ 			\
	   -I$(top_srcdir)/src/ogreGui/			\
	   -I$(top_srcdir)/src/maincore/		\
	   -I$(top_srcdir)/src/testHelpers/		\
	   $(FREETYPE_CFLAGS)				\
	   $(GNET_CFLAGS) 				\
	   $(OGRE_CFLAGS) 				\
	   $(OIS_CFLAGS)				\
	   $(CPPUNIT_CFLAGS)

ogregui2_tests_SOURCES = main.cpp			\
			 \
			 BrushTest.cpp			\
			 FocusableTest.cpp		\
			 FontManagerTest.cpp		\
			 DrawableTest.cpp		\
			 DrawableTestWithOgre.cpp	\
			 SerializableTest.cpp		\
			 WidgetListTest.cpp

individual_fontmanager_SOURCES = main-fontmanager.cpp		\
	                         FontManagerTest.cpp

individual_fontmanager_LDADD = $(RPG_LIB_ADD)				\
			       -L$(top_srcdir)/src/common/.libs		\
			       -lrainbrurpg-common 			\
			       -L$(top_srcdir)/src/ogreGui/.libs	\
			       -lrainbrurpg-ogregui			\
			       -L$(top_srcdir)/src/maincore/.libs	\
			       -lrainbrurpg-core			\
			       $(CPPUNIT_LIBS)				\
			       $(top_srcdir)/src/testHelpers/libtesthelpers.la


