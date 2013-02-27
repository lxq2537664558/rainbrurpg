/*
 *  Copyright 2006-2013 Jerome PASQUIER
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
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <slang.h>

#include <terminalapp.h>
#include <hook.h>

#include <menubar.h>
#include <menu.h>
#include <window.h>
#include <label.h>
#include <logger.h>
#include <lineedit.h>
#include <listbox.h>
#include <pushbutton.h>
#include <listview.h>
#include <listviewitem.h>
#include <infodialog.h>

using namespace RainbruRPG::Terminal;

int closeDialog(){
  TerminalApp::getSingleton().closeDialog();
  return 1;
}

int btn1Action(){
  InfoDialog* id= new InfoDialog( "A test of InfoDialog", 60, 10 );
  id->setMessage("This dialog is a test. It tests the caption::WORD_WRAPPED. If it seems to work, it can be good for some differents purpose. To correctly test this word wrapped text, it must be very long so I add text, and text...");

  PushButton* pb=new PushButton( "OK" );
  pb->setAction( &closeDialog );
  id->addButton( pb );

  TerminalApp::getSingleton().showDialog( id );
}

int item1Action(){
  TerminalApp::getSingleton().showMessage("Item1 has been called");

  Window* w=new Window("Server information");

  Label* l=new Label("Essai de label");
  w->getLayout()->addWidget( l, 0, 0, 10, 1 );

  LineEdit* l2=new LineEdit("lineedit");
  w->getLayout()->addWidget( l2, 0, 1, 20, 1 );

  ListBox * lb=new ListBox( "Listbox" );
  lb->addItem("Item1");
  lb->addItem("Item2");
  lb->addItem("Item3");
  lb->addItem("Item4");
  lb->addItem("Item5");
  lb->addItem("Item6");
  w->getLayout()->addWidget( lb, 0, 2, 15, 8 );

  LineEdit* l3=new LineEdit("lineedit2");
  w->getLayout()->addWidget( l3, 20, 0, 20, 1 );

  LineEdit* l4=new LineEdit("lineedit3");
  w->getLayout()->addWidget( l4, 20, 1, 20, 1 );

  LineEdit* l5=new LineEdit("lineedit4");
  w->getLayout()->addWidget( l5, 20, 2, 20, 1 );

  PushButton* pb=new PushButton( "Cancel" );
  pb->setAction( &btn1Action );
  w->getLayout()->addWidget( pb, 20, 3, 20, 1 );

  // The ListView test
  ListView* lv=new ListView( "ListView test");
  lv->addColumn(new ListViewColumn("col1", 5));
  lv->addColumn(new ListViewColumn("col2", 8));
  lv->addColumn(new ListViewColumn("col3", 6));
  w->getLayout()->addWidget(lv, 20, 4, 30, 8);

  ListViewItem * lvi01=new ListViewItem();
  lvi01->addColumn("12345");
  lvi01->addColumn("12345678");
  lvi01->addColumn("123456");
  lv->addItem(lvi01);

  ListViewItem * lvi02=new ListViewItem();
  lvi02->addColumn("23456");
  lvi02->addColumn("23456789");
  lvi02->addColumn("234567");
  lv->addItem(lvi02);

  ListViewItem * lvi03=new ListViewItem();
  lvi03->addColumn("34567");
  lvi03->addColumn("34567890");
  lvi03->addColumn("345678");
  lv->addItem(lvi03);

  TerminalApp::getSingleton().addWindow(w, true);

  return 1;
}

using namespace  RainbruRPG::Exception;

int main (int argc, char **argv){

  Logger::getSingleton().setFilename("apitest.log");
  Logger::getSingleton().setLogType( RainbruRPG::Exception::LOG_FILE );

  MenuBar mb;

  Menu m("&Server");
    MenuItem* it1=new MenuItem("&Identification");
    it1->setAction(&item1Action);
    m.addItem(it1);
    m.addItem(new MenuItem("item &2"));
    m.addItem(new MenuItem("very very long item &3"));
  mb.addMenu(&m);

  Menu m2("&Menu2");
    m2.addItem(new MenuItem("Menu 2/item &1"));
    m2.addItem(new MenuItem("Menu 2/item &2"));
    m2.addItem(new MenuItem("Menu 2/item &3"));
    m2.addItem(new MenuItem("Menu 2/item &4"));
    m2.addItem(new MenuItem("Menu 2/item &5"));
    m2.addItem(new MenuItem("Menu 2/item &6"));
    m2.addItem(new MenuItem("Menu 2/item &7"));
    m2.addItem(new MenuItem("Menu 2/item &8"));
    m2.addItem(new MenuItem("Menu 2/item &9"));
    m2.addItem(new MenuItem("Menu 2/item &10"));
    m2.addItem(new MenuItem("Menu 2/item &11"));
    m2.addItem(new MenuItem("Menu 2/item &12"));
    m2.addItem(new MenuItem("Menu 2/item &13"));
    m2.addItem(new MenuItem("Menu 2/item &14"));
    m2.addItem(new MenuItem("Menu 2/item &15"));
    m2.addItem(new MenuItem("Menu 2/item &16"));
    m2.addItem(new MenuItem("Menu 2/item &17"));
    m2.addItem(new MenuItem("Menu 2/item &18"));
    m2.addItem(new MenuItem("Menu 2/item &19"));

    m2.addItem(new MenuItem("Menu 2/item &20"));
    m2.addItem(new MenuItem("Menu 2/item &21"));
    m2.addItem(new MenuItem("Menu 2/item &22"));
    m2.addItem(new MenuItem("Menu 2/item &23"));
    m2.addItem(new MenuItem("Menu 2/item &24"));
    m2.addItem(new MenuItem("Menu 2/item &25"));
    m2.addItem(new MenuItem("Menu 2/item &26"));
    m2.addItem(new MenuItem("Menu 2/item &27"));
    m2.addItem(new MenuItem("Menu 2/item &28"));
    m2.addItem(new MenuItem("Menu 2/item &29"));
  mb.addMenu(&m2);

  mb.addMenu(new Menu("aze&rty"));
  mb.addMenu(new Menu("a&ze"));

  TerminalApp::getSingleton().setMenubar(&mb);
  TerminalApp::getSingleton().init();

  TerminalApp::getSingleton().draw();



  SLtt_set_color (0, NULL, "lightgray", "blue");

  TerminalApp::getSingleton().run();
  TerminalApp::getSingleton().cleanup();

  demolib_exit (0);
   
  return 0;
}
