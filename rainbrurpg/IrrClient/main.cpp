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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

// - Collision detection ( 3 methodes)
// - chargement d'une map quake 3
// - mini interface graphique

// Mercredi 3 mai 2006

#include <irrlicht.h>
#include <iostream>
#include <FL/Fl.H>

#include "launcher.h"
#include "gameengine.h"
#include "logger.h"
#include "guimanager.h"
#include <version.h>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace irr;
using namespace gui;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Gui;

#pragma comment(lib, "Irrlicht.lib")

/** \mainpage Main Page
  *
  * \section intro_sec Introduction
  *
  * RainbruRPG is a 3D Role Playing Game project. It uses Fltk,
  * Irrlicht and Tinyxml.
  *
  * \section sec_versions Versions
  *
  * The version are numbered \e x.y.z-b.
  * - \e x represents the major version
  * - \e y represents the minor versions
  * - \e z is the revision
  * - \e b is the build number
  *
  * \section dep_clo Command Line Options
  *
  * \c --no-launcher : This option is passed to the GameEngine
  * singleton. The launcher will not be shown.
  *
  * \section dep_sec Dependencies
  *
  * To build RainbruRPG you need this libraries :
  * - Irrlicht SDK 1.0 (0.14);
  * - fltk 1.1.6.
  *
  * The project also uses Tinyxml as build-in c++ sources. So
  * you don't need to deal with it.
  *
  * \section ren_sec Available renderers
  *
  * Because of cegui using, the Irrlicht software renderers can't be
  * used. I hope we can use OpenGl and DirectX renderers.
  */

/** \page client_server The client/Server structure
  *
  * This game is client/server oriented. This means that at least 2
  * application are made. The client is the game, to be able to be
  * played, it must be connected to a server.
  *
  * The server can be private or public. If you made a private server,
  * no one can be connected from the internet (the server.list does not
  * contain the name of your server). A public server allows anyone to
  * connect to. 
  *
  * \image html publicserver.png
  */

/** \page xoops_module Server/Player information in website
  *
  * To provide a real-time information in website, a xoops module must
  * be created. It uses a XML parser to read the XML files and a
  * TCP/IP client to ask more information to the servers.
  *
  * The goal is to provides a message : "Actually, ??? players have an
  * account. ??? players are playing in ? actives servers."
  */

/** \page site_side Website side files
  *Rpg-v0.0.0-70.t
  * All the files describes below are website side. These are
  * tranfered with the FTP (File Transfer Protocol). When we must
  * modify one of these files, a \c filename.lock is created.
  *
  * The registrDate and registrTime attributes are deleted if we
  * confirm the mailAdresse. If the email adresse is not confirmed the
  * confirmeDate field does not exist.
  *
  * \section site_info website information
  *
  * A xoops module has been added to the site to show a real-time information
  * on the online servers.
  */

/** \page xml_options Options XML file
  *
  * All the options you can change in the launcher window are stored
  * in a xml files called \c data/saves/options.xml.
  *
  * \htmlinclude ../doc/xmlOptions.html


  * 
  * The root element is \c options. It can have one \c lastuse and
  * more  than opne \c snapshot childs. A snapshot is a graphic
  * configuration wich can be save and restore with the Launcher.
  *
  */

/** \page rpg_libs RPGLibs
  *
  * In order to reduce the executable file's size, some sources are
  * compiled and linked as a lib : rainbrurpg-commons
  *
  * This sources must be compiled in :
  * - logger.cpp
  * - options.cpp
  * - tinyxml/tinystr.cpp
  * - tinyxml/tinyxml.cpp
  * - tinyxml/tinyxmlerror.cpp
  * - tinyxml/tinyxmlparser.cpp
  *
  * \section udef_screenshot Undefined reference on sources with deps
  *
  * This compilation and linkage of the lib failed if I include on it
  * some sources : screenshotmanager, launcher... This files need a
  * dependance to another lib (fltk or irrlicht).
  */

/** \page reg_test Regression test
  *
  * For every step (x.y.z-b), I test :
  * - Building and execution on Linux and Windows;
  * - The logging (all Assertions that failed, Warnings and Errors)
  * 
  * The line count is 
  * generated using David A. Wheeler's 'SLOCCount'.
  *
  * \section build_win32 Win32 Building Rules
  *
  * On Win 32, I build RainbruRPG with Code::Blocks/GCC. You must have
  * these DevPacks :
  * - fltk 1.1.6
  * - irrlicht 0.14
  *
  * and the project must be linked with (*.a)
  * -	Irrlicht
  * -	fltk
  * -	ws2_32
  * -	wsock32
  * -	ole32
  * -	winspool
  * -	winmm
  * -	shell32
  * -	comctl21
  * -	ctl3d32
  * -	oleaut32
  * -	uuid
  *
  * In order to execute RainbruRPG in its own directory, you must set
  * this DLLs in the same directory than the RainbruRPG executable
  * file :<pre>
  *	D3DX81ad (8.1.0.0)		  313 856 octets
  *	D3DX92ab (9.4.91.0)	        2 314 240 octets
  *	Irrlicht			2 584 723 octets
  *</pre>
  *
  * \section tests Tests
  *
  * v 0.0.0-?? : 
  * - Test bugs #1 & #2 solutions.
  *
  * v 0.0.0-10 : 
  * - Test the selction of faeries and triangles.
  * - Test the colision detector (wall, stairs)
  * - Try to fall
  *
  *
  * The Mem column is the amount of memory used by the application on
  * Win32 system with the OpenGL renderer. Sys is set to OK if the
  * application can be compiles, linked and run on the given OS.
  *
  * The column called cc represents the Console's Count command result
  *
  * \htmlinclude ../doc/regTest.html
  */

/** \page bug_list Bug list
  *
  * Here you can find all bugs found in RainbruRPG. The unsolved bugs
  * are in gray, the other colors are pllied to soled bugs.
  *
  * The bugs are ordered, the num is on the \b # column. The sys is
  * here to tell if this bug is in Linux, Win32 or both.
  *
  * <!--"#CCFFFF">  BLUE -->
  * <!--"#FFFFCC">  YELLOW -->
  * <!--"#999999" >  GRAY-->
  *
  * \htmlinclude ../doc/bugList.html
  */


/** \page valgrind_test Valgrind test
  *
  * Valgrind is a program wich can test a program's memory use.
  *
  * \section val_mem_leaks Memory Leaks
  *
  * To test possible memory leaks, run :<br>
  * <code>valgrind --leak-check=yes --log-file-exactly="val.log" 
  * rainbruRPG</code>. \c alleyoop is a frontend for valgring.
  *
  * Valgrind will print its results :
  * <pre>
  * ==8273== LEAK SUMMARY:
  * ==8273==    definitely lost: 1978 bytes in 30 blocks.
  * ==8273==    indirectly lost: 440 bytes in 22 blocks.
  * ==8273==      possibly lost: 208184 bytes in 328 blocks.
  * ==8273==    still reachable: 43356252 bytes in 7473 blocks.
  * ==8273==         suppressed: 0 bytes in 0 blocks.
  * </pre>
  *
  * Here is the table of tests :
  *
  * LR represents the number of loss record.
  *
  * <table width=100% border="1" bgcolor="#00CC99" cellspacing ="0" 
  *        cellpadding ="0">
  *   <tr>
  *     <th rowspan=2width=50px>Version</th>
  *     <th rowspan=2>LR</th>
  *     <th colspan=2>Definitely</th>
  *     <th colspan=2>Indirectly</th>
  *     <th colspan=2>Possibly</th>
  *     <th colspan=2>Reachable</th>
  *     <th colspan=2>Suppressed</th>
  *   </tr>
  *   <tr>
  *     <th>by</th>
  *     <th>bl</th>
  *     <th>by</th>
  *     <th>bl</th>
  *     <th>by</th>
  *     <th>bl</th>
  *     <th>by</th>
  *     <th>bl</th>
  *     <th>by</th>
  *     <th>bl</th>
  *   </tr>
  *
  *   <tr bgcolor="#CCFFFF" >
  *     <td>0.0.0-18</td>
  *     <td>1 014</td>
  *     <td>4 446</td>            <td>10</td>
  *     <td>31320</td>            <td>16</td>
  *     <td>0</td>                <td>0</td>
  *     <td>2 204 660</td>        <td>3 512</td>
  *     <td>0</td>                <td>0</td>
  *   </tr>
  *
  *
  *   <tr bgcolor="#FFFFCC" >
  *     <td>0.0.0-17</td>
  *     <td>-</td>
  *     <td>1 970</td>            <td>30</td>
  *     <td>440</td>              <td>22</td>
  *     <td>208 184</td>          <td>328</td>
  *     <td>43 142 560</td>       <td>7 340</td>
  *     <td>0</td>                <td>0</td>
  *   </tr>
  *
  *   <tr bgcolor="#CCFFFF" >
  *     <td>0.0.0-10</td>
  *     <td>-</td>
  *     <td>1 978</td>            <td>30</td>
  *     <td>440</td>              <td>22</td>
  *     <td>208 184</td>          <td>328</td>
  *     <td>43 356 252</td>       <td>7 473</td>
  *     <td>0</td>                <td>0</td>
  *   </tr>
  */

/** \page debCons Debugging Console 
  *
  * RainbruRPG provides an in-game debugging console. It is accessible
  * by hitting the <sup>2</sup> key (between the Tab and Esc keys).
  * The console is case insensitive so \c Get, \c gEt, \c get and \c
  * GET are valids.
  *
  * \section console_syntax The console syntax.
  *
  * All the command lines are made like this one :<br>
  * <pre>action object.attribute value</pre>
  * Where action can be \c set or \c get.
  *
  * There is special command :
  * - \c help (or ?) : show a basic help;
  * - \c help object : show all the attributes of the object with a
  * little description;
  *
  * \section console_example Examples
  *
  * Here are some example fonctions :
  *
  * <pre>get core.debug on</pre> set the \c debug attribute of the
  * object \c core to on.
  *
  * \section con_attr_type Attributes types
  *
  * The attributes are typed. So, a boolean can't be set to "aze"
  * value.
  *
  * - Boolean : on|off
  * - Integer : an integer (ex 1, 1200, 45300)
  * - Float   : a floating point number ex (4, 3.20, 4.02335)
  * - String  : a string ("aze", "eryull", "").
  *
  * \section err_cons Error messages
  *
  * - Unknown command '...' : the command must be \c help, \c set or
  * \c get;
  * - Unknown object '...' : the object doesn't exists;
  * - Unknown attribute '...' for object '...' : the attributes you
  * type doesn't exists in this object's space;
  * - Type error : 'Obj.aatrb' is of type '...' : the error contains
  * the type of the attribute need.
  */

/** \page translation Translation
  *
  * RainbruRPG provides its own translation system to avoid
  * portability issues. It comes with 2 executables : 
  * - \c transmsg : wich make the translation message file
  * - \c transgui : a GUI program wich let you make translation of
  *                 messages extracted by \c transmsg
  *
  * \section trans_dev Developper's view
  *
  * For each simple string you need to Translate, you must use a define based
  * macro called TR like this : <code>TR(idmsg, "message")</code>. For
  * the large amount of test, use instead the \c TRL("filename") macro.
  *
  * \section trans_tor Translator's view
  *
  * Before translate the strings, you must call the \c transmsg
  * program. It will create the strings-to-translate list.
  * 
  * Then you can call the \c transgui tool to translate the list.
  *
  * \section trans_intern Internal view
  *
  * \subsection trans_files The used files

  * Each language is identified by 2 char (\c FR for french, \c EN for
  * english...) and the \c transmsg program know that you're coding in
  * english language. It will create a 'messages_EN.xml' file. It will
  * not create the files called by the \c TRL("filename") macro. All
  * this files \b must be in the data/trans directory.
  *
  * When you call \c transgui, it takes all the files and it provides
  * you a simple way to translate both the simple strings and the
  * Large files. But the naming rule of the Large files must be
  * followed :
  * - The filename must be 'filename_XX.xml';
  * - The filename is in lower case.
  *
  * \subsection trans_context The translation context
  *
  * To provides a fast access to some translation string, the
  * translation system uses a context styled translation. The context
  * of a string is the filename (without the extension) from where it
  * is called. Example, if you use a string in the file \c foo.cpp,
  * the translation context of this string will be \c foo.
  *
  * All the contexts can be pre-load in memory to provide a fast-access
  * to its translation string. Otherwise, the xml file will be opened
  * each time you search a string in and the string will be search in
  * its context.
  */ 
 
//=================================================================
//          N A M E S P A C E
//=================================================================


/** \namespace RainbruRPG
  *
  * The global RainbruRPG namespace.
  *
  * All the classes used for this game must be part of this namespace
  * or one of its child.
  *
  */

/** \namespace RainbruRPG::Core
  *
  * The namespace of the core classes.
  *
  * The core classes are the managers, the templates and all the class
  * that cannot be in another namespace. It provides a
  * GameEngine/GameState mechanism : The GameState can have several
  * GameState-based class (call gs????). Only one GameState can be on
  * at a time and we can switch beetween them, pause and resume a GameState.
  *
  */

/** \namespace RainbruRPG::Gui
  *
  * The namespace of the Graphic User Interface 
  *
  * In this namespace are grouped the fltk and irrlicht build-in based
  * GUI classes.
  *
  */

/** \namespace RainbruRPG::Events
  *
  * The namespace of the events handlers
  *
  * The classes used for events are inside this namespace.
  *
  */

/** \namespace RainbruRPG::Exception
  *
  * The namespace of the logger and the exceptions
  *
  * This namespace contains the Logger,the exceptions or
  * the debugging classes. The attributes wrapper used by the debugging
  * console to access game values are in this namespace.
  *
  */

/** \namespace RainbruRPG::Options
  *
  * The namespace of the options system
  *
  * This namespace contains the options model classes and the
  * associated xml parser/writer.
  *
  */

/** \namespace RainbruRPG::Concept
  *
  * The namespace of the roleplay concept
  *
  * This namespace contains the concepts of the RPG roleplay part of
  * this game. Player, AI...
  *
  */

/** \namespace RainbruRPG::Concept::Player
  *
  * The namespace of the player concept
  *
  * This namespace contains the player concept classes.
  *
  */

/** \namespace RainbruRPG::Concept::AI
  *
  * The namespace of the Artificial Intelligence concept
  *
  * This namespace contains the AI (NPC) concept.
  *
  */

/** \namespace RainbruRPG::Editor
  *
  * The namespace of the RainbruRPG Editor
  *
  * This namespace contains the classes used for the Editor.
  *
  */

/** \namespace RainbruRPG::Terminal
  *
  * The namespace of the S-Lang API used by the server
  *
  * This namespace contains the S-Lang GUI API used by the server and
  * some text-based tools. It declares TerminalApp, a Singleton that
  * you must call. You can add a MenuBar and some Window to this Singleton. 
  *
  * In a Window, you can add some Widget based class. The events are
  * function-pointer driven.
  */

/** \namespace RainbruRPG::Network
  *
  * The global Network namespace.
  *
  * All the classes used for Network connexion.
  *
  */

/** \namespace RainbruRPG::Network::Ident
  *
  * The namespace of used by the identification protocol
  *
  * The \c xident maintenance program and others wich are used for the
  * identification protocol. 
  *
  */
using namespace RainbruRPG::Core;

/** The main function */
int main(int argc, char** argv){
  srand((unsigned)time(0)); 

  Version v;
  v.setApplicationName("RainbruRPG Client");
  v.logVersion();


  RainbruRPG::Gui::Launcher *l=new RainbruRPG::Gui::Launcher();
  l->hide();

  Fl::flush();

  GameEngine::getSingleton().init();
  GameEngine::getSingleton().setGuiTransparency(180);

  //  GameEngine::getSingleton().changeState(ST_CONNECT);
  GameEngine::getSingleton().changeState(ST_PERSO_CREATE);

  //GameEngine::getSingleton().changeState(ST_GAME);

  while(GameEngine::getSingleton().running()&&
	GameEngine::getSingleton().getIrrlichtDevice()->run()){

    if (GameEngine::getSingleton().getIrrlichtDevice()->isWindowActive()){
      GameEngine::getSingleton().run();
      GuiManager::getSingleton().showFPS();
    }
  }

  GameEngine::getSingleton().cleanup();
  GuiManager::getSingleton().cleanup();
  LOGI("Closing Irrlicht Device");
  //    GameEngine::getSingleton().getIrrlichtDevice()->closeDevice();
  //    GameEngine::getSingleton().getIrrlichtDevice()->drop();
    //  l->~Launcher();

  //  LOGI("Application cleanup OK");

  // return 0;
  return 0;
}


