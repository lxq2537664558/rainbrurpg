/*
 *  Copyright 2006-2009 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file rainbrudef.h
  * Handle the GCC visibility patch and win32 declspec
  *
  * For more informations on GCC visibility please follow
  * this link : http://gcc.gnu.org/wiki/Visibility
  *
  * Modifications :
  * - 18 mar 2009 : Added gettext stuff
  * - 08 aug 2008 : Documentation update
  *
  */

// i18n stuff
#include <libintl.h>
#include <locale.h>
# define _(STRING) gettext(STRING)

#ifdef _MSC_VER
  #ifdef BUILDING_DLL
    #define RAINBRU_EXPORT __declspec(dllexport)
  #else
    #define RAINBRU_EXPORT __declspec(dllimport)
  #endif
  #define RAINBRU_LOCAL
#else
  #ifdef HAVE_GCCVISIBILITYPATCH
    #define RAINBRU_EXPORT __attribute__ ((visibility("default")))
    #define RAINBRU_LOCAL __attribute__ ((visibility("hidden")))
  #else
    #define RAINBRU_EXPORT
    #define RAINBRU_LOCAL
  #endif
#endif
