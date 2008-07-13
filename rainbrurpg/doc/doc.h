// This header does not contain code
// It is only documentation

/*
 *  Copyright 2006-2008 Jerome PASQUIER
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


/** \mainpage Main Page
  *
  * \section intro_sec Introduction
  *
  * %RainbruRPG is a 3D Role Playing Game project. It uses FOX toolkit,
  * Ogre/CEGUI and Tinyxml.
  *
  * \section sec_versions Versions
  *
  * The version are numbered \e x.y.z-b.
  * - \e x represents the major version
  * - \e y represents the minor version
  * - \e z is the revision
  * - \e b is the build number
  *
  * Until 1.0.0, the game will not be playable or will be unstable. Then, 
  * the stability will be improved until it is fully usable. When 1.y.z is
  * stable, we will plan 2.0.0.
  *
  * \section dep_sec Dependencies
  * \subsection libraries_versions_subsec Libraries versions
  *
  * To build RainbruRPG you need these libraries :
  * - Fox toolkit v1.6 or 1.4
  * - Ogre v1.2(with GLX platform)
  * - OIS (Object-oriented Input System) v1.0
  *
  * The project also uses <a href="http://www.grinninglizard.com/tinyxml/">
  * Tinyxml</a> (zlib license) and <a href="http://easybmp.sourceforge.net/">
  * EasyBMP</a> (modified BSD license) as build-in c++ sources. 
  * So you don't need to deal with it.
  *
  * \subsection ogre_platform_subsec Ogre Platform
  *
  * On GNU/Linux, Ogre3D can be used with multiple platforms (SDL, GTK, GLX).
  * I personnally use the GLX one. The SDL platform makes the following
  * issues happening as of Ogre v1.2.5 (<b>bug #21)</b>:
  * - The client freezes the mouse.
  * - The editor's ogre widget is opened on a separated window.
  * - Some issues when moving the camera can happened.
  *
  * \section signals_slots_sec Signals/Slots mechanism
  *
  * Some part of this projet use sigc++ for signal/slot mechanism. See
  * http://libsigc.sourceforge.net/libsigc2/docs/manual/html/index.html
  * for further informations. Please see the RainbruRPG::Network::FtpClient
  * class for more informations.
  *
  * In Qt based applications, I use the Qt signal/slot implementation.
  *
  * \section FTP_sec FTP datafiles
  *
  * This section tells where to find datafiles. The FTP server will copy
  * datafiles at this place :
  *
  * - From the editor to the server : The editor can send a file
  *   from everywhere in your local filesystem. The server will
  *   store the file in the \e quarantine directory, waiting for server's
  *   administrator to approve each file.
  *
  * - From the server to a client : The server send files from the 
  *   \e uploaded directory and the client retrieves it to a directory
  *   called \e downloaded/serverName.
  *
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
  *
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
  * in a xml files called \c data/saves/options.xml
  *
  * \htmlinclude xmlOptions.html
  * 
  * The root element is \c options. It can have one \c lastuse and
  * more  than opne \c snapshot childs. A snapshot is a graphic
  * configuration wich can be save and restore with the Launcher.
  *
  */

/** \page reg_test Regression test
  *
  * The line count is 
  * generated using David A Wheeler's 'SLOCCount'.
  *
  * The Mem column is the amount of memory used by the application on
  * Win32 system with the OpenGL renderer. Sys is set to OK if the
  * application can be compiles, linked and run on the given OS.
  *
  * The column called \e cc represents the Console's Count command result
  *
  * The column called \e ut represents the number of unit test (made 
  * with CppUnit)
  *
  * The column called \e ref is the number of pages of the Doxygen 
  * documentation in pdf format. (not computed before build 157)
  *
  * \htmlinclude regTest.html
  */

/** \page reg_test_pre150 Regression test (pre150)
  *
  * The line count is 
  * generated using David A Wheeler's 'SLOCCount'.
  *
  * The Mem column is the amount of memory used by the application on
  * Win32 system with the OpenGL renderer. Sys is set to OK if the
  * application can be compiles, linked and run on the given OS.
  *
  * The column called \e cc represents the Console's Count command result
  *
  * The column called \e ut represents the number of unit test 
  * (made with CppUnit)
  *
  * \htmlinclude regTest.pre150.html
  */


/** \page leb_versionning Libraries versionning
  *
  * The code is often build and compiled in a library, it avoid redondant
  * code and share it between client, server and over executables.
  *
  * To be able to link client only with dedicated versions of libraries, I
  * use the libtool versionning system (please see 
  * http://www.nondot.org/sabre/Mirrored/libtool-2.1a/libtool_6.html).
  *
  * Here are a set of rules to help you update your library version information:
  *
  * -# Start with version information of `0:0:0' for each libtool library.
  * -# Update the version information only immediately before a public 
  *    release of your software. More frequent updates are unnecessary, 
  *    and only guarantee that the current interface number gets larger 
  *    faster.
  * -# If the library source code has changed at all since the last update, 
  *    then increment revision (`c:r:a' becomes `c:r+1:a').
  * -# If any interfaces have been added, removed, or changed since the 
  *    last update, increment current, and set revision to 0.
  * -# If any interfaces have been added since the last public release, 
  *    then increment age.
  * -# If any interfaces have been removed since the last public release, 
  *    then set age to 0. 
  *
  * \note The libraries versionning was note managed before <em>RainbruRPG</em>
  *       version 0.0.5-174.
  *
  * \htmlinclude libVersionning.html
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
  * \htmlinclude bugList.html
  */

/** \page plugin_sec Plugin development guide
  *
  * \htmlinclude plugin_dev.html
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
  * \brief The global RainbruRPG namespace.
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
  * The namespace of the options system.
  *
  * To allow plugins set their own options in the LauncherOption dialog,
  * this namespace defines an OptionManager. It is a singleton you can
  * in the librainbrurpg-commons.so library.
  *
  * By a call to this singleton, you can add OptionPanel. The panel
  * must contains at least a OptionButton before you can add 
  * some OptionAttribute.
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
  *
  * \note An example of usage of this library is provided in the
  *       \c examples/ subdirectory. To enable its building, please
  *       pass the \c --enable-examples option to the configure script.
  *
  * \note This library is linked to rainbrurpg-common one. You must 
  *       include common/ headers and link you program to librainbrurpg-common
  *       to use terminalApi.
  *
  */

/** \namespace RainbruRPG::Network
  *
  * The global Network namespace.
  *
  * All the classes used for Network connexion.
  *
  */

/** \namespace RainbruRPG::Network::Ftp
  *
  * The FTP (File Trnsfer Protocol) namespace
  *
  * The class that belongs to this namespace are part of the FTP server or
  * the FTP client. FTP is used to synchronized data files between a server
  * and its clients.
  *
  */

/** \namespace RainbruRPG::Network::Ident
  *
  * The namespace used by the identification protocol
  *
  * The \c xident maintenance program and others wich are used for the
  * identification protocol. 
  *
  */

/** \namespace RainbruRPG::Trans
  *
  * The translation tools namespace
  *
  */

/** \namespace RainbruRPG::Server
  *
  * The server namespace
  *
  */

/** \namespace RainbruRPG::OgreGui
  *
  * \brief A graphical user interface over Ogre3D based on BetaGui.
  *
  * \section ogreGui_intro_sec Introduction
  *
  * OgreGuiToolkit is a toolkit providing a graphical user interface over
  * Ogre3D. It is based on BetaGui 
  * (http://www.ogre3d.org/wiki/index.php/BetaGUI). For this reason, some
  * classes are in the BetaGUI namespace.
  *
  * \section ogreGui_skinmanager_sec Skin manager
  *
  * An important class is \ref RainbruRPG::OgreGui::SkinManager "SkinManager"
  * which manages a vector of \ref RainbruRPG::OgreGui::Skin 
  * "Skin" objects.
  *
  * \section ogreGui_fontdebug_sec Debugging font
  * 
  * In the \c ogreGui/fontmanager.h file, a preprocessor macro called 
  * \c DEBUG_FONT_TEXTURE_QUAD is defined. If this macro is defined as 
  * \c true, the font called \c DEBUG_FONT_TTF_NAME will be applied
  * as ogre window background.
  *
  */

