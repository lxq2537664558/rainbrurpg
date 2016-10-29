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

  hide();

  CEGUI::PushButton* btnNetPl = (CEGUI::PushButton *)mDialogWindow->
    getChild("winToolbar/btnOk");
  btnNetPl->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CeguiDialog::onOk, this));
}

CeguiDialog::~CeguiDialog()
{
  mDialogWindow = NULL; // How to really destroy it ?
  mRootWindow   = NULL;
  mWmgr         = NULL;
}


void
CeguiDialog::hide()
{
  //  mDialogWindow->setVisible(false);
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
