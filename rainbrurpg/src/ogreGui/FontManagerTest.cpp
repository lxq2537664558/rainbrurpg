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

#include <FontManager.hpp>
#include <OgreMinimalSetup.hpp>

#include <boost/test/unit_test.hpp>

using namespace RainbruRPG;


OgreGui::FontManager* setup_FontManager()
{
  return &OgreGui::FontManager::getSingleton();
}

void teardown_FontManager(OgreGui::FontManager* vFm)
{
}

BOOST_AUTO_TEST_CASE( test_1 )
{
  OgreGui::FontManager* fm=setup_FontManager();
  //  BOOST_CHECK( font );
  teardown_FontManager(fm);
}
