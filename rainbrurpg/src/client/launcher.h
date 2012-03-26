/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file client/launcher.h
  *
  * The declaration file of the class \ref RainbruRPG::Gui::Launcher "Launcher"
  *
  * Modifications :
  * - 16 jul 2008 : Documentation of header file
  *
  * \note This file must be included before libfox one. It is due to
  *       a double definition of PI, in \c fxdefs.h and \c OgreMath.h.
  *
  */
#include <fox-1.6/fx.h>

#include <XmlOptions.hpp>
/** To avoid multiple definitions of the PI macro
  * we must undef it because FOX and OGRE define it 
  */
#undef PI
#include <OgreImport.hpp>

using namespace RainbruRPG::Options;

namespace RainbruRPG{
  namespace Gui{

    /** The launcher mainWindow
      *
      * Loads a launcher window with a TGA image.
      *
      * The image must be in TGA format (a FOX native image
      * format) because the PNG format is hardly usable in Win32.
      *
      * When Quit or Play buttons are clicked, the FXApp is stopped.
      * We make the difference beetween Quitting and Playing with the
      * FXApp::quit() or FXApp::stop(). FXApp::run() will returned 0 in the
      * first case (we quit the game) and the Play button will call 
      * FXApp::stop(999). FXApp::run() returns 999 and main.cpp knows it
      * may run the game.
      *
      * To prevent SEGFAULT, an error message box may appears at startup.
      * it is shown if criticalError is \c true. the criticalMsg string
      * contains the error message.
      *
      */
    class Launcher : public FX::FXMainWindow {
      FXDECLARE(Launcher)
	
	public:
      Launcher(FXApp *); 
      virtual ~Launcher(); 

      virtual void create();
      long onPlayButtonPressed(FXObject *,FXSelector,void*);
      long onOptionsButtonPressed(FXObject *,FXSelector,void*);
      long onQuitButtonPressed(FXObject *,FXSelector,void*);
      long onRenderComboPressed(FXObject *,FXSelector,void*);
      long onRenderComboDoubleClick(FXObject *,FXSelector,void*);
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** The identifier of the default unimplemented button */
	ID_BUTTON=FXMainWindow::ID_LAST,       
	/** The play button identifier */
	ID_BTN_PLAY=FXMainWindow::ID_LAST+1,
	/** The options button identifier */
	ID_BTN_OPTS=FXMainWindow::ID_LAST+2,
	/** The quit button identifier */
	ID_BTN_QUIT=FXMainWindow::ID_LAST+3,
        /** The renerer combobox identifier */
	ID_RENDERER=FXMainWindow::ID_LAST+4,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
      
    private:
      /** Required or Undefined references */
      Launcher(){};
      /** Required or Undefined references */
      Launcher(const Launcher&);
      /** Required or Undefined references */
      Launcher &operator=(const Launcher&);
      /// The snapshot combobox
      FXComboBox *cbQuality;

      void createSnapCombo(FXComposite*);
      void createRenderCombo(    FXComposite*);  

      FX::FXImage* loadImage(const char*);

      /** The renderers combobox */
      FX::FXList* lbRend;
 
      /** Is A critical error occurs
        *
	* A dialog is shown if this is \c true.
	*
	*/
      bool criticalError;
      /** The critical error message
        * 
	* This message is shown in a error dialog at startup if
	* criticalError is \c true.
	*
	*/
      const char* criticalMsg;

    protected:
      /** A test for the application icon */
      FXIcon * wm_icon_small;
      /** A test for the application icon */
      FXIcon * wm_icon_big;
      
    }; 
  }
}




