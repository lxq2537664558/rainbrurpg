/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file inputmanager.cpp
  * Implements an input manager for OIS to be used with Ogre3D
  *
  */

#include "inputmanager.h"

#include <logger.h>

#include "WindowHandle.hpp"
#include "../../config.h"
#include "NullWindowHandleException.hpp"

#ifdef WIN32
#  include <OgreD3D9RenderWindow.h>
#endif // WIN32

RainbruRPG::Core::InputManager *RainbruRPG::Core::InputManager::mInputManager;

using namespace RainbruRPG::Exception;

/** The default constructor
  *
  */
RainbruRPG::Core::InputManager::InputManager( void ) :
    mMouse( NULL ),
    mKeyboard( NULL ),
    mInputSystem( NULL ) 
{

}

/** The default destructor
  *
  */
RainbruRPG::Core::InputManager::~InputManager( void ) {
    if( mInputSystem ) {
        if( mMouse ) {
            mInputSystem->destroyInputObject( mMouse );
            mMouse = 0;
        }

        if( mKeyboard ) {
            mInputSystem->destroyInputObject( mKeyboard );
            mKeyboard = 0;
        }

        if( mJoysticks.size() > 0 ) {
            itJoystick    = mJoysticks.begin();
            itJoystickEnd = mJoysticks.end();
            for(; itJoystick != itJoystickEnd; ++itJoystick ) {
                mInputSystem->destroyInputObject( *itJoystick );
            }

            mJoysticks.clear();
        }

	mInputSystem->destroyInputSystem(mInputSystem);
        mInputSystem = 0;

        // Clear Listeners
        mKeyListeners.clear();
        mMouseListeners.clear();
        mJoystickListeners.clear();
    }
}

/** Initializes the InputManager with a Ogre render window
  *
  * \param renderWindow The associated render window
  *
  */
void RainbruRPG::Core::InputManager::
initialise( Ogre::RenderWindow *renderWindow ) {
  size_t windowHnd = 0;

  mMouse       = NULL;
  mKeyboard    = NULL;
  mInputSystem = NULL;


  if( !mInputSystem ) {
    // Setup basic variables
    OIS::ParamList paramList;    
    std::ostringstream windowHndStr;
    
    try{
      // Get window handle
      windowHnd=WindowHandle::get(renderWindow);
    }
    catch (NullWindowHandleException e){
      LOGE(e.what());
      exit(1);
    }

    // Fill parameter list
    windowHndStr << (unsigned int) windowHnd;
    paramList.insert(std::make_pair(std::string("WINDOW"), 
				    windowHndStr.str()));

    // Create inputsystem
    mInputSystem = OIS::InputManager::createInputSystem( paramList );

    // If possible create a buffered keyboard
    if( mInputSystem->numKeyBoards() > 0 ) {
      mKeyboard = static_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
      mKeyboard->setEventCallback( this );
    }

    // If possible create a buffered mouse
    if( mInputSystem->numMice() > 0 ) {
      mMouse = static_cast<OIS::Mouse*>( mInputSystem->createInputObject( OIS::OISMouse, true ) );
      mMouse->setEventCallback( this );
      
      // Get window size
      unsigned int width, height, depth;
      int left, top;
      renderWindow->getMetrics( width, height, depth, left, top );
      
      // Set mouse region
      this->setWindowExtents( width, height );
    }
    
    // If possible create all joysticks in buffered mode
    if( mInputSystem->numJoysticks() > 0 ) {
      mJoysticks.resize( mInputSystem->numJoysticks() );
      
      itJoystick    = mJoysticks.begin();
      itJoystickEnd = mJoysticks.end();
      for(; itJoystick != itJoystickEnd; ++itJoystick ) {
	(*itJoystick) = static_cast<OIS::JoyStick*>( mInputSystem->createInputObject( OIS::OISJoyStick, true ) );
	(*itJoystick)->setEventCallback( this );
      }
    }
  }
}

/** Captures the mouse, keyboard and joystick events
  *
  * This must be called every frame. So it is called from
  * \ref RainbruRPG::Core::GameEngine::frameStarted "GameEngine::frameStarted".
  *
  * \note v0.0.5-167 : Some LOGA() calls was added to assert on
  *       \ref RainbruRPG::Core::InputManager::mMouse "mMouse" and 
  *       \ref RainbruRPG::Core::InputManager::mKeyboard "mKeyboard"
  *       to avoid a SEGFAULT. Please see v0.0.5-167 changelog for
  *       complete trace output.
  *
  */
void RainbruRPG::Core::InputManager::capture( void ) {
    // Need to capture / update each device every frame
    if( mMouse ) {
      LOGA( mMouse, _("RainbruRPG::Core::InputManager::mMouse is NULL. "
		      "Program should crash."));
      mMouse->capture();
    }

    if( mKeyboard ) {
      LOGA( mKeyboard, _("RainbruRPG::Core::InputManager::mKeyboard is NULL. "
			 "Program should crash."));
      mKeyboard->capture();
    }

    if( mJoysticks.size() > 0 ) {
        itJoystick    = mJoysticks.begin();
        itJoystickEnd = mJoysticks.end();
        for(; itJoystick != itJoystickEnd; ++itJoystick ) {
            (*itJoystick)->capture();
        }
    }
}

/** Add a key listener
  *
  * \param keyListener The key listener to add
  * \param instanceName The name of the instance
  *
  */
void RainbruRPG::Core::InputManager::addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName ) {
    if( mKeyboard ) {
        // Check for duplicate items
        itKeyListener = mKeyListeners.find( instanceName );
        if( itKeyListener == mKeyListeners.end() ) {
            mKeyListeners[ instanceName ] = keyListener;
        }
        else {
            // Duplicate Item
        }
    }
}

/** Add a mouse listener
  *
  * \param mouseListener The mouse listener to add
  * \param instanceName The name of the instance
  *
  */
void RainbruRPG::Core::InputManager::addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName ) {

  LOGI(_("Adding a mouse listener"));

    if( mMouse ) {
        // Check for duplicate items
        itMouseListener = mMouseListeners.find( instanceName );
        if( itMouseListener == mMouseListeners.end() ) {
            mMouseListeners[ instanceName ] = mouseListener;
        }
        else {
            // Duplicate Item
        }
    }
}

/** Add a joystick listener
  *
  * \param joystickListener The mouse listener to add
  * \param instanceName The name of the instance
  *
  */
void RainbruRPG::Core::InputManager::addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName ) {
    if( mJoysticks.size() > 0 ) {
        // Check for duplicate items
        itJoystickListener = mJoystickListeners.find( instanceName );
        if( itJoystickListener == mJoystickListeners.end() ) {
            mJoystickListeners[ instanceName ] = joystickListener;
        }
        else {
            // Duplicate Item
        }
    }
}

/** Removes a key listener
  *
  * \param instanceName The name of the instance to remove
  *
  */
void RainbruRPG::Core::InputManager::removeKeyListener( const std::string& instanceName ) {
    // Check if item exists
    itKeyListener = mKeyListeners.find( instanceName );
    if( itKeyListener != mKeyListeners.end() ) {
        mKeyListeners.erase( itKeyListener );
    }
    else {
        // Doesn't Exist
    }
}

/** Removes a mouse listener
  *
  * \param instanceName The name of the instance to remove
  *
  */
void RainbruRPG::Core::InputManager::removeMouseListener( const std::string& instanceName ) {

  LOGI(_("Removing MouseListener"));
  // Check if item exists
  itMouseListener = mMouseListeners.find( instanceName );
  if( itMouseListener != mMouseListeners.end() ) {
    mMouseListeners.erase( itMouseListener );
  }
  else {
    // Doesn't Exist
    LOGW(_("MouseListener not found"));
  }
}

/** Removes a joystick listener
  *
  * \param instanceName The name of the instance to remove
  *
  */
void RainbruRPG::Core::InputManager::removeJoystickListener( const std::string& instanceName ) {
    // Check if item exists
    itJoystickListener = mJoystickListeners.find( instanceName );
    if( itJoystickListener != mJoystickListeners.end() ) {
        mJoystickListeners.erase( itJoystickListener );
    }
    else {
        // Doesn't Exist
    }
}

/** Removes a key listener
  *
  * \param keyListener The key listener to remove
  *
  */
void RainbruRPG::Core::InputManager::removeKeyListener( OIS::KeyListener *keyListener ) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if( itKeyListener->second == keyListener ) {
            mKeyListeners.erase( itKeyListener );
            break;
        }
    }
}

/** Removes a mouse listener
  *
  * \param mouseListener The mouse listener to remove
  *
  */
void RainbruRPG::Core::InputManager::removeMouseListener( OIS::MouseListener *mouseListener ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        if( itMouseListener->second == mouseListener ) {
            mMouseListeners.erase( itMouseListener );
            break;
        }
    }
}

/** Removes a joystick listener
  *
  * \param joystickListener The joystick listener to remove
  *
  */
void RainbruRPG::Core::InputManager::removeJoystickListener( OIS::JoyStickListener *joystickListener ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        if( itJoystickListener->second == joystickListener ) {
            mJoystickListeners.erase( itJoystickListener );
            break;
        }
    }
}

/** Removes all key, mouse and joystick listener
  *
  */
void RainbruRPG::Core::InputManager::removeAllListeners( void ) {
    mKeyListeners.clear();
    mMouseListeners.clear();
    mJoystickListeners.clear();
}

/** Remove all key listener
  *
  */
void RainbruRPG::Core::InputManager::removeAllKeyListeners( void ) {
    mKeyListeners.clear();
}

/** Remove all mouse listener
  *
  */
void RainbruRPG::Core::InputManager::removeAllMouseListeners( void ) {
    mMouseListeners.clear();
}

/** Remove all joystick listener
  *
  */
void RainbruRPG::Core::InputManager::removeAllJoystickListeners( void ) {
    mJoystickListeners.clear();
}

/** Sets the mouse region
  *
  * \param width The width of the window
  * \param height The height of the window
  *
  */
void RainbruRPG::Core::InputManager::setWindowExtents( int width, int height ) {
  // Set mouse region (if window resizes, we should alter this to 
  // reflect as well)
  const OIS::MouseState &mouseState = mMouse->getMouseState();
  mouseState.width  = width;
  mouseState.height = height;
}

/** Get the mouse
  *
  * \return The mouse
  *
  */
OIS::Mouse* RainbruRPG::Core::InputManager::getMouse( void ) {
    return mMouse;
}

/** Get the keyboard
  *
  * \return The keyboard
  *
  */
OIS::Keyboard* RainbruRPG::Core::InputManager::getKeyboard( void ) {
    return mKeyboard;
}

/** Get the joystick
  *
  * \param index The joystick index
  *
  * \return The joystick
  *
  */
OIS::JoyStick* RainbruRPG::Core::InputManager::getJoystick( unsigned int index ) {
    // Make sure it's a valid index
    if( index < mJoysticks.size() ) {
        return mJoysticks[ index ];
    }

    return 0;
}

/** Get the number of joystick
  *
  * \return The number of joystick
  *
  */
int RainbruRPG::Core::InputManager::getNumOfJoysticks( void ) {
    // Cast to keep compiler happy ^^
    return (int) mJoysticks.size();
}

/** The key pressed callback
  *
  * \param e The event
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::keyPressed( const OIS::KeyEvent &e ) {
  LOGI(_("InputManager::keyPressed called"));

  itKeyListener    = mKeyListeners.begin();
  itKeyListenerEnd = mKeyListeners.end();

  for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
    itKeyListener->second->keyPressed( e );
  }
  
  return true;
}

/** The key released callback
  *
  * \param e The event
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::keyReleased( const OIS::KeyEvent &e ) {
  itKeyListener    = mKeyListeners.begin();
  itKeyListenerEnd = mKeyListeners.end();
  for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
    itKeyListener->second->keyReleased( e );
  }
  
  return true;
}

/** The mouse moved callback
  *
  * \param e The event
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::mouseMoved( const OIS::MouseEvent &e ) {
  itMouseListener    = mMouseListeners.begin();
  itMouseListenerEnd = mMouseListeners.end();

  for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
    itMouseListener->second->mouseMoved( e );
  }

  return true;
}

/** The mouse pressed callback
  *
  * \param e The event
  * \param id The button identifier
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::
mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
  itMouseListener    = mMouseListeners.begin();
  itMouseListenerEnd = mMouseListeners.end();
  for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
    itMouseListener->second->mousePressed( e, id );
  }
  
  return true;
}

/** The mouse released callback
  *
  * \param e The event
  * \param id The mouse button
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
        itMouseListener->second->mouseReleased( e, id );
    }

    return true;
}

/** The joystick pov callback
  *
  * \param e The event
  * \param pov The pov
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::povMoved( const OIS::JoyStickEvent &e, int pov ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        itJoystickListener->second->povMoved( e, pov );
    }

    return true;
}

/** The joystick axis callback
  *
  * \param e The event
  * \param axis The pov
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::axisMoved( const OIS::JoyStickEvent &e, int axis ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        itJoystickListener->second->axisMoved( e, axis );
    }

    return true;
}

/** The joystick slider callback
  *
  * \param e The event
  * \param sliderID The slider identifier
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        itJoystickListener->second->sliderMoved( e, sliderID );
    }

    return true;
}

/** The joystick bouton pressed callback
  *
  * \param e The event
  * \param button The button pressed
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        itJoystickListener->second->buttonPressed( e, button );
    }

    return true;
}

/** The joystick bouton released callback
  *
  * \param e The event
  * \param button The button
  *
  * \return Always true
  *
  */
bool RainbruRPG::Core::InputManager::
buttonReleased( const OIS::JoyStickEvent &e, int button ) {

    itJoystickListener    = mJoystickListeners.begin();
    itJoystickListenerEnd = mJoystickListeners.end();
    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
        itJoystickListener->second->buttonReleased( e, button );
    }

    return true;
}

/** Get the instance pointer
  *
  * \return A pointer to this instance
  *
  */
RainbruRPG::Core::InputManager* RainbruRPG::Core::InputManager::
getSingletonPtr( void ) {

    if( !mInputManager ) {
        mInputManager = new InputManager();
    }

    return mInputManager;
}
