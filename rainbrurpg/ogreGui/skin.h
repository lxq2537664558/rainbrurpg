/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

/* Modifications :
 * - 27 sep 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_H_
#define _OGRE_GUI_SKIN_H_

#include <string>

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{

    /** The base class of all skins
      *
      * It defines some pure virtual functions that must be reimplemented.
      *
      */
    class Skin{
      std::string getName(void);
      void setName(std::string);

      virtual void drawWindow(unsigned int x, unsigned int y,
			      unsigned int w, unsigned int h);

    private:
      /** The name of the skin */
      std::string name;
    };

  }
}

#endif // _OGRE_GUI_SKIN_H_
