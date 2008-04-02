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

#ifndef GUI_FRAME_LISTENER
#define GUI_FRAME_LISTENER

#include <logger.h>

#include "exampleframelistener.h"

#include "guimanager.h"
#include "gameengine.h"

using namespace RainbruRPG::Gui;
using namespace RainbruRPG::Core;


namespace RainbruRPG{
  namespace Events{

    /** A frame listener designed for GUI gamestates
      *
      *
      */
    class GuiFrameListener : public ExampleFrameListener, 
                             public MouseListener{

    public:
      GuiFrameListener(RenderWindow* win, Camera* cam);
       

      void setCamera(Camera*);

      // Tell the frame listener to exit at the end of the next frame
      void requestShutdown(void);


      virtual bool frameStarted(const FrameEvent& evt);
      virtual bool frameEnded(const FrameEvent& evt);

      bool mouseMoved (const OIS::MouseEvent& e);
      bool mouseDragged(const OIS::MouseEvent& e);
      bool mousePressed(const OIS::MouseEvent& e);
      bool mouseReleased(const OIS::MouseEvent& e);

      /** A unimplemented function
        *
	* \param e The event
	* \param btn The button identifier
	*
	* \return nothing
	*
	*/
      virtual bool mousePressed(const OIS::MouseEvent& e, 
				OIS::MouseButtonID btn){};
      /** A unimplemented function
        *
	* \param e The event
	* \param btn The button identifier
	*
	* \return nothing
	*
	*/
      virtual bool mouseReleased(const OIS::MouseEvent& e, 
				 OIS::MouseButtonID btn){};

      /** An empty mouse clicked event listener */
      void mouseClicked(OIS::MouseEvent* e) {}
      /** An empty mouse entered event listener */
      void mouseEntered(OIS::MouseEvent* e) {}
      /** An empty mouse exited event listener */
      void mouseExited(OIS::MouseEvent* e) {}

      bool keyPressed(const KeyEvent& e);
      bool keyReleased(const KeyEvent& e);
      bool keyClicked(const KeyEvent& e);
      
    private:
      /** A flag saying if we have requested the shutdown of the engine */
      bool mShutdownRequested;
      float mMoveScale;
    };

  }

}

#endif // GUI_FRAME_LISTENER
