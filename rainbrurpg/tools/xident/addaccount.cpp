/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "addaccount.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::AddAccount) AddAccountMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::AddAccount::ID_NYI, RainbruRPG::Gui::AddAccount::onNotYetImplemented),

};

FXIMPLEMENT(RainbruRPG::Gui::AddAccount,FXDialogBox,AddAccountMap,ARRAYNUMBER(AddAccountMap));

/** The constructor
  *
  * \param a The base FOX application
  *
  */
RainbruRPG::Gui::AddAccount::AddAccount(FXApp *a)
  :FXDialogBox{


}

/** Destructor
  *
  */
RainbruRPG::Gui::AddAccount::~AddAccount(){

}

/** The FOX-Toolkit create method
  *
  * It creates and execute a FoxAccountList instance.
  *
  */
void RainbruRPG::Gui::AddAccount::create(){
  FXPacker::create();
  this->show();
}

/** The NotYetImplemented callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::AddAccount::
onNotYetImplemented(FXObject* o,FXSelector s,void* v){
  return 1;
}
