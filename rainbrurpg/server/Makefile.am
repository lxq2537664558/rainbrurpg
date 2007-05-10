# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-server

rainbrurpg_server_LDADD=-lQtCore -lQtGui -lrainbrurpg-common \
			-L$(top_srcdir)/common/.libs -lglib-2.0 -lQtSql \
			-lQt3Support

glib_cflags = $(shell pkg-config glib-2.0 --cflags) -DQT_QT3SUPPORT_LIB -DQT3_SUPPORT

INCLUDES = -I$(top_srcdir)/common \
           -I/usr/include/qt4/QtGui -I/usr/include/qt4 \
           -I/usr/include/qt4/QtCore -I/usr/include/qt4/Qt3Support \
	   $(glib_cflags)

# You have two .cpp files you wrote, myapp.cpp and another.cpp
# Remember to include the name of the resource file with the .cpp extension.
rainbrurpg_server_SOURCES = resources.cpp		\
			    \
			    main.cpp             	\
                            mainwindow.cpp       	\
                            serverlog.cpp        	\
                            logexportdialog.cpp  	\
			    configdialog.cpp		\
			    serverconfiguration.cpp	\
			    technotedialog.cpp		\
			    xmlserverconf.cpp		\
			    helpviewer.cpp		\
			    enetserver.cpp		\
			    serverthread.cpp		\
			    clientlist.cpp		\
			    objectlist.cpp		\
			    ftpcontrol.cpp		\
			    ftptransfer.cpp		\
			    ftpserver.cpp		\
			    transfervisual.cpp		\
			    \
			    moc_mainwindow.cpp       	\
                            moc_serverlog.cpp        	\
                            moc_logexportdialog.cpp	\
			    moc_configdialog.cpp	\
			    moc_technotedialog.cpp	\
			    moc_helpviewer.cpp		\
			    moc_clientlist.cpp		\
			    moc_enetserver.cpp		\
			    moc_serverthread.cpp	\
			    moc_objectlist.cpp		\
			    moc_ftpcontrol.cpp		\
			    moc_ftptransfer.cpp		\
			    moc_ftpserver.cpp

# You have one .h file, it's called myapp.h. Therefore, here I list
# its mocced name, moc_myapp.cpp.
#nodist_rainbrurpg_server_SOURCES = moc_mainwindow.cpp       \
#                                   moc_serverlog.cpp        \
#                                   moc_logexportdialog.cpp

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
CLEANFILES = $(filter moc_%.cpp,$(rainbrurpg_server_SOURCES)) resources.cpp




