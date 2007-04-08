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
#ifndef SERVER_LIST
#define SERVER_LIST

#include "logger.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Hold_Browser.H>

#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>

#include "xmlserverlist.h"
#include "addserver.h"

namespace RainbruRPG{
  namespace Gui{

    /** Tghe fltk Fl_Group used to show the list of server
      *
      * It contains a Fl_Hold_Browser showing the servers' name and some
      * widgets showing the selected one.
      *
      * The informations shown are : the creation date of the server, its
      * description, its IP adress, its port and its technical note.
      *
      * This informations are stored in tServerListItem, a item of 
      * tServerList.
      */
    class ServerList : public Fl_Group {
    public:
      ServerList(int, int, int, int);
      ~ServerList();
      
      void refresh();
    private:
      static void cbShowServer(Fl_Widget *w, void *f);
      inline void i_cbShowServer();
      
      static void cbAdd(Fl_Widget *w, void *f);
      inline void i_cbAdd();

       static void cbDel(Fl_Widget *w, void *f);
      inline void i_cbDel();
     
      void loadServerList();
      void showNoneServer();
      void showServer(tServerListItem*);
      
      /** The fltk widget containing the server's name list */
      Fl_Hold_Browser *svrList;
      
      Fl_Multiline_Output* floDescription; //!< The description
      Fl_Output* floDate;    //!< The ip adress
      Fl_Output* floIpAdress;    //!< The ip adress
      Fl_Output* floPort;        //!< The tcp port
      Fl_Multiline_Output* floTechNote;    //!< The technical note
      Fl_Button* btnDel;     //!< The delete server button

      /** A global pointer to the player list */
      tServerList* pl;

      /** A pointer to the AddServer dialog */
      AddServer* addServer;
    };
  }
}

#endif // SERVER_LIST
