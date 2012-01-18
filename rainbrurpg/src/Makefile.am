#  Copyright 2006-2012 Jerome PASQUIER
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

SUBDIRS=testHelpers interdep common ogreGui maincore client 

if RB_OPTION_TOOLS_FLAGS
  SUBDIRS+=tools
endif

if RB_OPTION_SERVER_FLAGS
  SUBDIRS+=server
endif

if RB_OPTION_TESTS_FLAGS
  SUBDIRS+=tests
endif

if RB_OPTION_TAPI_FLAGS
  SUBDIRS+=terminalapi
endif

if BUILD_LIB_DESIGN
  SUBDIRS+=design
endif

if RB_OPTION_EDITOR_FLAGS
  SUBDIRS+=editor
endif

if RB_OPTION_EXAMPLES_FLAGS
  SUBDIRS+=examples
endif
