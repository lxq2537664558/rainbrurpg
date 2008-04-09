# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-xident

rainbrurpg_tools_xident_LDADD = -lrainbrurpg-common		\
				-L$(top_srcdir)/common/.libs 

INCLUDES = -I$(top_srcdir)/common

rainbrurpg_tools_xident_SOURCES = main.cpp			\
			   	  xidentwindow.cpp		\
				  foxaccountlist.cpp		\
				  foxserverlist.cpp		\
				  addserver.cpp			\
				  deleteserver.cpp		\
				  modifyserver.cpp		\
				  serverdesc.cpp		\
				  servertechnote.cpp		\
				  foxpersolist.cpp		\
				  addaccount.cpp
