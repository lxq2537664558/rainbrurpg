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

#include <FontManager.hpp>
#include <OgreMinimalSetup.hpp>

#include <boost/test/unit_test.hpp>

using namespace RainbruRPG;

OgreMinimalSetup* oms;

OgreGui::FontManager* setup()
{
  oms = new OgreMinimalSetup();
  oms->setupOgre();
  return &OgreGui::FontManager::getSingleton();
}

void teardown(OgreGui::FontManager* vFm)
{
  oms->teardownOgre();
  delete oms;
}

BOOST_AUTO_TEST_CASE( test_load_font )
{
  OgreGui::FontManager* fm=setup();
  RainbruRPG::OgreGui::Font* font = fm->loadFont("Iconiv2.ttf", 10);
  BOOST_CHECK( font );
  teardown(fm);
}

BOOST_AUTO_TEST_CASE( test_font_not_found )
{
 OgreGui::FontManager* fm=setup();
 RainbruRPG::OgreGui::Font* font=NULL;
 BOOST_CHECK_THROW( font = fm->loadFont("unexpected_font_name.ttf", 10),
		    Ogre::FileNotFoundException);
 BOOST_CHECK( font==NULL );
 teardown(fm);
}
