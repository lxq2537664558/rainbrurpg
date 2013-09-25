#  Copyright 2006-2013 Jerome PASQUIER
# 
#  This file is part of RainbruRPG.
#
#  RainbruRPG is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  RainbruRPG is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with RainbruRPG; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301  USA

# The final program is called "myapp"
bin_PROGRAMS = rainbrurpg-tools-netflooder

#add_libs = $(shell pkg-config --libs glib-2.0 sigc++-2.0)

rainbrurpg_tools_netflooder_LDADD = -lrainbrurpg-common 	\
				    -lglib-2.0 			\
				    -lsigc-2.0			\
				    -L$(top_srcdir)/src/common/.libs\
				    $(GLIB_LIBS) 		\
				    $(SIGC_LIBS)

INCLUDES = -I$(top_srcdir)/src/common 				\
	   -I$(top_srcdir)/ext	 				\
	   $(GLIB_CFLAGS)					\
	   $(SIGC_CFLAGS)

rainbrurpg_tools_netflooder_SOURCES = main.cpp			\
				      netflooderwindow.cpp	\
				      connectionpanel.cpp	\
				      waitingpanel.cpp		\
				      enetflooderclient.cpp	\
				      floodpanel.cpp		\
				      floodertestbase.cpp	\
				      ftreliable.cpp		\
				      chartviewer.cpp