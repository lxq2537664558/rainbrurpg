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

/** \file terminalapp.h
  * Defines the base class of TerminalAPI.
  * 
  * Defines the \ref RainbruRPG::Terminal::TerminalApp "TerminalApp"
  * class.
  *
  * Modifications :
  * - 11 jul 2008 : Now using std strings 
  *
  */
#ifndef TERMINAL_APP
#define TERMINAL_APP

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <slang.h>
#include <list>

#include <boost/algorithm/string.hpp> // For to_lower()

#include "singleton.h"
#include "hook.h" //The signal handler's functions
#include "menubar.h"
#include "window.h"
#include "dialog.h"

using namespace RainbruRPG::Core;
using namespace std;
using namespace boost;

namespace RainbruRPG{
  namespace Terminal{

    /** Represents a menu shortcut */
    struct tShortCut{
      char sc;     //!< The char corresponding to the shortcut
      Menu* menu;  //!< The menu opened by this shortcut
      int xPos;    //!< The X position of the menu we have to open
    };

    /** A stl list of shortcut */
    typedef std::list<tShortCut*> tShortcutList;

    /** A stl list of Window */
    typedef std::list<Window*> tWindowList;

    /** The Base class of the terminal API
      *
      * This class uses S-Lang.
      *
      * A dialog can be set with showDialog(Dialog*)
      *
      * Before using this class, call init().
      * This class should use a menu bar, you can set it by calling 
      * setMenubar(MenuBar*).
      *
      * The standard usage is as follow :
      * <code>
      * TerminalApp::getSingleton().init();
      * TerminalApp::getSingleton().setMenubar(createMenubar());
      * TerminalApp::getSingleton().draw();     
      * TerminalApp::getSingleton().run();     
      * // TerminalAPI is wotking
      * TerminalApp::getSingleton().cleanup();     
      * </code>
      *
      */
    class TerminalApp :public Singleton<TerminalApp>{
    public:
      TerminalApp();
      ~TerminalApp();

      void init();
      void run();
      void cleanup();

      void draw();

      ///////////////////
      // Public functions

      void setMenubar( MenuBar* );
      MenuBar* getMenubar();
      void showMessage(const std::string&);
      void showDialog(Dialog*);
      void addWindow(Window*);
      void addWindow(Window* , bool);

      void closeDialog();
      unsigned int windowCount();
      Dialog* getCurrentDialog();


    private:
      /** Unimplemented forbidden copy constructor
        *
	* \param obj a TerminalApp
	*/
      TerminalApp(const TerminalApp& obj);

      /** Unimplemented forbidden assignment constructor
        *
	* \param obj a TerminalApp
	*/
      TerminalApp& operator=(const TerminalApp& obj);

      int getch();

      int initTerminal (int , int);
      void initSignals();
      void initColors();

      void eraseScreen();
      void actionMenu();

      void drawMessageBox();
      void drawKeycodeBox();
      void drawEmptyMenuBar();
      void drawMenuBar();
      void drawMenuCaption(int x, int y, string c);
      void drawSelectedMenuCaption(int x, int y, string c);
      void drawBiggerMenuIndicatorBotton(int);
      void drawWindows();

      void high(bool);
      void createMenuBarShortcut();
      void drawMenu( tShortCut* );

      void keyHit();
      void keyTabHit();
      void keyArrowInMenu(int);
      void sendKeyToCurrentWindow( int );

      tShortCut* getShortcutFromIndex(int);
      void drawItemCaption(int x, int y, string c ,bool hl);


      ////////////////////
      // Private variables

      /** The current Dialog
        *
	*/
      Dialog* dialog;

      /** The TerminalApp MenuBar
        *
	* Always NULL if no menubar is manually set.
	*
	*/
      MenuBar* menubar;

      /** The current available shortcut list 
        *
        */
      tShortcutList currentShortcut;

      /** The Window list 
        *
        */
      tWindowList windowList;

      /** The waiting time in milliseconds to check if input is pending
        *
	* This is the parameter send to the SLang_input_pending SLang function.
	*/
      int timeout;

      /** The width of the keycodeBox
        *
	*/
      int keycodeboxWidth;
      /** The last key code returned by the getch() function
        *
	*/
      int lastKeycode;

      /** The current selected menu if inMenu is true
        *
	*/
      int currentMenu;

      /** The current selected sub menu if inSubMenu is true
        *
	* This index is the submenu selected in the menu currentMenu.
	*
	*/
      int currentSubMenu;

      /** if we found the Alt key (195) we set this to true
        *
	*/
      bool altKeycode;

      /** Are we in the menubar
        *
	*/
      bool inMenu;
      /** If inMenu and inSubMenu are true, we are in a subMenu
        *
	*/
      bool inSubMenu;

      /** If showDialog(Dialog*) has been called, true
        *
	*/
      bool showingDialog;

      /** The string to be drawn in the message box
        *
	*/
      std::string message;
    };
  }
}

#endif //TERMINAL_APP
