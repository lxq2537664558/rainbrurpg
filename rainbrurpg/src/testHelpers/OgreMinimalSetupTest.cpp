/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

#include <OgreMinimalSetup.hpp>

#define BOOST_TEST_MODULE OgreMinimalSetupTest

#include <boost/test/unit_test.hpp>

OgreMinimalSetup* oms;

void setup()
{
  oms = new OgreMinimalSetup();
}

void teardown()
{
  delete oms;
}

BOOST_AUTO_TEST_CASE( test_setup_pointer )
{
  setup();
  BOOST_CHECK( oms );
  teardown();
}

BOOST_AUTO_TEST_CASE( test_setup_ogre_throw )
{
  setup();
  BOOST_CHECK_THROW( oms->setupOgre("../unbelievable_directory_name_for_configuration_files"),
		     std::string);
  teardown();
}

BOOST_AUTO_TEST_CASE( test_setup_ogre_correct_config )
{
  setup();
  BOOST_CHECK( oms );
  oms->setupOgre("../../");
  //  oms->teardownOgre();
  teardown();
}
