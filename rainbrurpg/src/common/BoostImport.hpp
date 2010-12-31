/*
 *  Copyright 2006-2011 Jerome PASQUIER, Carine CHUM
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

/** \file BoostImport.hpp
  * Implements a hack used to build in win32 due to ptrdiff_t
  *
  * Modifications :
  * - 30 nov 2010 : CamelCased this header
  * - 01 apr 2009 : Renamed from include_boost.h to boostimport.h
  * - 31 mar 2009 : Implementation
  *
  */

#ifndef RAINBRURPG_BOOST_INCLUDE
#define RAINBRURPG_BOOST_INCLUDE

/* v0.0.5-192 : When cross-compiling to win32, the config.h file
 * defined ptrdiff_t as a preprocessor macro. The boost code
 * prefix its use with the std namespace. It causes a lot of 
 * compilation errors. Undefining 'ptrdiff_t' will let
 * boost see the std::ptrdiff_t declaration.
 *
 */
#if defined __WIN32__
#  undef ptrdiff_t
#endif  

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/convenience.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#endif // !RAINBRURPG_BOOST_INCLUDE
