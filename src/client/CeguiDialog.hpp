/*
 * Copyright 2011-2016 Jerome Pasquier
 *
 * This file is part of rainbrurpg-client.
 *
 * rainbrurpg-client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rainbrurpg-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rainbrurpg-client.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _CEGUI_DIALOG_HPP_
#define _CEGUI_DIALOG_HPP_

#include <string>
#include <CEGUI/EventArgs.h>  // Used as a reference

using namespace std;

// Forward declarations
namespace CEGUI
{
  class Window;
  class WindowManager;
}
// End of forward declarations

/* A really simple super-class for all CEGUI-related dialogs
 *
 * If you plan to use it multiple times in a single game state, do not create
 * and destroy it. The Ok button only hides the dialog. You just
 * have to create it once and show() it after that :
 *
 * constructor:
 *   CeguiDialog* mydialog = NULL;
 *
 * onShow:
 *   if (!mydialog);
 *     mydialog = new CeguiDialog("mylayout");
 *
 *   mydialog->show();
 *
 */
class CeguiDialog
{
public:
  CeguiDialog(const string&, const string&);
  virtual ~CeguiDialog();

  void hide();
  void show();
  bool isVisible();
  void setVisible(bool);

  CEGUI::Window* getDialog();
  
protected:
  bool onOk(const CEGUI::EventArgs&);
  
  CEGUI::Window* mRootWindow;   // The default GUI context' root window
  /** The window that will contain our dialog
    *
    * This is the fullscreen transparent window that will contains the dialog.
    * Use it if you need to call getChild().
    * 
    * Note: If this window is visible, no event will work on other controls.
    */
  CEGUI::Window* mDialogWindow;
  /** The real dialog
    *
    * This is the visible falagard-styled window. Use it with StateSaver
    * to save/restore state.
    */
  CEGUI::Window* mDialog; 
  CEGUI::WindowManager* mWmgr;  // the CEGUI windowManager

private:
  string mLayoutName;           // The layout file to be loaded
  string mUniqueName;
};

#endif // !_CEGUI_DIALOG_HPP_
