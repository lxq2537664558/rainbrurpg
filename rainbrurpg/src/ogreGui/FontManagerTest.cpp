#include <FontManager.hpp>
#include <OgreMinimalSetup.hpp>

#define BOOST_TEST_MODULE FontManagerTest

#include <boost/test/unit_test.hpp>

using namespace RainbruRPG;

OgreMinimalSetup* oms;

OgreGui::FontManager* setup()
{
  oms = new OgreMinimalSetup();
  oms->setupOgre("../../");
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
