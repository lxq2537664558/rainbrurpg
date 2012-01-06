
/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

#include "WindowHandle.hpp"
#include "NullWindowHandleException.hpp"

#include <OgreMinimalSetup.hpp>

#define BOOST_TEST_MODULE WindowHandleTest

#include <boost/test/unit_test.hpp>

using namespace RainbruRPG::Core;
using namespace RainbruRPG::Exception;

// Define a configuration directory according to the platform
#ifdef WIN32
#  define CONFIG_DIR "./"
#else
#  define CONFIG_DIR "../../"
#endif

OgreMinimalSetup* oms;

void setup()
{
  oms = new OgreMinimalSetup();
  oms->setupOgre(CONFIG_DIR);
}

void teardown()
{
  oms->teardownOgre();
  delete oms;
}

BOOST_AUTO_TEST_CASE( test_null_render_window )
{
  // Need an initialization of Ogre because uses Ogre::Root
  setup();
  BOOST_CHECK_THROW(WindowHandle::get(NULL), NullWindowHandleException);
  teardown();
}

BOOST_AUTO_TEST_CASE( test_non_null_handle )
{
  // Need an initialization of Ogre because uses Ogre::Root
  setup();
  size_t winHnd = WindowHandle::get(oms->getRenderWindow());
  BOOST_CHECK(winHnd != 0);
  teardown();
}
