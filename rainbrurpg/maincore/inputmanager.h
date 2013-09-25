#ifndef InputManager_H
#define InputManager_H

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISJoyStick.h>
#include <OIS/OISInputManager.h>

#include <OGRE/OgreRenderWindow.h>

/** An input manager for OIS to be used with Ogre3D
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
#endif
