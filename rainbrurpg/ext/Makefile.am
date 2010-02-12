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

# Simply create a 'libtool convenience library' because this code is note
# mine. It is later incorporated in the common/ library. Headers are
# installed in the common directory

noinst_LTLIBRARIES = libexternal.la

h_sources= EasyBMP_BMP.h			\
	   EasyBMP_DataStructures.h		\
	   EasyBMP.h				\
	   EasyBMP_VariousBMPutilities.h	\
	   tinystr.h				\
	   tinyxml.h

libexternal_la_SOURCES = EasyBMP.cpp		\
			 tinystr.cpp		\
			 tinyxml.cpp		\
			 tinyxmlerror.cpp	\
			 tinyxmlparser.cpp

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)/$(LIB_COMMON_NAME)
library_include_HEADERS = $(h_sources)
INCLUDES = -I$(top_srcdir)/common/