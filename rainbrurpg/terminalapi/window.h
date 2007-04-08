/*
 *  Copyright 2006 Jerome PASQUIER
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
#ifndef WINDOW_H
#define WINDOW_H

#include <slang.h>
#include <string>

#include "scrollingpanel.h"
#include "layout.h"
#include "freelayout.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** The state of a window
      *
      */
    enum tWindowState {
      HIDDEN,     //!< The window is not visible
      NORMAL,     //!< No special flag has been set
      MINIMIZED,  //!< Only the title is visible
      MAXIMIZED   //!< The window is fullscreen
    };

    /** A terminal window that can be added to the TerminalApp
      *
      * the focusWindow property defines if we are focusing the Window
      * or its Widgets. We must toggle this property with the F11 key.
      * 
      */
    class Window{
    public:
      Window();
      Window( const char* );
      virtual ~Window();

      void setCaption( const char* );
      void setX( int );
      void setY( int );
      void setWidth( int );
      void setHeight( int );
      void setVisible( bool );
      void setState(tWindowState);
      void setSelected( bool );

      void show();
      void hide();

      void move( int, int );
      void resize( int, int );

      const char* getCaption( );
      int getX( );
      int getY( );
      int getWidth( );
      int getHeight( );
      Layout* getLayout();

      bool isVisible();
      bool isSelected();

      /** The draw() method inherited from Widget */
      virtual void draw();

    private:
      /** The state of the window 
        *
        * use setState to change it
        */
      tWindowState state;

      /** The last state used by this window
        *
	* It is used to store the state before hidding it.
	*/
      tWindowState lastState;

      /** The panel providing the scrolling ability
        *
	*/
      ScrollingPanel* panel;

      /** The window layout
        *
	*/
      Layout* layout;

      /** The title string of the window 
        *
	*/
      const char* caption;

      /** The horizontal position */
      int x;

      /** The vertical position */
      int y;

      /** The width */
      int width;

      /** The height */
      int height;

      /** Is the window selected
        *
	* If true (with focusWindow at true), the border is in green, 
	* otherwise, it is in white.
	*/
      bool selected;

      /** Is the focus in the Window or in its Widgets
        *
	*
	*/
      bool focusWindow;

    };
  }
}

#endif // WINDOW_H
