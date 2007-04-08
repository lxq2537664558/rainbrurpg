#include "inputmanager.h"

InputManager *InputManager::mInputManager;

/** The default constructor
  *
  */
InputManager::InputManager( void ) :
    mMouse( 0 ),
    mKeyboard( 0 ),
    mInputSystem( 0 ) {
}

/** The default destructor
  *
  */
InputManager::~InputManager( void ) {
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
void InputManager::initialise( Ogre::RenderWindow *renderWindow ) {
    if( !mInputSystem ) {
        // Setup basic variables
        OIS::ParamList paramList;    
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;

        // Get window handle
#if defined OIS_WIN32_PLATFORM
        renderWindow->getCustomAttribute( "HWND", &windowHnd );
        // Uncomment these two lines to allow users to switch keyboards via the language bar
        //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND") ));
        //paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE") ));

#elif defined OIS_LINUX_PLATFORM
        renderWindow->getCustomAttribute( "GLXWINDOW", &windowHnd );
#endif

        // Fill parameter list
        windowHndStr << (unsigned int) windowHnd;
        paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );

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
  * This must be called every frame
  *
  */
void InputManager::capture( void ) {
    // Need to capture / update each device every frame
    if( mMouse ) {
        mMouse->capture();
    }

    if( mKeyboard ) {
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
void InputManager::addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName ) {
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
void InputManager::addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName ) {
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
void InputManager::addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName ) {
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
void InputManager::removeKeyListener( const std::string& instanceName ) {
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
void InputManager::removeMouseListener( const std::string& instanceName ) {
    // Check if item exists
    itMouseListener = mMouseListeners.find( instanceName );
    if( itMouseListener != mMouseListeners.end() ) {
        mMouseListeners.erase( itMouseListener );
    }
    else {
        // Doesn't Exist
    }
}

/** Removes a joystick listener
  *
  * \param instanceName The name of the instance to remove
  *
  */
void InputManager::removeJoystickListener( const std::string& instanceName ) {
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
void InputManager::removeKeyListener( OIS::KeyListener *keyListener ) {
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
void InputManager::removeMouseListener( OIS::MouseListener *mouseListener ) {
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
void InputManager::removeJoystickListener( OIS::JoyStickListener *joystickListener ) {
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
void InputManager::removeAllListeners( void ) {
    mKeyListeners.clear();
    mMouseListeners.clear();
    mJoystickListeners.clear();
}

/** Remove all key listener
  *
  */
void InputManager::removeAllKeyListeners( void ) {
    mKeyListeners.clear();
}

/** Remove all mouse listener
  *
  */
void InputManager::removeAllMouseListeners( void ) {
    mMouseListeners.clear();
}

/** Remove all joystick listener
  *
  */
void InputManager::removeAllJoystickListeners( void ) {
    mJoystickListeners.clear();
}

/** Sets the mouse region
  *
  * \param width The width of the window
  * \param height The height of the window
  *
  */
void InputManager::setWindowExtents( int width, int height ) {
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
OIS::Mouse* InputManager::getMouse( void ) {
    return mMouse;
}

/** Get the keyboard
  *
  * \return The keyboard
  *
  */
OIS::Keyboard* InputManager::getKeyboard( void ) {
    return mKeyboard;
}

/** Get the joystick
  *
  * \param index The joystick index
  *
  * \return The joystick
  *
  */
OIS::JoyStick* InputManager::getJoystick( unsigned int index ) {
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
int InputManager::getNumOfJoysticks( void ) {
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
bool InputManager::keyPressed( const OIS::KeyEvent &e ) {
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
bool InputManager::keyReleased( const OIS::KeyEvent &e ) {
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
bool InputManager::mouseMoved( const OIS::MouseEvent &e ) {
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
bool InputManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
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
bool InputManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
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
bool InputManager::povMoved( const OIS::JoyStickEvent &e, int pov ) {
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
bool InputManager::axisMoved( const OIS::JoyStickEvent &e, int axis ) {
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
  * \param sliderID The pov
  *
  * \return Always true
  *
  */
bool InputManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
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
bool InputManager::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
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
bool InputManager::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
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
InputManager* InputManager::getSingletonPtr( void ) {
    if( !mInputManager ) {
        mInputManager = new InputManager();
    }

    return mInputManager;
}
