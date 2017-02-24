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

#ifndef _CONFIRMATION_DIALOG_HPP_
#define _CONFIRMATION_DIALOG_HPP_

#include <CEGUI/EventArgs.h>  // Used as a reference

#include "ModalDialog.hpp"

/** A modal dialog with Ok/Cancel buttons
  *
  */
class ConfirmationDialog : public ModalDialog
{
public:
  ConfirmationDialog(const string&, const string&, const string&);
  ~ConfirmationDialog();

protected:
  bool onOk(const CEGUI::EventArgs&);
  bool onCancel(const CEGUI::EventArgs&);
};

#endif // !_CONFIRMATION_DIALOG_HPP_

