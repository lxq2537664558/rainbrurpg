/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    ExampleFrameListener.h
Description: Defines an example frame listener which responds to frame events.
This frame listener just moves a specified camera around based on
keyboard and mouse movements.
Mouse:    Freelook
W or Up:  Forward
S or Down:Backward
A:        Step left
D:        Step right
             PgUp:     Move upwards
             PgDown:   Move downwards
             F:        Toggle frame rate stats on/off
			 R:        Render mode
             T:        Cycle texture filtering
                       Bilinear, Trilinear, Anisotropic(8)
             P:        Toggle on/off display of camera position / orientation
-----------------------------------------------------------------------------
*/

#ifndef __ExampleFrameListener_H__
#define __ExampleFrameListener_H__

#include <Ogre.h>

#include <OIS.h>

#include <logger.h>

using namespace Ogre;
using namespace OIS;

namespace RainbruRPG{
  namespace Core{

    /**
      *
      * \todo remove EventProcessor, InputReader
      *
      */
    class ExampleFrameListener: public FrameListener, public KeyListener{

    public:
      // Constructor takes a RenderWindow because it uses 
      // that to determine input context
      ExampleFrameListener(RenderWindow*, Camera* ,  
			   bool useBufferedInputKeys = false, 
			   bool useBufferedInputMouse = false);

      virtual ~ExampleFrameListener();

      virtual bool processUnbufferedKeyInput(const FrameEvent& evt);

      bool processUnbufferedMouseInput(const FrameEvent& evt);

      virtual void moveCamera();

//      void showDebugOverlay(bool show){ }
      
      // Override frameStarted event to process that 
      //(don't care about frameEnded)
      bool frameStarted(const FrameEvent& evt);
      
      void switchMouseMode();
      void switchKeyMode();
      void keyClicked(KeyEvent* e);
      
      /** The key pressed event listener */
      void keyPressed(KeyEvent* e) {}
      /** The key released event listener */
      void keyReleased(KeyEvent* e) {}
      
    protected:
      /** The Ogre Event processor */
      //    EventProcessor* mEventProcessor;
      /** The input device */
      //      InputReader* mInputDevice;
      /** The Ogre camera */
      Camera* mCamera;
      /** The translation vector */
      Vector3 mTranslateVector;
      /** The Ogre render windows */
      RenderWindow* mWindow;
      /** Do we show statistics */
      bool mStatsOn;
      /** Do we use buffered input keys */
      bool mUseBufferedInputKeys;
      /** Do we use buffered input mouse */
      bool mUseBufferedInputMouse;
      /** Used to switch input type */
      bool mInputTypeSwitchingOn;

      /** The number of screenshots we took */
      unsigned int mNumScreenShots;
      /** The moving scale of the camera */
      float mMoveScale;
      /** The rotation scale of the camera */
      Degree mRotScale;
      /** just to stop toggles flipping too fast */
      Real mTimeUntilNextToggle;
      /** The X rotation value */
      Radian mRotX;
      /** The Y rotation value */
      Radian mRotY;
      /** The texture options */
      TextureFilterOptions mFiltering;
      /** The anisotropic value */
      int mAniso;
      /** The scene detail index */
      int mSceneDetailIndex ;
      /** The moving speed of the camera */
      Real mMoveSpeed;
      /** The rotate speed of the camera */
      Degree mRotateSpeed;
      
    };
  }
}

#endif
