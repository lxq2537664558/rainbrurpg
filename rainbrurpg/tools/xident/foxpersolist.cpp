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

#include "foxpersolist.h"

#include "logger.h"

#include <fox-1.6/FXMessageBox.h>

FXDEFMAP(RainbruRPG::Gui::FoxPersoList) FoxPersoListMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxPersoList::ID_NYI, RainbruRPG::Gui::FoxPersoList::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxPersoList::ID_ACCOUNT, RainbruRPG::Gui::FoxPersoList::onAccountSelected),

};

FXIMPLEMENT(RainbruRPG::Gui::FoxPersoList,FXPacker,FoxPersoListMap,ARRAYNUMBER(FoxPersoListMap));


/** The constructor
  *
  * The parent must not be NULL
  *
  * \param parent The parent composite
  * \param opts The FOX construction parameter
  *
  */
RainbruRPG::Gui::FoxPersoList::FoxPersoList(FXComposite *parent,FXuint opts)
  :FX::FXPacker(parent, opts) {

  FXint listOpt=LAYOUT_FILL_X|LAYOUT_FILL_Y|LIST_SINGLESELECT;
  xmlPerso=new xmlPersoList();;


  // The root layout and the help text
  FXVerticalFrame *root = new FXVerticalFrame(this,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXString lab="This screen provides the perso management. Please choose  "
    "an account and the perso list will be fed.";
  FXLabel* labHelp=new FXLabel(root, lab);
  FXHorizontalFrame *hframe = new FXHorizontalFrame(root,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // Frame containing the account list
  FXVerticalFrame *listFrame = new FXVerticalFrame(hframe,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXLabel* labAdminName=new FXLabel(listFrame, "Accounts");
  accountList=new FXList(listFrame, this, ID_ACCOUNT, listOpt);

  // Frame containing the persos list
  FXVerticalFrame *listFrame2 = new FXVerticalFrame(hframe,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXLabel* labPersos=new FXLabel(listFrame2, "Persos");
  persoList=new FXList(listFrame2, this, ID_NYI, listOpt);

  // Feed the account list
  feedAccountList();
}

/** The destructor
  *
  */
RainbruRPG::Gui::FoxPersoList::~FoxPersoList(){
  delete accountList;
  delete persoList;

  delete xmlPerso;
}

/** The FOX-Toolkit create method
  *
  * It creates and execute a FoxServerList instance.
  *
  */
void RainbruRPG::Gui::FoxPersoList::create(){
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
long RainbruRPG::Gui::FoxPersoList::
onNotYetImplemented(FXObject* o,FXSelector s,void* v){

}

/** Feed the account list
  *
  */
void RainbruRPG::Gui::FoxPersoList::feedAccountList(void){
  tPersoList* pl=xmlPerso->getPersoList();
  LOGCATS("FoxPersoList size=");
  LOGCATI(pl->size());
  LOGCAT();


  tPersoList::const_iterator iter;
  for (iter=pl->begin(); iter != pl->end(); iter++){
    accountList->appendItem((*iter)->name);
  }
}

/** The account callback
  *
  * When an account is clicked, we show its perso in perso list.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v The index of the clicked item (need a cast to int)
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxPersoList::
onAccountSelected(FXObject* o,FXSelector s,void* v){
  LOGI("onAccountSelected called");

  FXint itemIndex=(int)v;
  FXString itemText=accountList->getItemText(itemIndex);
  std::string strItemText(itemText.text());
  LOGCATS("Item index : ");
  LOGCATI(itemIndex);
  LOGCATS(" item text : ");
  LOGCATS(strItemText.c_str());
  LOGCAT();

  // Get the perso list of the given account
  tPersoListItem* pli=xmlPerso->getAccountByName(strItemText);
  if (pli==NULL){
    LOGW("Cannot get the tPersoListItem");
  }
  else{
    LOGCATS("Perso number for account ");
    LOGCATS(strItemText.c_str());
    LOGCATS(" : ");
    LOGCATI(pli->persoList.size());
    LOGCAT();

    persoList->clearItems();

    tPersoSubList::const_iterator iter;
    for (iter=pli->persoList.begin(); iter != pli->persoList.end(); iter++){
      persoList->appendItem((*iter)->persoId);
    }

  }
}

