/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

#include "Brush.hpp"
#include <OgreMinimalSetup.hpp>

#include <boost/test/unit_test.hpp>

using namespace RainbruRPG::OgreGui;

Brush* setup_Brush()
{

}

void teardown_Brush(Brush*)
{

}

/// It is a dummy test only for memory management purpose
BOOST_AUTO_TEST_CASE( test_bush_construct )
{
  Brush* instance = setup_Brush();
  teardown_Brush(instance);
}
