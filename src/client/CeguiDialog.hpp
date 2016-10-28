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
 */
class CeguiDialog
{
public:
  CeguiDialog(const string&);
  virtual ~CeguiDialog();

private:
  string mLayoutName;           // The layout file to be loaded
  CEGUI::Window* mRootWindow;   // The default GUI context' root window
  CEGUI::Window* mDialogWindow; // The default that will contain our dialog
  CEGUI::WindowManager* mWmgr;  // the CEGUI windowManager
};

#endif // !_CEGUI_DIALOG_HPP_
