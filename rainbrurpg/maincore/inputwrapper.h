#ifndef INPUT_WRAPPER_H
#define INPUT_WRAPPER_H

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISPrereqs.h>
#include <CEGUI/CEGUIInputEvent.h>

namespace RainbruRPG{
  namespace Core{

    /** Defines some mouse and keyboard wrapping
      *
      * It defines the mouse sensibility and some keyboard keys.
      *
      *
      */
    class InputWrapper{
    public:
      InputWrapper();
      ~InputWrapper();

      CEGUI::MouseButton OISButtontoCEGUI(OIS::MouseButtonID);

      float getMouseMenuSensibility();
      OIS::KeyCode getForward();
      OIS::KeyCode getBackward();
      OIS::KeyCode getLeft();
      OIS::KeyCode getRight();

    private:
      /** The ratio for mouse events when their are injected to CEGUI */
      float mouseMenuSensibility;
      /** The sensibility of the camera */
      float mouseCameraSensibility;
      /** The keycode for moving forward */
      OIS::KeyCode forward;
      /** The keycode for moving backward */
      OIS::KeyCode backward;
      /** The keycode for moving left */
      OIS::KeyCode left;
      /** The keycode for moving right */
      OIS::KeyCode right;
    };
  }
}

#endif// INPUT_WRAPPER_H
