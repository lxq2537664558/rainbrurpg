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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/* Modifications :
 * - 26 may 2006 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_WIDGET_DRAWER_MULTI_COLUMN_LIST_H_
#define _OGRE_GUI_WIDGET_DRAWER_MULTI_COLUMN_LIST_H_

#include "widgetdrawer.h"

#include <OgreTexture.h>
#include <OgreColourValue.h>
#include <OgreRectangle.h>

/** Defines the space between header lines and background rectangle */
# define HEADER_BG_SPACE 2


// Forward declarations
namespace BetaGUI{
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class MultiColumnList;
    class Widget;
    class TextSettings;
    class MultiColumnListColumn;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** A class used to draw MultiColumnList
      *
      */
    class wdMultiColumnList : public WidgetDrawer{
    public:
      wdMultiColumnList();
      virtual ~wdMultiColumnList();

      void preDrawingComputation(MultiColumnList*);
      void draw(QuadRenderer*, MultiColumnList*);

    protected:
      void init(MultiColumnList*);

      void drawBorder(QuadRenderer*);
      void drawAllHeaders(QuadRenderer*, MultiColumnList*, int);
      void drawOneHeader(QuadRenderer*, MultiColumnListColumn*, int);

    private:
      /** The texture used to draw the MultiColumnList column indicator
        * when no sort was selected
	*/
      TexturePtr mMclColumnNoSort;

       /** The texture used to draw the MultiColumnList column indicator
        * when ascendant sort was selected
	*/
      TexturePtr mMclColumnAscSort;

      /** The texture used to draw the MultiColumnList column indicator
        * when descendant sort was selected
	*/
      TexturePtr mMclColumnDescSort;

      /** The MultiColumnList parent, used to get some values */
      Widget* mWidgetParent;

      /** Is this drawer initialized */
      bool wasInit;

      /** The text setting used to draw column header */
      TextSettings* tsMclColumnHeader;

      /** The MultiColumnList absolute corners */
      Ogre::Rectangle mMclAbsCorners;

      /** The border column */
      Ogre::ColourValue mMclBorderColor;

      /** The absolute position of the bottom line of the headers */
      int mMclHeaderBottomLine;

      /** The rectangle used to draw the column header caption*/
      Ogre::Rectangle mColumnCaption;
      
      /**  Used to test left line visibility */
      int maxMclRight;
    };

  }
}


#endif // _OGRE_GUI_WIDGET_DRAWER_MULTI_COLUMN_LIST_H_
