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

#include <Font.hpp>

#include <boost/test/unit_test.hpp>

#include <OgreTexture.h>

using namespace RainbruRPG;

#define FONT_NAME "a_font"
#define FONT_SIZE 10
#define FONT_TEXTURE_NAME "Font_texture"

OgreGui::Font* setup_Font()
{
  return new OgreGui::Font(FONT_NAME, FONT_SIZE);
}

void teardown_Font(OgreGui::Font* vF)
{
  delete vF;
}

BOOST_AUTO_TEST_CASE( test_name )
{
  OgreGui::Font* f=setup_Font();
  BOOST_CHECK( FONT_NAME == f->getName() );
  teardown_Font(f);
}

BOOST_AUTO_TEST_CASE( test_size )
{
  OgreGui::Font* f=setup_Font();
  BOOST_CHECK( FONT_SIZE == f->getSize() );
  teardown_Font(f);
}

BOOST_AUTO_TEST_CASE( test_texture_ptr )
{
  Ogre::TexturePtr tptr= Ogre::TexturePtr();

  OgreGui::Font* f=setup_Font();
  f->setTexture ( tptr );
  BOOST_CHECK( f->getTexture() == tptr );
  teardown_Font(f);
}

BOOST_AUTO_TEST_CASE( test_glyphmap )
{
  OgreGui::Font* f=setup_Font();
  GlyphMap gm = f->getGlyphMap ();
  BOOST_CHECK( gm.size() == 0 );
  teardown_Font(f);
}

BOOST_AUTO_TEST_CASE( test_maxglyphheight )
{
  OgreGui::Font* f=setup_Font();
  size_t mgh = f->getMaxGlyphHeight ();
  BOOST_CHECK( GLYPH_V_SPACE + FONT_SIZE == mgh );
  teardown_Font(f);
}

BOOST_AUTO_TEST_CASE( test_maxbearingy )
{
  OgreGui::Font* f=setup_Font();
  int mby= f-> getMaxBearingY();
  BOOST_CHECK( 0 == mby );
  teardown_Font(f);
}

BOOST_AUTO_TEST_CASE( test_settexturename )
{
  OgreGui::Font* f=setup_Font();
  f->setTextureName( FONT_TEXTURE_NAME );
  BOOST_CHECK( f->getTextureName () == FONT_TEXTURE_NAME );
  teardown_Font(f);
}

