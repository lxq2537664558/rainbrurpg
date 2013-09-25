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

# The final program is called "rainbrurpg-examples-tapi"
bin_PROGRAMS = rainbrurpg-examples-tapi-01		\
	       rainbrurpg-examples-tapi-02

INCLUDES = 	-I$(top_srcdir)/terminalapi 		\
		-I$(top_srcdir)/common

rainbrurpg_examples_tapi_01_LDADD = -lrainbrurpg-terminalapi		\
				 -L$(top_srcdir)/terminalapi/.libs 	\
				 -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 

rainbrurpg_examples_tapi_01_SOURCES = example_tapi_01.cpp

rainbrurpg_examples_tapi_02_LDADD = -lrainbrurpg-terminalapi		\
				 -L$(top_srcdir)/terminalapi/.libs 	\
				 -lrainbrurpg-common			\
				 -L$(top_srcdir)/common/.libs 

rainbrurpg_examples_tapi_02_SOURCES = example_tapi_02.cpp
