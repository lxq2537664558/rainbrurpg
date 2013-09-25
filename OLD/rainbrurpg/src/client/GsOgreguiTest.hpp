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

/** \file GsOgreguiTest.hpp
  * Declares an OgreGui test game state
  *
  * Modifications :
  * - 22 mar 2010 : Implementation started
  *
  */

#ifndef GS_OGREGUI_TEST_H
#define GS_OGREGUI_TEST_H

#include "GsMenuBase.hpp"

namespace RainbruRPG {
  namespace Core{

    /** A gamestate to test OgreGui
      *
      */
    class gsOgreguiTest : public gsMenuBase{
    public:
      gsOgreguiTest();
      virtual ~gsOgreguiTest();

      virtual void init();
      virtual void resume();
      virtual void pause();

      // Purely virtual in gsmenubase
      virtual void setupTabOrder(){

      };
    };
  }
}
#endif // GS_OGREGUI_TEST_H