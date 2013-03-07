
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

#include <Glyph.hpp>

#include <boost/test/unit_test.hpp>

#include <OgreTexture.h>

using namespace RainbruRPG;

#define GLYPH_OFFX 2.0f // The X offset
#define GLYPH_OFFY 3.0f // The Y offset
#define GLYPH_VSPA 6.0f // The vertical spacing
#define GLYPH_CC   95   // The charcode

void setup_glyph_geometry(Ogre::Rectangle* r)
{
  r->top = 10;
  r->left = 12;
  r->bottom = 20;
  r->right = 24;
}

bool ogre_glyph_compare_rectangle(Ogre::Rectangle r1,Ogre::Rectangle r2)
{
  return (r1.top == r2.top) &&
    (r1.left == r2.left) &&
    (r1.bottom == r2.bottom) &&
    (r1.right == r2.right);
}

OgreGui::Glyph* setup_Glyph()
{
  Ogre::Rectangle r;
  setup_glyph_geometry (&r); 
  return new OgreGui::Glyph(r, GLYPH_OFFX, 
			    GLYPH_OFFY, GLYPH_VSPA, GLYPH_CC);
}

void teardown_Glyph(OgreGui::Glyph* vF)
{
  delete vF;
}

// Check default constructor
BOOST_AUTO_TEST_CASE( test_glyph_empty )
{
  Ogre::Rectangle r;
  r.top    = 0;
  r.left   = 0;
  r.bottom = 0;
  r.right  = 0;

  OgreGui::Glyph g;
  BOOST_CHECK( ogre_glyph_compare_rectangle(g.getGeometry(), r));
  BOOST_CHECK( g.getSpace () == 0.0f);
  BOOST_CHECK( g.getHeight () == 0.0f);
  BOOST_CHECK( g.getWidth () == 0.0f);
  BOOST_CHECK( g.getOffsetX () == 0.0f);
  BOOST_CHECK( g.getOffsetY () == 0.0f);
  BOOST_CHECK( g.getTop () == 0.0f);
  BOOST_CHECK( g.getLeft () == 0.0f);
  BOOST_CHECK( g.getRight () == 0.0f);
  BOOST_CHECK( g.getBottom () == 0.0f);
  BOOST_CHECK( g.getCharCode () == 0);
}

BOOST_AUTO_TEST_CASE( test_glyph_params )
{
  OgreGui::Glyph* g = setup_Glyph ();
  Ogre::Rectangle r;
  setup_glyph_geometry (&r); 

  BOOST_CHECK( ogre_glyph_compare_rectangle(g->getGeometry(), r));
  BOOST_CHECK( g->getSpace () == GLYPH_VSPA);
  BOOST_CHECK( g->getOffsetX () == GLYPH_OFFX);
  BOOST_CHECK( g->getOffsetY () == GLYPH_OFFY);
  BOOST_CHECK( g->getCharCode () == GLYPH_CC);
  teardown_Glyph (g);
}
