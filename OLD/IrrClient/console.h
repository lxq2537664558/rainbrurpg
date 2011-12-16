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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <irrlicht.h>
//#include <string>
#include <vector>
#include <stdlib.h>

#include "singleton.h"
#include "tokenizer.h"
#include "tokenizerdbg.h"
#include "gameengine.h"
#include "consoleobject.h"
#include "cocore.h"

//using namespace std;
using namespace irr;
using namespace irr::core;
using namespace video;
using namespace gui;
using namespace RainbruRPG::Core;

namespace RainbruRPG {
  namespace Exception{

    /** A console command object
      *
      * A console command is a command text and eventually the
      * namespace it calls in.
      *
      */
    struct consoleCmd{
      irr::core::stringw cmd;    //!< The command text
      irr::core::stringw prompt; //!< The command namespace
    };

    /** The debugging console
      *
      * This is the developper reference of the Console class. If you
      * want to know how to use the console, you should see \ref
      * debCons "this page".
      *
      * This singleton class is used to create an console. It
      * provides in-game access to ConsoleObject. You can move the
      * console's scrollbar with the PAGEUP PAGEDOWN keys and call
      * former commands with the UP and DOWN ones.
      *
      * To provides the access of multiple command in a single object,
      * we use a Namespace function. With the \c using keyword, you
      * can preselect an object that will be used for the attribute
      * access until you choose to set the namespace to none (by
      * calling \c using \c none).
      *
      * If the function's name start with \c command, it treat a
      * console's command. ex: commandShowObject treat the \c show \c
      * object_name command.
      *
      * The Console is created only if you call it and is keeping in
      * memory when you hide it. So it will never take CPU charge if
      * you do not use it but once you have call it, it will always
      * stay in memory.
      * 
      * The console has its own event receiver :
      * RainbruRPG::Events::erConsole, and it is shown/hiden by the
      * GameEngine showConsole() and hideConsole() method.
      */
    class Console : public Singleton<Console>{
    public:
      Console(){};
      void init();
      void initScrollbar();
      void cleanup();
      void createConsole();

      void hide();
      void enter();
      void setHome();
      void setEnd();
      void setPageUp();
      void setPageDown();
      void setUp();
      void setDown();

      void clearConsole();
      void showHelp();
      void showList();

    private:
      /** Unimplemented copy constructors 
        *
	* In a singleton the use of this method must be forbidden.
	* 
	* \param obj A Console
	*/
      Console(const Console& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this method must be forbidden.
	* \param obj A Console
	*/
      Console& operator=(const Console& obj);


      void setPrompt();
      void initObjectsVector();
      void cleanupObjectsVector();

      irr::core::stringw getIndentedString();
      void showIndentedMessage( irr::core::stringw );
      void showCmdIndex();
      void showPrevCmd();
      void showAllObjects();
      void showCmdCount();
      int  showObjCount(ConsoleObject*);
      void showObjectAttribute(ObjectAttribute*);

      void treatCommandType(tTokentizerReturn* t );

      bool simpleCommand( irr::core::stringw );
      bool doubleCommand( tTokentizerReturn* );
      bool tripleCommand( tTokentizerReturn* );
      bool quadCommand  ( tTokentizerReturn* );

      void commandNotFound( irr::core::stringw );
      void commandShowObject( std::string );
      void commandUsingObject( std::string );
      void commandGetObjectAttribute( tTokentizerReturn* );

      bool getTokenizerError( tTokentizerReturn* );
      ConsoleObject* getObjectByName(std::string);
      ObjectAttribute* getAttributeByName( ConsoleObject*, std::string);

      /// The Irrlicht Device
      irr::IrrlichtDevice *irrDevice;

      /// The Irrlicht driver type
      irr::video::E_DRIVER_TYPE driverType;

      /// The Irrlicht video driver
      irr::video::IVideoDriver* irrDriver;

      /// The Irrlicht scene manager
      irr::scene::ISceneManager* irrSmgr;

      /// The Irrlicht build-in Gui environment
      irr::gui::IGUIEnvironment* irrGui;

      /// The tab used to show and hide the console
      IGUITab*        irrTab;
      /// The editBox of the console
      IGUIEditBox*    consoleEdit;
      /// The listBox of the console
      IGUIListBox*    consoleList;
      /// The staticText used to show the current prompt
      IGUIStaticText* consolePrompt;
      /// The staticText used to show the index of the command
      IGUIStaticText* consoleIndex;
      /** The scrollBar of the console
        *
	* It is created by the consoleList listBox so the
	* initScrollbar() methode search it in the consoleList's
	* child list.
	*/
      IGUIScrollBar*  scrollbar;

      /** The tokenizer instance
        *
	* It is created once and used.
	*/
      Tokenizer *tok;

      /** The Tokenizer debugger
        *
	*
	*/
      TokenizerDbg *tokDbg;

      /// The prompt show in the consolePrompt staticText
      irr::core::stringw prompt;

      /** The value to add or remove to the scrollbar position when
        * the user hits PAGEUP and PAGEDOWN;
        *
	*/
      int scrollValue;

      /** The index of the current command 
        *
	* This integer value is set to 0 in the init() method and is
	* incremented by 1 at each enter key hitting.
        */
      int cmdIndex;

      /** The command recall vector
        *
	* To provides the recalling of the former commands and the \c
	* list command result, we keep all the command in this vector
	*/
      vector<consoleCmd> cmdVector;

      /** The object vector
        *
	* All the objects stored in this vector can be access at real time.
	*/
      vector<ConsoleObject*> objectsVector;
    };
  }
}
#endif // CONSOLE_H
