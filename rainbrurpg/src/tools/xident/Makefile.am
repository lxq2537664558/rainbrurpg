#  Copyright 2006-2010 Jerome PASQUIER
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

# The final program is called "rainbrurpg-tools-xident"
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
