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

#include "Logger.hpp"

#include <CEGUI/System.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>

static Rpg::Logger static_logger("engine", Rpg::LT_BOTH);

/* Named constructor
 *
 * Create a dialog based on a CEGUI XML-based layout file.
 *
 * \param layoutName the xml layout filename.
 * \param uniqueName a context name that is unique to avoid a 
 *          CEGUI::AlreadyExistsException
 *
 */
CeguiDialog::CeguiDialog(const string& layoutName, const string& uniqueName):
  mLayoutName(layoutName),
  mUniqueName(uniqueName),
  mRootWindow(NULL),
  mDialogWindow(NULL),
  mWmgr(NULL)
{
  mWmgr = CEGUI::WindowManager::getSingletonPtr();

  // Create the parent window using unique name, makes it fullsize
  // and transparent
  mDialogWindow=mWmgr->createWindow("Vanilla/StaticImage", uniqueName);
  mDialogWindow->setProperty("Size", "{{1,0},{1,0}}");
  mDialogWindow->setProperty("FrameEnabled", "False");
  mDialogWindow->setProperty("BackgroundEnabled", "False");
  
  // Load the given layout file
  CEGUI::Window* layoutWindow = mWmgr->loadLayoutFromFile(mLayoutName);

  mRootWindow = CEGUI::System::getSingleton().getDefaultGUIContext().
    getRootWindow();
  mRootWindow->addChild(mDialogWindow);
  mDialogWindow->addChild(layoutWindow);

  hide();

  CEGUI::PushButton* btnNetPl = (CEGUI::PushButton *)mDialogWindow->
    getChild("nyiRoot/winToolbar/btnOk");
  btnNetPl->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CeguiDialog::onOk, this));
}

CeguiDialog::~CeguiDialog()
{
  mWmgr->destroyWindow(mDialogWindow);
  mRootWindow   = NULL;
  mWmgr         = NULL;
}


void
CeguiDialog::hide()
{
  mDialogWindow->hide();
}

void
CeguiDialog::show()
{
  mDialogWindow->setVisible(true);
  mDialogWindow->activate();
}

bool
CeguiDialog::isVisible()
{
  return mDialogWindow->isVisible();
}

bool
CeguiDialog::onOk(const CEGUI::EventArgs&)
{
  hide();
  return true;
}
