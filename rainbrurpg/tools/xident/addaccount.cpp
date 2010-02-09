/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file tools/xident/addaccount.cpp
  * Implements a dialog used to add an account
  *
  */

#include "addaccount.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::AddAccount "AddAccount" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::AddAccount) AddAccountMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::AddAccount::ID_NYI, RainbruRPG::Gui::AddAccount::onNotYetImplemented),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::AddAccount "AddAccount" class
  * uses the AddAccountMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::AddAccount,FXDialogBox,AddAccountMap,ARRAYNUMBER(AddAccountMap));

/** The constructor
  *
  */
RainbruRPG::Gui::AddAccount::AddAccount()
  :FXDialogBox(){


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
  FXDialogBox::create();
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
