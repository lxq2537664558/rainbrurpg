/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file tools/xident/foxaccountlist.cpp
  * Implements the XIdent account list
  *
  */

#include "foxaccountlist.h"

#include <xmlaccountlist.h>
#include <taccountlist.h>
#include <logger.h>

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::FoxAccountList "FoxAccountList" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::FoxAccountList) FoxAccountListMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxAccountList::ID_NYI, RainbruRPG::Gui::FoxAccountList::onNotYetImplemented),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FoxAccountList::ID_BTN_ADD, RainbruRPG::Gui::FoxAccountList::onAddAccountClicked),

  FXMAPFUNC(SEL_SELECTED, RainbruRPG::Gui::FoxAccountList::ID_TABLE_SEL, RainbruRPG::Gui::FoxAccountList::onTableSelectionChange),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::FoxAccountList "FoxAccountList" class
  * uses the FoxAccountListMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::FoxAccountList,FXPacker,FoxAccountListMap,ARRAYNUMBER(FoxAccountListMap));

/** The constructor
  *
  * The parent must not be NULL
  *
  * \param parent The parent composite
  * \param opts The FOX construction parameter
  *
  */
RainbruRPG::Gui::FoxAccountList::
FoxAccountList(FXComposite *parent,FXuint opts):
  FXPacker(parent, opts),
  mSelectedAccountName("")
{


  accountList=new xmlAccountList();

  FXVerticalFrame *root = new FXVerticalFrame(this,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXString lab="This screen provides the account management. From the list "
    "of account below, you can chose one and edit it.";
  FXLabel* labAdminName=new FXLabel(root, lab);

 // frame containing admin info and button
  FXHorizontalFrame *hframe = new FXHorizontalFrame(root,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);


  FXVerticalFrame *frame = new FXVerticalFrame(hframe,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXuint table_opts = LAYOUT_FILL_X|LAYOUT_FILL_Y|TABLE_READONLY
    |TABLE_NO_COLSELECT;

  table=new FXTable(frame, this, ID_TABLE_SEL, table_opts);
  table->insertColumns(0, 5);
  table->getColumnHeader()->setItemText(0, "Name");
  table->getColumnHeader()->setItemText(1, "Mail");
  table->getColumnHeader()->setItemText(2, "Blacklist");
  table->getColumnHeader()->setItemText(3, "Creation");
  table->getColumnHeader()->setItemText(4, "Confirmation");
  table->getRowHeader()->setWidth(40);

  // Accountlist count label
  labPlCount=new FXLabel(frame, "Total accounts : <not set>");

  // Buttons in the right
  FXVerticalFrame *btnFrame = new FXVerticalFrame(hframe);
  FXuint btnOpts= LAYOUT_FILL_X|BUTTON_NORMAL;
  FXButton* btn1=new FXButton( btnFrame, "Add", NULL,this,ID_BTN_ADD, btnOpts);
  FXButton* btn2=new FXButton( btnFrame, "Delete",NULL,this,ID_NYI, btnOpts);
  FXButton* btn3=new FXButton( btnFrame, "Toggle blacklist", NULL,this,ID_NYI, 
			       btnOpts);
  FXButton* btn4=new FXButton( btnFrame, "Change password", NULL,this,ID_NYI, 
			       btnOpts);
  FXButton* btn5=new FXButton( btnFrame, "Edit", NULL,this,ID_NYI, btnOpts);

  // Initialize the panel
  this->feedTable();

}

/** The destructor
 *
 */
RainbruRPG::Gui::FoxAccountList::~FoxAccountList(){
  delete accountList;
  accountList=NULL;
}

/** The FOX-Toolkit create method
  *
  * It creates and execute a FoxAccountList instance.
  *
  */
void RainbruRPG::Gui::FoxAccountList::create(){
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
long RainbruRPG::Gui::FoxAccountList::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
}

/** The method feeding the account table
  *
  * It uses the tAccountList retrived from xmlAccountList accountList.
  *
  */
void RainbruRPG::Gui::FoxAccountList::feedTable(){
  LOGI("Starting feedTable");
  tAccountList* pl=accountList->getAccountList();
  if (pl){
    setAccountNumber(pl->size());

    // Feeding ^^
    tAccountList::const_iterator iter;
    for (iter=pl->begin(); iter != pl->end(); iter++){
      this->addAccount((*iter));
    }

    pl=NULL;
    LOGI("feedTable complete");
  }
  else{
    LOGE("Cannot get a valid account list");
  }
}

/** Change the number of account printed
  *
  * i.e. change the labPlCount content.
  *
  * \param i The new value
  *
  */
void RainbruRPG::Gui::FoxAccountList::setAccountNumber(unsigned int i){
  std::ostringstream temp ;
  temp << "Total accounts : ";
  temp << i;

  labPlCount->setText(temp.str().c_str());
}

/** Adds the informations of the given player into the table
  *
  * \param p The player to add
  *
  */
void RainbruRPG::Gui::FoxAccountList::
addAccount(RainbruRPG::Gui::tAccountListItem* p){
  FXString s;

  FXint num=table->getNumRows();
  // Adds a new row at the end of the table
  table->insertRows(num, 1);

  std::ostringstream temp ;
  temp << num+1;

  // Set the row header
  table->getRowHeader()->setItemText(num, temp.str().c_str());
  table->getRowHeader()->setItemJustify(num, FXHeaderItem::RIGHT);

  // Sets the name
  FXTableItem* item=new FXTableItem(p->name);
  table->setItem(num, 0, item);

  // Sets the mail
  FXTableItem* item2=new FXTableItem(p->mail);
  table->setItem(num, 1, item2);

  // Sets the blacklist status
  if (p->blacklist)
    s="Yes";
  else
    s="No";

  FXTableItem* item3=new FXTableItem(s);
  table->setItem(num, 2, item3);

  // Sets the creation date
  FXTableItem* item4=new FXTableItem(p->creation.c_str());
  table->setItem(num, 3, item4);

  // Sets the confirmation date
  FXTableItem* item5=new FXTableItem(p->confirm.c_str());
  table->setItem(num, 4, item5);

}

/** The Add account button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FoxAccountList::
onAddAccountClicked(FXObject* o,FXSelector s,void* v){
  LOGW("onAddAccountClicked called");

  return 1;
}

/** The Table selection callback
  *
  * This function is called when the \ref table selection change. To
  * provide only the whole row selection, we get the selected row from
  * the third argument. It must be cast to a FXTablePos pointer that
  * contains the selection psition.
  * 
  * \param vObj Not used
  * \param vSel Not used
  * \param vPos The object we cast to FXTablePos* to get the selection
  *             position.
  *
  * \return Always 1.
  *
  */
long RainbruRPG::Gui::FoxAccountList::
onTableSelectionChange(FXObject* vObj,FXSelector vSel,void* vPos){
  FXTablePos* pos= static_cast<FXTablePos*>(vPos);
  if (pos){
    cout << pos->row << "," << pos->col << endl;
    table->selectRow(pos->row);
    mSelectedAccountName=table->getItemText(pos->row, 0);
    LOGCATS("mSelectedAccountName=");
    LOGCATS(mSelectedAccountName.text());
    LOGCAT();
  }
  return 1;
}
