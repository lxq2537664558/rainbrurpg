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
 * - 02 jan 2007 : Linux window handle modification. Assertion added.
 *
 */


#ifndef InputManager_H
#define InputManager_H

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISJoyStick.h>
#include <OIS/OISInputManager.h>

#include <OGRE/OgreRenderWindow.h>

namespace RainbruRPG {
  namespace Core{

    /** An input manager for OIS to be used with Ogre3D
      *
      * \warning Do not forget to call capture() for each frame. If
      * you do not call the capture function, no listener will be 
      * able to get events.
      *
      */
    class InputManager : public OIS::KeyListener, OIS::MouseListener, 
      OIS::JoyStickListener {
    public:
      virtual ~InputManager( void );
      
      void initialise( Ogre::RenderWindow *renderWindow );
      void capture( void );
      
      void addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName );
      void addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName );
      void addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName );
      
      void removeKeyListener( const std::string& instanceName );
      void removeMouseListener( const std::string& instanceName );
      void removeJoystickListener( const std::string& instanceName );
      
      void removeKeyListener( OIS::KeyListener *keyListener );
      void removeMouseListener( OIS::MouseListener *mouseListener );
      void removeJoystickListener( OIS::JoyStickListener *joystickListener );
      
      void removeAllListeners( void );
      void removeAllKeyListeners( void );
      void removeAllMouseListeners( void );
      void removeAllJoystickListeners( void );
      
      void setWindowExtents( int width, int height );
      
      OIS::Mouse*    getMouse( void );
      OIS::Keyboard* getKeyboard( void );
      OIS::JoyStick* getJoystick( unsigned int index );
      
      int getNumOfJoysticks( void );
      
      static InputManager* getSingletonPtr( void );

    private:
      InputManager( void );
      /** A forbidden constructor */
      InputManager( const InputManager& ) { }
      /** A forbidden constructor */
      InputManager & operator = ( const InputManager& );
      
      bool keyPressed( const OIS::KeyEvent &e );
      bool keyReleased( const OIS::KeyEvent &e );
      
      bool mouseMoved( const OIS::MouseEvent &e );
      bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
      bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );
      
      bool povMoved( const OIS::JoyStickEvent &e, int pov );
      bool axisMoved( const OIS::JoyStickEvent &e, int axis );
      bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
      bool buttonPressed( const OIS::JoyStickEvent &e, int button );
      bool buttonReleased( const OIS::JoyStickEvent &e, int button );
      
      /** The OIS InputManager */
      OIS::InputManager *mInputSystem;
      /** The mouse */
      OIS::Mouse        *mMouse;
      /** The keyboard */
      OIS::Keyboard     *mKeyboard;
      
      /** A vector of joystick */
      std::vector<OIS::JoyStick*> mJoysticks;
      /** An iterator of joystick vector */
      std::vector<OIS::JoyStick*>::iterator itJoystick;
      /** An iterator of joystick vector */
      std::vector<OIS::JoyStick*>::iterator itJoystickEnd;
      
      /** A map of key listener */  
      std::map<std::string, OIS::KeyListener*> mKeyListeners;
      /** A map of mouse listener */  
      std::map<std::string, OIS::MouseListener*> mMouseListeners;
      /** A map of joystick listener */  
      std::map<std::string, OIS::JoyStickListener*> mJoystickListeners;
      
      /** An iterator for the key listener map */  
      std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
      /** An iterator for the mouse listener map */
      std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;
      /** An iterator for the joystick listener map */
      std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener;
      
      /** An iterator for the key listener map */  
      std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
      /** An iterator for the mouse listener map */
      std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;
      /** An iterator for the joystick listener map */
      std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListenerEnd;
      
      /** The unique static instance */
      static InputManager *mInputManager;
    };
  }
}
#endif
