/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file scrollingpanel.h
  * Declares a class that provides scrolling ability of a window
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef SCROLLING_PANEL_H
#define SCROLLING_PANEL_H

#include <list>


#include "slangcommand.h"

namespace RainbruRPG{
  namespace Terminal{

    /** A stl list of SLangCommand */
    typedef std::list<SLangCommand*> tSLangCommandList;

    /** Provides the scrolling ability of the Window
      *
      * The scrolling ability is done by logical and physical
      * dimension. The xOffset and yOffset values is the position of
      * the first visible caractèer.
      *
      * The goDown(), goUp(), goRight() and goLeft() functions must be
      * called when the corresponding arrows keys are pressed.
      *
      * The ability to draw is done by a list of SLangCommand subclasses.
      * eEach slc* is a wrapper to a S-Lang operation.
      *
      */
    class ScrollingPanel{
    public:
      ScrollingPanel();
      ~ScrollingPanel();

      void setPhysicalSize(int, int);
      void setLogicalSize(int, int);

      void setPhysicalWidth(int);
      void setPhysicalHeight(int);
      void setLogicalWidth(int);
      void setLogicalHeight(int);

      void setXOffset(int);
      void setYOffset(int);

      void goDown();
      void goUp();
      void goRight();
      void goLeft();

      int getPhysicalWidth();
      int getPhysicalHeight();
      int getLogicalWidth();
      int getLogicalHeight();
      int getXOffset();
      int getYOffset();



    private:
      /** The list of SLang commands */
      tSLangCommandList commandList;

      /** The width of the physical screen
        *
	*/
      int physicalWidth;

      /** The height of the physical screen
        *
	*/
      int physicalHeight;

      /** The width of the logical screen
        *
	*/
      int logicalWidth;

      /** The height of the logical screen
        *
	*/
      int logicalHeight;

      /** The x offset of the physical screen
        *
	*/
      int xOffset;

      /** The y offset of the physical screen
        *
	*/
      int yOffset;
    };

  }
}

#endif // SCROLLING_PANEL_H
