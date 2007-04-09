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

#include "tapitestsuite.h"

// TestFixtures implementations
#include "captiontest.h"
#include "freelayouttest.h"
#include "infodialogtest.h"
#include "labeltest.h"
#include "layouttest.h"
#include "lineedittest.h"
#include "listboxtest.h"
#include "listboxitemtest.h"
#include "listviewtest.h"
#include "listviewcolumntest.h"
#include "listviewitemtest.h"
#include "menutest.h"
#include "menubartest.h"
#include "menuitemtest.h"
#include "pushbuttontest.h"
#include "scrollingpaneltest.h"
#include "terminalapptest.h"

// Classes to be tested
#include <caption.h>
#include <freelayout.h>
#include <infodialog.h>
#include <label.h>
#include <layout.h>
#include <lineedit.h>
#include <listbox.h>
#include <listboxitem.h>
#include <listview.h>
#include <listviewcolumn.h>
#include <listviewitem.h>
#include <menu.h>
#include <menubar.h>
#include <menuitem.h>
#include <pushbutton.h>
#include <scrollingpanel.h>
#include <terminalapp.h>

using namespace RainbruRPG::Terminal;

/** Test suite constructor
  *
  */
tapiTestSuite::tapiTestSuite()
  :TestSuite("TerminalAPI")
{
  addTest( CaptionTest<Caption>::suite() );
  addTest( FreeLayoutTest<FreeLayout>::suite() );
  addTest( InfoDialogTest<InfoDialog>::suite() );
  addTest( LabelTest<Label>::suite() );
  addTest( LayoutTest<Layout>::suite() );
  addTest( LineEditTest<LineEdit>::suite() );
  addTest( ListBoxTest<ListBox>::suite() );
  addTest( ListBoxItemTest<ListBoxItem>::suite() );
  addTest( ListViewTest<ListView>::suite() );
  addTest( ListViewColumnTest<ListViewColumn>::suite() );
  addTest( ListViewItemTest<ListViewItem>::suite() );
  addTest( MenuTest<Menu>::suite() );
  addTest( MenuBarTest<MenuBar>::suite() );
  addTest( MenuItemTest<MenuItem>::suite() );
  addTest( PushButtonTest<PushButton>::suite() );
  addTest( ScrollingPanelTest<ScrollingPanel>::suite() );
  addTest( TerminalAppTest<TerminalApp>::suite() );
}

/** Destructor
  *
  */
tapiTestSuite::~tapiTestSuite(){

}