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

#include <Container.hpp>

//#define BOOST_TEST_MODULE ContainerTest
#include <boost/test/unit_test.hpp>

using namespace RainbruRPG::OgreGui;

Container* setup_container()
{
  return new Container(NULL, "TestedContainer", 0, 0, 10, 10);;
}

void teardown_container(Container* vContainer)
{
  delete vContainer;
}

/** Tests that an empty container always returns \c false
  * for events handling functions
  *
  */
BOOST_AUTO_TEST_CASE( test_empty )
{
  bool ret;
  Container* tested_container = setup_container();

  OIS::KeyEvent ke(NULL, OIS::KC_A, 0);

  ret = tested_container->keyPressed( ke );
  BOOST_CHECK( ret == false);

  ret = tested_container->keyReleased( ke );
  BOOST_CHECK( ret == false);

  teardown_container(tested_container);
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE( test_container_true_focusable )
{
  bool ret;
  OIS::KeyEvent ke(NULL, OIS::KC_A, 0);
  Container* m_instance = setup_container();

  // Widget is a true focusable by default
  Widget w(NULL, "test widget", 0, 0, 10, 10);
  m_instance->push_back(&w);

  // Should always return false because focused widget
  // didn't change
  ret = m_instance->keyPressed( ke );
  BOOST_CHECK( ret == false);

  ret = m_instance->keyReleased( ke );
  BOOST_CHECK( ret == false);

  // Focus the added widget
  m_instance->focusNext();

  ret = m_instance->keyPressed( ke );
  BOOST_CHECK( ret == false);

  ret = m_instance->keyReleased( ke );
  BOOST_CHECK( ret == false);

  teardown_container(m_instance);
}

/** When a child is pushed back to a container
  * The dirty flag should be propagated to the parent container.
  *
  */
BOOST_AUTO_TEST_CASE( test_container_pushback_set_dirtyflag )
{
  Container* m_instance = setup_container();
  BOOST_CHECK( m_instance->isDirty() == true ); // true by default
  m_instance->compute(0,0, Ogre::Rectangle());
  BOOST_CHECK( m_instance->isDirty() == false );

  // Widget is a true focusable by default
  Widget w(m_instance, "test widget", 0, 0, 10, 10);
  m_instance->push_back(&w);
  BOOST_CHECK( m_instance->isDirty() == true );

  teardown_container(m_instance);
}
