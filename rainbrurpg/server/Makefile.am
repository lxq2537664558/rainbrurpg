# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-server

rainbrurpg_server_LDADD=-lQtCore -lQtGui -lrainbrurpg-common 	\
			-lrainbrurpg-design 			\
			-L$(top_srcdir)/common/.libs 		\
			-L$(top_srcdir)/design/.libs 		\
			-lQtSql 				\
			-lQt3Support				\
			$(GLIB_LIBS)

INCLUDES = -I$(top_srcdir)/common -I$(top_srcdir)/design 	\
           -I/usr/include/qt4/QtGui -I/usr/include/qt4 		\
           -I/usr/include/qt4/QtCore 				\
	   -I/usr/include/qt4/Qt3Support 			\
	   $(GLIB_CFLAGS)					\
	   -DQT_QT3SUPPORT_LIB -DQT3_SUPPORT

MOC_FILES = 		    moc_mainwindow.cpp       	\
                            moc_serverlog.cpp        	\
                            moc_logexportdialog.cpp	\
			    moc_configdialog.cpp	\
			    moc_technotedialog.cpp	\
			    moc_clientlist.cpp		\
			    moc_enetserver.cpp		\
			    moc_serverthread.cpp	\
			    moc_objectlist.cpp		\
			    moc_ftpcontrol.cpp		\
			    moc_ftptransfer.cpp		\
			    moc_ftpserver.cpp		\
			    moc_ftpdataconnection.cpp   \
			    moc_quarantinelist.cpp           


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
			    enetserver.cpp		\
			    serverthread.cpp		\
			    clientlist.cpp		\
			    objectlist.cpp		\
			    ftpcontrol.cpp		\
			    ftptransfer.cpp		\
			    ftpserver.cpp		\
			    transfervisual.cpp		\
			    ftpdataconnection.cpp	\
			    uniquename.cpp              \
			    quarantinelist.cpp

# You have one .h file, it's called myapp.h. Therefore, here I list
# its mocced name, moc_myapp.cpp.
nodist_rainbrurpg_server_SOURCES = $(MOC_FILES)

# This is to ensure the myapp.h file is distributed in your myapp-0.1.tar.gz
# I also have a resources.qrc I need to include. The png is used in myapp.
#EXTRA_DIST = \
#	$(nodist_myapp_SOURCES:moc_%.cpp=%.h) \
#	resources.qrc myapp.png

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp : %.h
	moc-qt4 $< -o $@

# Adjust this line according to your resources.qrc
resources.cpp : resources.qrc
	rcc resources.qrc -o resources.cpp

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = 	$(MOC_FILES) 		\
		resources.cpp




