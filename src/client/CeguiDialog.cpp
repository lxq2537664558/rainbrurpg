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

#include "CeguiDialog.hpp"

#include <CEGUI/System.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>

/* Named constructor
 *
 * Create a dialog based on a CEGUI XML-based layout file.
 *
 * \param layoutName the xml layout filename.
 *
 */
CeguiDialog::CeguiDialog(const string& layoutName):
  mLayoutName(layoutName),
  mRootWindow(NULL),
  mDialogWindow(NULL),
  mWmgr(NULL)
{
  mWmgr = CEGUI::WindowManager::getSingletonPtr();
  mRootWindow = CEGUI::System::getSingleton().getDefaultGUIContext().
    getRootWindow();

  mDialogWindow = mWmgr->loadLayoutFromFile(mLayoutName);
  mRootWindow->addChild(mDialogWindow);
  mDialogWindow->moveToFront();
}

CeguiDialog::~CeguiDialog()
{
  mDialogWindow = NULL;
  mRootWindow   = NULL;
  mWmgr         = NULL;
}
