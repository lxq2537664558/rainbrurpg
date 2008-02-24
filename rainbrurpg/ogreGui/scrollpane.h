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
 * - 12 feb 2008 : using QuadRenderer::useParentScissor
 * - 23 nov 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SCROLLPANE_H_
#define _OGRE_GUI_SCROLLPANE_H_

#include "container.h"

#include <skinmanager.h> // For OgreGuiSkinID

// Forward declarations
namespace BetaGUI{
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class VScrollBar;
    class HScrollBar;
  }
}
// End of forward declarations

using namespace RainbruRPG::OgreGui;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** The ScrollPane policy of scrollbar drawing 
      *
      */
    typedef enum{
      SBP_NEVER = 0, //!< Never draw scrollbars
      SBP_ALWAYS,    //!< Always draw scrollbars
      SBP_IF_NEEDED  //!< Draw scrollbars only if needed
    }tScrollBarPolicy;

    /** A container that handle the clipping of child widgets and scrollbars
      *
      * Both horizontal and vertical scrollbar are drawn only if needed by
      * default.
      *
      * \note A scropane test window is created if the \c configure script
      *       is called with the \c --enable-scrollp-test option.
      *
      */
    class ScrollPane : public Container {
    public:
      ScrollPane(Vector4, Window*,OgreGuiSkinID sid=OSI_PARENT);
      virtual ~ScrollPane();

      virtual void draw(QuadRenderer*);

      void setHorizontalScrollbarPolicy(tScrollBarPolicy);
      void setVerticalScrollbarPolicy(tScrollBarPolicy);

      tScrollBarPolicy getHorizontalScrollbarPolicy(void);
      tScrollBarPolicy getVerticalScrollbarPolicy(void);

      int getMaxChildRight(void);
      int getMaxChildBottom(void);

      bool isHorizontalScrollbarNeeded(void);
      bool isVerticalScrollbarNeeded(void);

      void setScrollBarsVisbleStatus();

      virtual void setWidth(int);
      virtual void setHeight(int);

      void horizontalScrollBarValueChange(int);
      void verticalScrollBarValueChange(int);

    private:

      /** The vertical scrollbar */
      VScrollBar* mVScrollBar;

      /** The horizontal scrollbar */
      HScrollBar* mHScrollBar;

      /** The vertical scrollbar policy */
      tScrollBarPolicy mVScrollBarPolicy;

      /** The horizontal scrollbar policy */
      tScrollBarPolicy mHScrollBarPolicy;

      int xDrawingDev;
      int yDrawingDev;

    };

  }
}

#endif // _OGRE_GUI_SCROLLPANE_H_
