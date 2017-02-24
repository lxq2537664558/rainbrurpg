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

#include "ConfirmationDialog.hpp"

#include <CEGUI/CEGUI.h> // Uses CEGUI::PushButton

ConfirmationDialog::ConfirmationDialog(const string& title,
				       const string& message,
				       const string& uniqueName):
  ModalDialog("modal_dialog.layout", title, message, uniqueName)
{
  // Dialog creation is in ModalDialog::ModalDialog()
  CEGUI::PushButton* btnOk = (CEGUI::PushButton *)mDialogWindow->
    getChild("nyiRoot/winToolbar/btnOk");
  btnOk->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ConfirmationDialog::onOk, this));

  CEGUI::PushButton* btnCancel = (CEGUI::PushButton *)mDialogWindow->
    getChild("nyiRoot/winToolbar/btnCancel");
  btnCancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ConfirmationDialog::onCancel, this));
}

ConfirmationDialog::~ConfirmationDialog()
{

}

bool
ConfirmationDialog::onOk(const CEGUI::EventArgs&)
{
  return closeDialog(true);
}

bool
ConfirmationDialog::onCancel(const CEGUI::EventArgs&)
{
  return closeDialog(false);
}
