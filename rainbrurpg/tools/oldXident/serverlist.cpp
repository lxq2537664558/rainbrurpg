/*
 *  Copyright 2006 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "serverlist.h"

/** The placement constructor
  *
  * \param x The x placement
  * \param y The y placement
  * \param w The width of the panel
  * \param h The height of the panel
  *
  */
RainbruRPG::Gui::ServerList::ServerList(int x, int y, int w, int h)
                    :Fl_Group(x, y, w, h, "Server list") {

  // The x coordonate of the output fields;
  int out=350;
  // The width of the multiline output fields
  int moWidth=(x+w)-360;
  // The x coordonate of the buttons
  int xBtn=(x+w)-110;

    this->box(FL_SHADOW_BOX);

    svrList=new Fl_Hold_Browser(x+10, y+10, 200, h-20 );
 
    floDate =new Fl_Output(out, y+10, 200, 20, "Inline since");

    floDescription=new Fl_Multiline_Output(out, y+30, moWidth-110, 20, 
					   "Description");
 
    floIpAdress=new Fl_Output(out, y+50, 150, 20, "Ip adress");
    floPort =new Fl_Output(out, y+70, 120, 20, "Port");
    floTechNote=new Fl_Multiline_Output(out, y+90, moWidth, 60, "Tech note");
    

    Fl_Button* btnAdd=new Fl_Button( xBtn, y+10, 100, 30, "Add" );
    btnDel=new Fl_Button( xBtn, y+40, 100, 30, "Delete" );

  this->end();

  btnDel->deactivate();

  svrList->callback(cbShowServer, this);
  btnAdd->callback(cbAdd, this);
  btnDel->callback(cbDel, this);

  addServer=NULL;
  loadServerList();
}

/** The default destructor
  * 
  */
RainbruRPG::Gui::ServerList::~ServerList(){

}

/** Graphically loads the server list into the fltk Fl_Hold_Browser
  *
  */
void RainbruRPG::Gui::ServerList::loadServerList(){
  tServerList::const_iterator iter;
 
  pl= new tServerList();

  xmlServerList xmlPl;
  pl=xmlPl.getServerList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      svrList->add( (*iter)->name );
    }
  }
}

/** The static callback used to show server's information
  *
  */
void RainbruRPG::Gui::ServerList::cbShowServer(Fl_Widget *w, void *f){
  ( (ServerList*)f )->i_cbShowServer();

}

/** The inline callback used to show server's information
  *
  * It fills some widget with the selected server information.
  */
void RainbruRPG::Gui::ServerList::i_cbShowServer(){
  tServerList::const_iterator iter;

  showNoneServer();

  // get the selected item
  int sel=svrList->value();


  // An item is selected
  if (sel>0){
    btnDel->activate();
    //get the text of this item
    const char* str= svrList->text(sel);
    

    // Iterate through the tPlayerList
    if (pl){
      for (iter=pl->begin(); iter != pl->end(); iter++){
	const char* tname=(*iter)->name;
	// If the two names are the same
	if(strcmp(str, tname)==0){
	  showServer((*iter));
	}
      }
    }
  }
  else{ // None player is selected
    showNoneServer();
    btnDel->deactivate();
  }

}

/** Set the server information widgets empty
  *
  * This method is used when no server is selected.
  */
void RainbruRPG::Gui::ServerList::showNoneServer(){
  floDescription->value("");
  floIpAdress->value("");
  floPort->value("");
  floTechNote->value("");
}

/** Shows the information of this server
  *
  * \param i A pointer to the server to show
  */
void RainbruRPG::Gui::ServerList::showServer(tServerListItem* i){
  floDate->value(i->creation.c_str());
  floDescription->value(i->description);
  floIpAdress->value(i->ipAdress);
  floPort->value(i->port);
  floTechNote->value(i->techNote);
}

/** The static callback to add a server
  *
  */
void RainbruRPG::Gui::ServerList::cbAdd(Fl_Widget *w, void *f){
  ( (ServerList*)f )->i_cbAdd();
}

/** The inline callback to add a server
  *
  * It creates a AddServer dialog if the global addServer pointer is NULL.
  * otherwise, it shows the existign AddServer dialog.
  */
void RainbruRPG::Gui::ServerList::i_cbAdd(){

  if (addServer==NULL){
    addServer=new AddServer(this);
  }
  else{
    addServer->show();
  }
}

/** Refresh the server list
  *
  * It internally calls showNoneServer() and loadServerList();
  */
void RainbruRPG::Gui::ServerList::refresh(){
  showNoneServer();
  svrList->clear();
  loadServerList();
}

/** The static callback to delete a server
  *
  */
void RainbruRPG::Gui::ServerList::cbDel(Fl_Widget *w, void *f){
  ( (ServerList*)f )->i_cbDel();

}

/** The inline callback to delete a server
  *
  * It calls delServer() of xmlServerList.
  */
void RainbruRPG::Gui::ServerList::i_cbDel(){
 // get the selected item
  int sel=svrList->value();


  // An item is selected
  if (sel>0){
    //get the text of this item
    const char* svName= svrList->text(sel);

    // A confirmation dialog
    string s="Do you really want to definitly delete the server ";
    s+=svName;
    s+=" ?";
    int confirmation= fl_choice(s.c_str(), "Yes", "No", NULL);

    if (confirmation==0){ //yes
      xmlServerList xmlSvr;
      xmlSvr.delServer( svName );
    }
  }

  refresh();
}
