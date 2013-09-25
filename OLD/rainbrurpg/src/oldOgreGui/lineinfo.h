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

/** \file lineinfo.h
  * Declares a class that stores infos about a single line of text
  *
  * Modifications :
  * - 29 oct 2009 : Made messages transatable with gettext
  * - 26 aug 2008 : Single file documentation
  * - 07 dec 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_LINE_INFO_H_
#define _OGRE_GUI_LINE_INFO_H_

#include <string>
#include <RainbruDef.hpp>    // For the GNU gettext stuff

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{
    /** Stores the contents and width of a single line of text. Used 
      * for optimized caching of pre-processed GUI text
      *
      */
    class LineInfo{
    public:
      LineInfo( const std::string& vText, float vWidth);
      LineInfo();

      float getWidth() const;
      const std::string& getText()const;

    private:
      /** The text contained in this line */
      std::string text;
      /** The width of this line of text */
      float width;

    };

  }
}

#endif // _OGRE_GUI_LINE_INFO_H_
