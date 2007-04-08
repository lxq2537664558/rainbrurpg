#include "inputwrapper.h"

/** The default constructor
  *
  */
RainbruRPG::Core::InputWrapper::InputWrapper(){
  mouseMenuSensibility=1.0f;

  // standard keys definition
  forward = OIS::KC_Z;
  backward= OIS::KC_S;
  left    = OIS::KC_Q;
  right   = OIS::KC_D;
}

/** The default destructor
  *
  */
RainbruRPG::Core::InputWrapper::~InputWrapper(){

}

/** Convert a mouse button from OIS to CEGUI
  *
  * \param id The OIS mouse button value
  *
  * \return The CEGUI button
  *
  */ 
CEGUI::MouseButton RainbruRPG::Core::InputWrapper::
OISButtontoCEGUI(OIS::MouseButtonID id){

  switch (id){
  case OIS::MB_Left:
    return CEGUI::LeftButton;
  case OIS::MB_Right:
    return CEGUI::RightButton;
  case OIS::MB_Middle:
    return CEGUI::MiddleButton;
  }

}

/** Get the mouse move sensibility used in menus
  *
  * \return The mouse sensibility factor
  *
  */
float RainbruRPG::Core::InputWrapper::getMouseMenuSensibility(){
  return mouseMenuSensibility;
}

/** Get the forward keycode
  *
  * \return The keycode for moving forward
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getForward(){
  return forward;
}

/** Get the backward keycode
  *
  * \return The keycode for moving backward
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getBackward(){
  return backward;
}

/** Get the left keycode
  *
  * \return The keycode for moving left
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getLeft(){
  return left;
}

/** Get the right keycode
  *
  * \return The keycode for moving right
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getRight(){
  return right;
}
