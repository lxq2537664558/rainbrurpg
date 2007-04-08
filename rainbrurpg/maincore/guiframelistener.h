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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef GUI_FRAME_LISTENER
#define GUI_FRAME_LISTENER

#include <logger.h>

//mem probs without this next one
#include <OgreNoMemoryMacros.h>
#include <CEGUI/CEGUIImageset.h>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUILogger.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIFontManager.h>
#include <CEGUI/CEGUIWindow.h>
//#include <CEGUI/elements/CEGUIPushButton.h>

#include "OgreCEGUIRenderer.h"
#include "OgreCEGUIResourceProvider.h"
//regular mem handler
#include <OgreMemoryMacros.h> 
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
                             public MouseMotionListener, 
                             public MouseListener{
      
    private:
      /** The CEGUI renderer */
      CEGUI::Renderer* mGUIRenderer;
      /** A flag saying if we have requested the shutdown of the engine */
      bool mShutdownRequested;

    public:
      // NB using buffered input
      GuiFrameListener(RenderWindow* win, Camera* cam, 
		       CEGUI::Renderer* renderer);
       

      void setCamera(Camera*);

      // Tell the frame listener to exit at the end of the next frame
      void requestShutdown(void);


      virtual bool frameStarted(const FrameEvent& evt);
      virtual bool frameEnded(const FrameEvent& evt);

      void mouseMoved (MouseEvent *e);
      void mouseDragged (MouseEvent *e);
      void mousePressed (MouseEvent *e);
      void mouseReleased (MouseEvent *e);
      /** An empty mouse clicked event listener */
      void mouseClicked(MouseEvent* e) {}
      /** An empty mouse entered event listener */
      void mouseEntered(MouseEvent* e) {}
      /** An empty mouse exited event listener */
      void mouseExited(MouseEvent* e) {}
      void keyPressed(KeyEvent* e);
      void keyReleased(KeyEvent* e);
      void keyClicked(KeyEvent* e);

    };

  }

}

#endif // GUI_FRAME_LISTENER
