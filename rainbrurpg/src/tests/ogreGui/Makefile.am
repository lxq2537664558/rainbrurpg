# The final program is called "ogregui2-tests"
bin_PROGRAMS = ogregui2-tests

ogregui2_tests_LDADD = -L$(top_srcdir)/src/common/.libs			\
			 -lrainbrurpg-common 				\
			-L$(top_srcdir)/src/ogreGui/.libs		\
			 -lrainbrurpg-ogregui				\
			 $(GNET_LIBS)					\
			 $(RPG_LIB_ADD)					\
			 $(CPPUNIT_LIBS)				\
			 $(SIGC_LIBS)					\
	   		-lcppunit


INCLUDES = -I$(top_srcdir)/src/common/ 			\
	   -I$(top_srcdir)/src/ogreGui/			\
	   $(GNET_CFLAGS) 				\
	   $(OGRE_CFLAGS) 				\
	   $(CPPUNIT_CFLAGS)

ogregui2_tests_SOURCES = main.cpp			\
			 \
			 DrawableTest.cpp		\
			 SerializableTest.cpp		\
			 WidgetListTest.cpp
