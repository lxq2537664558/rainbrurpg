# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-editor

rainbrurpg_editor_LDADD=-lQtCore -lQtGui 		\
			-lrainbrurpg-common 		\
			-lrainbrurpg-core		\
			-lrainbrurpg-ogregui		\
			-lrainbrurpg-design 		\
			-L$(top_srcdir)/common/.libs 	\
			-L$(top_srcdir)/design/.libs 	\
			-L$(top_srcdir)/maincore/.libs

OGRE_CFLAGS= -I/usr/local/include/OGRE

INCLUDES = -I$(top_srcdir)/common/ -I$(top_srcdir)/maincore/ \
	   -I$(top_srcdir)/design/ \
           -I/usr/include/qt4/QtGui -I/usr/include/qt4 \
           -I/usr/include/qt4/QtCore \
	    $(OGRE_CFLAGS)

# You have two .cpp files you wrote, myapp.cpp and another.cpp
# Remember to include the name of the resource file with the .cpp extension.
rainbrurpg_editor_SOURCES = resources.cpp        \
			    \
			    main.cpp             \
		            mainwindow.cpp       \
		            ogreview.cpp         \
		            loglistener.cpp      \
		            tabenvironment.cpp   \
		            objectstab.cpp       \
		            staticmeshdialog.cpp \
		            meshviewer.cpp       \
		            meshviewerstats.cpp  \
		            selectioncycle.cpp   \
		            selectionmanager.cpp \
		            posordialog.cpp	\
			    highlighter.cpp      \
			    luahighlighter.cpp   \
			    scripteditor.cpp

# You have one .h file, it's called myapp.h. Therefore, here I list
# its mocced name, moc_myapp.cpp.
nodist_rainbrurpg_editor_SOURCES = moc_mainwindow.cpp       \
		           moc_ogreview.cpp         \
		           moc_loglistener.cpp      \
		           moc_tabenvironment.cpp   \
		           moc_objectstab.cpp       \
		           moc_staticmeshdialog.cpp \
		           moc_meshviewer.cpp       \
		           moc_meshviewerstats.cpp  \
		           moc_selectioncycle.cpp   \
		           moc_selectionmanager.cpp \
		           moc_posordialog.cpp	    \
			   moc_highlighter.cpp      \
			   moc_luahighlighter.cpp   \
			   moc_scripteditor.cpp

# This is to ensure the myapp.h file is distributed in your myapp-0.1.tar.gz
# I also have a resources.qrc I need to include. The png is used in myapp.
#EXTRA_DIST = \
#	$(nodist_myapp_SOURCES:moc_%.cpp=%.h) \
#	resources.qrc myapp.png

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc $< -o $@

# Adjust this line according to your resources.qrc
resources.cpp : resources.qrc #octave-gui.png
	rcc resources.qrc -o resources.cpp

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(filter moc_%.cpp,$(rainbrurpg_editor_SOURCES)) resources.cpp




