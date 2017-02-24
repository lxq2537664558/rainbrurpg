/*
 * Copyright 2011-2017 Jerome Pasquier
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

#include "ModalDialog.hpp"

#include <iostream>

#include <Ogre.h>
#include <CEGUI/CEGUI.h>

#include <OgreWindowEventUtilities.h> // Uses MEU::messagePump()


#include "GameEngine.hpp"

/* Named constructor
 *
 * Create a modal dialog.
 *
 * \param message    The in-dialog message.
 * \param uniqueName a context name that is unique to avoid a 
 *          CEGUI::AlreadyExistsException
 *
 */
ModalDialog::ModalDialog(const string& title,const string& message,
			 const string& uniqueName):
  CeguiDialog("modal_dialog.layout", uniqueName),
  waiting(false),
  returnValue(false)

{
  CEGUI::Window* mT = static_cast<CEGUI::Window*>
    (mDialogWindow->getChild("nyiRoot/winToolbar"));
  mT->setProperty("Text", title);

  CEGUI::Window* mM = static_cast<CEGUI::Window*>
    (mDialogWindow->getChild("nyiRoot/winToolbar/static_Text"));
  mM->setProperty("Text", message);

  CEGUI::PushButton* btnOk = (CEGUI::PushButton *)mDialogWindow->
    getChild("nyiRoot/winToolbar/btnOk");
  btnOk->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ModalDialog::onOk, this));

  CEGUI::PushButton* btnCancel = (CEGUI::PushButton *)mDialogWindow->
    getChild("nyiRoot/winToolbar/btnCancel");
  btnCancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ModalDialog::onCancel, this));

}

ModalDialog::~ModalDialog()
{

}

/*
void
ModalDialog::hide()
{
  mDialogWindow->hide();
  mDialog->hide();
}
*/

bool
ModalDialog::exec(GameEngine* ge)
{
  cout << "Entering ModalDialog::exec" << endl;
  waiting = true;
  show();

  /* FIXME: I can't draw CEGUI's GeometryBuffer here.
   */
  while (waiting)
    {
      CEGUI::System::getSingleton().getDefaultGUIContext()
	.clearGeometry(CEGUI::RQ_OVERLAY);
      Ogre::WindowEventUtilities::messagePump();
      Ogre::Root::getSingleton().renderOneFrame();
      ge->drawOverlays();

    }
  return returnValue;
}

bool
ModalDialog::closeDialog(bool value)
{
  returnValue = value;
  waiting = false;
  hide();
  return true;
}

bool
ModalDialog::onOk(const CEGUI::EventArgs&)
{
  return closeDialog(true);
}

bool
ModalDialog::onCancel(const CEGUI::EventArgs&)
{
  return closeDialog(false);
}
