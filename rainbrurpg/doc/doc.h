/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file doc.h
  * A documentation file
  *
  * This header does not contain code. It is only documentation for
  * namespaces and other members that cannot be documented in other places.
  *
  * \note Some macro from \c config.h are documented here because they
  *       use conditionnal compilation to avoid doxygen warnings. That's why
  *       we need to include the config.h file.
  *
  * Modifications :
  * - 02 feb 2009 : Add publicserver.png to the latex documentation
  * - 09 jan 2008 : Add some precisions on regression tests 'line' value.
  * - 03 dec 2008 : Fix some Doxygen warning when configure never complete.
  * - 08 oct 2008 : Cross compilation section moved to doc_crosscompil.h
  * - 07 oct 2008 : Cross compilation section added.
  * - 13 aug 2008 : Single file documentation.
  *
  */

// Mandatory if we want to use conditionnal compilation
#include "../config.h"

/** \mainpage Main Page
  *
  * \section intro_sec Introduction
  *
  * %RainbruRPG is a 3D Role Playing Game project. It uses FOX toolkit,
  * Ogre and others libaries. It is not currently a playable game. it is
  * under active development.
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
  * \section pdf_latex_err pdflatex error
  *
  * To get a PDF file from the latex output, I use the pdflatex program.
  * It can produce an error telling <code>TeX capacity exceeded, sorry 
  * [save size=5000].</code>.
  *
  * To fix this error, please edit the \c /etc/texmf/texmf.cnf file and
  * set \c save_size to a greater value (32000 seems to work).
  *
  */

/** \page client_server The client/Server structure
  *
  * This game is client/server oriented. This means that at least 2
  * application are made. The client is the game, to be able to be
  * played, it must be connected to a server.
  *
  * The server can be private or public. If you made a private server,
  * no one can be connected to it from the internet (the public server
  * list does not contain the name of your server). A public server 
  * allows anyone to connect to. 
  *
  * The following image shows how the identification process works.
  * The administration website is shown because it is used in the
  * identification process to verify password and black list.
  *
  * The client's source code is contained in the client/ directory but it
  * also uses the maincore/ and OgreGui/ libraries. The server is 
  * implemented in the server/ directory but it also uses the
  * design/ library. Both client and server uses the common/ library.
  *
  * \image html publicserver.png
  * \image latex publicserver.png
  *
  *
  */


/** \page xoops_module Server/Player information in website
  *
  * To provide a real-time information in website, a xoops module must
  * be created. It uses a XML parser to read the XML files and a
  * TCP/IP client to ask more information to the servers.
  *
  * The goal is to provides a message : "Actually, ??? players have an
  * account. ??? players are playing in ? actives servers."
  *
  * \sa \ref site_side "Website side files" for more informations on 
  *     how to retrieve information from the administration site.
  *
  * \note This module is broken because my actual webspace provider
  *       for administration site and Sourceforge are differents.
  *       My web homepage, provided by Sourceforge cannot get
  *       administration site informations from the administration site 
  *       because of security reasons.
  *
  * \note The code of this module is not released because it is broken 
  *       and it is not used anymore.
  *
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
  * The website files are retrieved with subclasses of 
  * \ref RainbruRPG::Network::Ident::CurlFileToXml "CurlFileToXml". These
  * class are usually named xml*. By example, please see
  * \ref RainbruRPG::Network::Ident::xmlAccountList "xmlAccountList" 
  * documentation to know how to retrieve players' account informations.
  *
  * To modify informations on these files, you must submit form with
  * subclasses of \ref RainbruRPG::Network::Ident::CurlSubmitForm
  * "CurlSubmitForm". Please see 
  * \ref RainbruRPG::Network::Ident::CurlAccountAdd "CurlAccountAdd" to
  * add an account.
  *
  * \section site_info website information
  *
  * A \ref xoops_module "xoops module" has been added to the site to show 
  * a real-time information on the online servers.
  *
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
  * The \e line count is 
  * generated using David A Wheeler's 'SLOCCount'. This value must be
  * computed on RainbruRPG and adminsite after a 'make distclean' command.
  *
  * The \e mem column is the amount of memory used by the application on
  * Win32 system with the OpenGL renderer. 
  * 
  * The \e sys is set to OK if the
  * application can be run on the given OS. The compilation can be
  * made on another system (cross-compilation).
  *
  * The column called \e cc represents the Console's Count command result
  *
  * The column called \e ut represents the number of unit test (made 
  * with CppUnit).
  *
  * The column called \e ref is the number of pages of the Doxygen 
  * documentation in pdf format. (not computed before build 157)
  *
  * The column called \e CL is the size of the ChangeLog in line number.
  * It was not computed before build 183 because the ChangeLog was not 
  * GNU coding standard compliant.
  *
  * The column called \e PoMsg is the number of ready-to-be-translated
  * strings. There are listed in the \e po/RainbruRPG.po. It was not
  * computed before build 191.
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


/** \page lib_versionning Libraries versionning
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
  * are in gray, the other colors are applied to solved bugs.
  *
  * The bugs are ordered, the num is on the \b # column. The sys is
  * here to tell if this bug is in GNU/Linux, Win32 or both.
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
  * GameEngine/GameState mechanism : The GameEngine can have several
  * GameState-based class (call gs????). Only one GameState can be on
  * at a time and we can switch beetween them, pause and resume a GameState.
  *
  */

/** \namespace RainbruRPG::Gui
  *
  * The namespace of the Graphic User Interface 
  *
  * In this namespace are grouped the FOX and OgreGUI based
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
  * The namespace of the roleplay concepts
  *
  * This namespace will contains the concepts of the RPG roleplay part of
  * the game. All concepts that are not part of the player (contained in
  * \ref RainbruRPG::Concept::Player) or the AI (contained in
  * \ref RainbruRPG::Concept::AI) should be here. These concepts can be about,
  * but are not restricted to :
  * - the world : concepts can be about the world cut off;
  * - the elementals : the crafting concepts ans all other concepts about
  *   fire, earth, etc ...
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


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//              CONFIG.H DOCUMENTATION
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


/** \file config.h
  *
  * Generated file from config.h.in by configure
  *
  * The \c config.h file intend to define system dependant values
  * as preprocessor macro. \c config.h.in is generated by autoheader from 
  * \c configure.in and \c ./configure generates \c config.h from 
  * \c config.h.in.
  *
  * \note As this file is generated, members documentation is in the doc/doc.h 
  *       file.
  *
  */

// Avoid doxygen complains about 'unknown define'
#ifdef BUILD_EDITOR
/** \def BUILD_EDITOR
  *
  * Defines if the editor is built.
  * 
  * This value is set to 1 (build the editor) if the \c --enable-editor
  * argument is passed to the /c configure script.
  *
  */
#endif // BUILD_EDITOR

// The BUILD_LIB_DESIGN macro can be undefined if configure call never complete
#ifdef BUILD_LIB_DESIGN
/** \def BUILD_LIB_DESIGN
  * 
  * Defines if the \c design library must be built. 
  *
  * This value cannot be change through a \c configure option, it takes 
  * it value according to the program parts you choose to build (editor, 
  * server...).
  *
  */
#endif // BUILD_LIB_DESIGN

// Avoid doxygen complains about 'unknown define'
#ifdef  BUILD_SERVER
/** \def BUILD_SERVER
  *
  * Defines if the server is built.
  *
  * This value is set to 1 (build the server) if the \c --enable-server
  * argument is passed to the /c configure script.
  *
  *
  */
#endif //  BUILD_SERVER

// The BUILD_RELEASE macro can be undefined if configure call never complete
#ifdef BUILD_RELEASE
/** \def BUILD_RELEASE
  *
  * Defines the build release number as a string.
  *
  * The version pilicy is <em>x.y.z-w</em>. The <em>w</em> number is the build
  * release, I will never reset it.
  *
  */
#endif // BUILD_RELEASE

// The HAVE_ALLOCA macro can be undefined if configure call never complete
#ifdef HAVE_ALLOCA
/** \def HAVE_ALLOCA
  *
  * Define to 1 if you have `alloca', as a function or macro.
  *
  * \c alloca is a function, generally defined in \c stdlib.h, used to 
  * allocate memory. For more informations and an example please visit
  * http://www.gnu.org/software/libtool/manual/libc/Variable-Size-Automatic.html#Variable-Size-Automatic
  *
  */
#endif // HAVE_ALLOCA

#ifdef HAVE_ALLOCA_H
/** \def HAVE_ALLOCA_H
  *
  * Define to 1 if you have \c <alloca.h> and it should be used
  *
  * Some platforms define the \c alloca function in \c alloca.h instead
  * of \c stdlib.h
  *
  */
#endif // HAVE_ALLOCA_H

// The HAVE_DIRENT_H macro can be undefined if configure call never complete
#ifdef HAVE_DIRENT_H
/** \def HAVE_DIRENT_H
  *
  * Define to 1 if you have the \c <dirent.h> header file, and it defines 
  * \c DIR
  *
  * \c dirent.h is the header in the C POSIX library that contains 
  * constructs that facilitate directory traversing. 
  *
  */
#endif // HAVE_DIRENT_H

#ifdef HAVE_DLFCN_H
/** \def HAVE_DLFCN_H
  *
  * Define to 1 if you have the <dlfcn.h> header file.
  *
  * The \c <dlfcn.h> library contains four functions for loading a dynamic 
  * library into a core program, accessing a library's components (known 
  * as symbols), unloading a library and error handling. 
  *
  */
#endif // HAVE_DLFCN_H

// The HAVE_FCNTL_H macro can be undefined if configure call never complete
#ifdef HAVE_FCNTL_H
/** \def HAVE_FCNTL_H
  *
  * Defines file control options. 
  *
  * The \c fcntl.h file defines the values that can be specified for 
  * the Command and Argument parameters of the \c fcntl subroutine and 
  * for the Oflag parameter of the \c open subroutine. The file-status 
  * flags of an open file are also described. 
  */
#endif // HAVE_FCNTL_H

// The HAVE_INTTYPES_H macro can be undefined if configure call never complete
#ifdef HAVE_INTTYPES_H
/** \def HAVE_INTTYPES_H
  *
  * Define to 1 if you have the \c <inttypes.h> header file.
  *
  * The \c inttypes.h file is a C header file that is part of the C standard 
  * library and API. It includes the \c stdint.h header. It defines a number 
  * of macros for use with the \c printf and \c scanf family of functions, 
  * as well as functions for working with the \c intmax_t type.
  *
  */
#endif // HAVE_INTTYPES_H

#ifdef HAVE_LIBBOOST_FILESYSTEM
/** \def HAVE_LIBBOOST_FILESYSTEM
  * 
  * Define to 1 if you have the `boost_filesystem' library.
  *
  * The Boost.Filesystem library provides portable facilities to query 
  * and manipulate paths, files, and directories.
  *
  */
#endif // HAVE_LIBBOOST_FILESYSTEM

#ifdef HAVE_LIBBOOST_THREAD
/** \def HAVE_LIBBOOST_THREAD
  *
  * Define to 1 if you have the `boost_thread' library
  *
  * Boost.Thread enables the use of multiple threads of execution with 
  * shared data in portable C++ code. It provides classes and functions 
  * for managing the threads themselves, along with others for synchronizing 
  * data between the threads or providing separate copies of data specific 
  * to individual threads. 
  *
  */
#endif // HAVE_LIBBOOST_THREAD

#ifdef HAVE_LIBENET
/** \def HAVE_LIBENET
  *
  * Define to 1 if you have the `enet' library.
  *
  * ENet's purpose is to provide a relatively thin, simple and robust 
  * network communication layer on top of UDP (User Datagram Protocol). 
  * The primary feature it provides is optional reliable, in-order 
  * delivery of packets.
  *
  */
#endif // HAVE_LIBENET

#ifdef HAVE_LIBFOX_1_6
/** \def HAVE_LIBFOX_1_6
  *
  *  Define to 1 if you have the `FOX-1.6' library.
  *
  * FOX is a library used to create Graphic User Interface. Please visit
  * http://www.fox-toolkit.org/ for more informations.
  *
  */
#endif // HAVE_LIBFOX_1_6

#ifdef HAVE_LIBGD
/** \def HAVE_LIBGD
  *
  * Define to 1 if you have the `gd' library.
  *
  * GD is a library for the dynamic creation of images. It is used to create 
  * graph and charts.
  *
  */
#endif // HAVE_LIBGD

#ifdef HAVE_LIBGLIB_2_0
/** \def HAVE_LIBGLIB_2_0
  *
  * Define to 1 if you have the `glib-2.0' library.
  *
  * GLib is a cross-platform library notably containing non-GUI features
  * (used for endianness handling).
  * 
  *
  */
#endif // HAVE_LIBGLIB_2_0

#ifdef HAVE_LIBGNET_2_0
/** \def HAVE_LIBGNET_2_0
  *
  * Define to 1 if you have the `gnet-2.0' library.
  *
  * GNet is a simple network library.
  *
  */
#endif // HAVE_LIBGNET_2_0

#ifdef HAVE_LIBJPEG
/** \def HAVE_LIBJPEG
  * 
  * Define to 1 if you have the `jpeg' library.
  *
  */
#endif // HAVE_LIBJPEG

// Avoid doxygen complains about 'unknown define'
#ifdef  HAVE_LIBMAGIC
/** \def HAVE_LIBMAGIC
  *
  * Define to 1 if you have the `magic' library.
  *
  * LibMagic is a library that can classify files according to magic 
  * number tests.
  *
  */
#endif //  HAVE_LIBMAGIC

// Avoid doxygen complains about 'unknown define'
#ifdef  HAVE_LIBQT3SUPPORT
/** \def HAVE_LIBQT3SUPPORT
  *
  * Define to 1 if you have the `Qt3Support' library.
  *
  * This library is part od Qt4. It adds support for Qt3 classes.
  *
  */
#endif //  HAVE_LIBQT3SUPPORT

// Avoid doxygen complains about 'unknown define'
#ifdef  HAVE_LIBQTCORE
/** \def HAVE_LIBQTCORE
  *
  * Define to 1 if you have the `QtCore' library.
  *
  * QtCore is the Qt4 part defining non-gui objects.
  *
  */
#endif //  HAVE_LIBQTCORE

// Avoid doxygen complains about 'unknown define'
#ifdef  HAVE_LIBQTGUI
/** \def HAVE_LIBQTGUI
  *
  * Define to 1 if you have the `QtGui' library.
  *
  * QtGui defines the GUI part of Qt4.
  *
  */
#endif //  HAVE_LIBQTGUI

// Avoid doxygen complains about 'unknown define'
#ifdef  HAVE_LIBQTNETWORK
/** \def HAVE_LIBQTNETWORK
  *
  * Define to 1 if you have the `QtNetwork' library.
  *
  * QtNetwork defines the network related part of Qt4.
  *
  */
#endif //  HAVE_LIBQTNETWORK

#ifdef HAVE_LIBSIGC_2_0
/** \def HAVE_LIBSIGC_2_0
  *
  * Define to 1 if you have the `sigc-2.0' library
  *
  * libsigc++ implements a full callback system for use in widget libraries, 
  * abstract interfaces, and general programming.
  *
  */
#endif // HAVE_LIBSIGC_2_0

// The HAVE_LOCALE_H macro can be undefined if configure call never complete
#ifdef HAVE_LOCALE_H
/** \def HAVE_LOCALE_H
  *
  * Define to 1 if you have the <locale.h> header file.
  *
  * \c locale.h defines structures and macros needs to handle currency and
  * monetary.
  *
  */
#endif // HAVE_LOCALE_H

// The HAVE_MEMORY_H macro can be undefined if configure call never complete
#ifdef HAVE_MEMORY_H
/** \def HAVE_MEMORY_H
  *
  * Define to 1 if you have the <memory.h> header file.
  *
  */
#endif // HAVE_MEMORY_H

#ifdef HAVE_MKFIFO
/** \def HAVE_MKFIFO
  *
  * Define to 1 if you have the `mkfifo' function.
  *
  * the \c mkfifo function provides a way to create FIFO files. Please
  * see http://en.wikipedia.org/wiki/FIFO .
  *
  */
#endif // HAVE_MKFIFO

// The HAVE_STDINT_H macro can be undefined if configure call never complete
#ifdef HAVE_STDINT_H
/** \def HAVE_STDINT_H
  *
  * Define to 1 if you have the <stdint.h> header file.
  *
  * \c stdint.h is a header in the C standard library to allow programmers 
  * to write more portable code by providing a set of typedefs that specify 
  * exact-width integer types, together with the defined minimum and maximum 
  * allowable values for each type, using macros.
  *
  */
#endif // HAVE_STDINT_H

// The HAVE_STDLIB_H macro can be undefined if configure call never complete
#ifdef HAVE_STDLIB_H
/** \def HAVE_STDLIB_H
  *
  * Define to 1 if you have the <stdlib.h> header file.
  *
  * \c stdlib is the header which includes functions involving memory 
  * allocation, process control, conversion and others.
  *
  */
#endif // HAVE_STDLIB_H

// The HAVE_STRINGS_H macro can be undefined if configure call never complete
#ifdef HAVE_STRINGS_H
/** \def HAVE_STRINGS_H
  *
  * Define to 1 if you have the <strings.h> header file.
  *
  * \c strings.h is a headers file which defines a set of function and/or
  * macro providing string operations.
  *
  */
#endif // HAVE_STRINGS_H

// The HAVE_STRING_H macro can be undefined if configure call never complete
#ifdef HAVE_STRING_H
/** \def HAVE_STRING_H
  *
  * Define to 1 if you have the <string.h> header file.
  *
  * \c string.h is the header in the C standard library which contains 
  * macro definitions, constants, and declarations of functions and types 
  * used not only for string handling but also various memory handling 
  * functions.
  *
  */
#endif // HAVE_STRING_H

#ifdef HAVE_STRUCT_STAT_ST_BLOCKS
/** \def HAVE_STRUCT_STAT_ST_BLOCKS
  *
  * Define to 1 if `st_blocks' is member of `struct stat'.
  *
  * The \c stat structure is used to retrieve informations about the 
  * status of a file. Its member \c st_blocks is the number of allocated 
  * blocks.
  *
  */
#endif // HAVE_STRUCT_STAT_ST_BLOCKS

// HAVE_STRUCT_UTIMBUF macro can be undefined if configure call never complete
#ifdef HAVE_STRUCT_UTIMBUF
/** \def HAVE_STRUCT_UTIMBUF
  *
  * Define if struct utimbuf is declared.
  * 
  * Usually, the structure \c utimbuf is declared in <utime.h>. Some systems
  * have utime.h but don't declare the struct anywhere.
  *
  */
#endif // HAVE_STRUCT_UTIMBUF

#ifdef HAVE_ST_BLOCKS
/** \def HAVE_ST_BLOCKS
  *
  * Define to 1 if your `struct stat' has `st_blocks'. 
  *
  * \warning Deprecated, use \ref HAVE_STRUCT_STAT_ST_BLOCKS instead.
  *
  */
#endif // HAVE_ST_BLOCKS

// The HAVE_SYS_PARAM_H macro can be undefined if configure call never complete
#ifdef HAVE_SYS_PARAM_H
/** \def HAVE_SYS_PARAM_H
  *
  * Define to 1 if you have the <sys/param.h> header file.
  *
  * The \c <sys/param.h> header file declares some utility macros as MIN, MAX,
  * bit map related or rounding/counting macros.
  *
  */
#endif // HAVE_SYS_PARAM_H

// The HAVE_SYS_STAT_H macro can be undefined if configure call never complete
#ifdef HAVE_SYS_STAT_H
/** \def HAVE_SYS_STAT_H
  *
  * Define to 1 if you have the <sys/stat.h> header file.
  *
  * The \c stat.h file is a standard POSIX header defining file 
  * characteristics.
  *
  */
#endif // HAVE_SYS_STAT_H

#ifdef HAVE_SYS_SYSMACROS_H
/** \def HAVE_SYS_SYSMACROS_H
  *
  * Define to 1 if you have the <sys/sysmacros.h> header file.
  *
  * The \c <sys/sysmacros.h> defines the macros \c major(), \c minor() and 
  * \c makedev().
  *
  */
#endif // HAVE_SYS_SYSMACROS_H

#ifdef HAVE_LIBSLANG
/** \def HAVE_LIBSLANG
  *
  * Define to 1 if you have the SLang library installed
  *
  */
#endif // !HAVE_LIBSLANG

// The HAVE_SYS_TIME_H macro can be undefined if configure call never complete
#ifdef HAVE_SYS_TIME_H
/** \def HAVE_SYS_TIME_H
  *
  * Define to 1 if you have the <sys/time.h> header file.
  *
  * The \c <sys/time.h> header declares macros used to handle timeval and
  * timespec.
  *
  */
#endif // HAVE_SYS_TIME_H

// The HAVE_SYS_TYPES_H macro can be undefined if configure call never complete
#ifdef HAVE_SYS_TYPES_H
/** \def HAVE_SYS_TYPES_H
  *
  * Define to 1 if you have the <sys/types.h> header file.
  *
  * The \c sys/types.h, from the POSIX standard, defines primitive system
  * data types.
  *
  */
#endif // HAVE_SYS_TYPES_H

// The HAVE_TIME_H macro can be undefined if configure call never complete
#ifdef HAVE_TIME_H
/** \def HAVE_TIME_H
  *
  * Define to 1 if you have the <time.h> header file.
  *
  * This header file defines some ISO C99 standard date and time types, macros
  * and functions.
  *
  */
#endif // HAVE_TIME_H

// The HAVE_UNISTD_H macro can be undefined if configure call never complete
#ifdef HAVE_UNISTD_H
/** \def HAVE_UNISTD_H
  *
  * Define to 1 if you have the <unistd.h> header file.
  *
  * The \c unistd.h header file declares some POSIX standard compliant 
  * symbolic constants. These constants may be used to determine what 
  * facilities are present at compile time. For example, functions like 
  * sleep() (making the process sleep <i>n</i> seconds) or chdir() are declared
  * here.
  *
  */
#endif // HAVE_UNISTD_H

// The HAVE_UTIME_H macro can be undefined if configure call never complete
#ifdef HAVE_UTIME_H
/** \def HAVE_UTIME_H
  *
  * Define to 1 if you have the <utime.h> header file.
  *
  * The header file \c utime.h is compliant with the POSIX standard. It
  * defines the structure and a function needed to set file access and 
  * modification times.
  *
  */
#endif // HAVE_UTIME_H

// The PACKAGE macro can be undefined if configure call never complete
#ifdef PACKAGE
/** \def PACKAGE
  *
  * Defines the name of the package
  *
  * This value should always be \b RainbruRPG.
  *
  */
#endif PACKAGE

// PACKAGE_BUGREPORT macro can be undefined if configure call never complete
#ifdef PACKAGE_BUGREPORT
/** \def PACKAGE_BUGREPORT
  *
  * Define to the address where bug reports for this package should be sent.
  *
  * \todo Test if this value is correct. It should be set from the call
  *       to AC_INIT in the configure.in file.
  *
  */
#endif // PACKAGE_BUGREPORT

// PACKAGE_NAME macro can be undefined if configure call never complete
#ifdef PACKAGE_NAME
/** \def PACKAGE_NAME
  *
  * Define to the full name of this package.
  *
  */
#endif // PACKAGE_STRING

// PACKAGE_STRING macro can be undefined if configure call never complete
#ifdef PACKAGE_STRING
/** \def PACKAGE_STRING
  *
  * Define to the full name and version of this package.
  *
  */
#endif // PACKAGE_STRING

// PACKAGE_TARNAME macro can be undefined if configure call never complete
#ifdef PACKAGE_TARNAME
/** \def PACKAGE_TARNAME
  *
  * Define to the one symbol short name of this package.
  *
  */
#endif // PACKAGE_TARNAME

// PACKAGE_VERSION macro can be undefined if configure call never complete
#ifdef PACKAGE_VERSION
/** \def PACKAGE_VERSION
  *
  * Define to the version of this package.
  *
  */
#endif // PACKAGE_VERSION

#ifdef RAINBRU_RPG_DEBUG
/** \def RAINBRU_RPG_DEBUG
  *
  * Activate local website administration and intensive informative logging
  * informations.
  *
  * It is a \c configure script option, enabled with the argument 
  * \c --enable-debug. This has several effects :
  * - The logger will print all informations, in production mode,
  *   it only print warnings and errors;
  * - The server and client will attempt to contact a local administration
  *   site instead of the official inline one.
  *
  */
#endif // RAINBRU_RPG_DEBUG

#ifdef RB_DISABLE_OGRE_DEPREC_WARN
/** \def RB_DISABLE_OGRE_DEPREC_WARN
  * 
  * Defines if we must disable the deprecated warnings due to Ogre 
  * inclusion of std headers.
  *
  * This option is enable by passing the \c --enable-Wno-stddep-ogre to the
  * \c configure script. It is provided to avoid many warnings due to Ogre3D.
  * It appears that Ogre uses deprecated standard headers. The way I use to
  * temporally disabled is explained in the \file ogreimport.h
  *
  */
#endif // RB_DISABLE_OGRE_DEPREC_WARN

// STDC_HEADERS macro can be undefined if configure call never complete
#ifdef STDC_HEADERS
/** \def STDC_HEADERS
  *
  * Define to 1 if you have the ANSI C header files.
  *
  *
  */
#endif // STDC_HEADERS

// TIME_WITH_SYS_TIME macro can be undefined if configure call never complete
#ifdef TIME_WITH_SYS_TIME
/** \def TIME_WITH_SYS_TIME
  *
  * Define to 1 if you can safely include both <sys/time.h> and <time.h>.
  *
  *
  */
#endif // TIME_WITH_SYS_TIME

// USER_INSTALL_PREFIX macro can be undefined if configure call never complete
#ifdef USER_INSTALL_PREFIX
/** \def USER_INSTALL_PREFIX
  *
  * The directory installation prefix. This value is needed to locate the
  * datafiles.
  *
  * Often, this value will be \c /usr/local but it can be different if you
  * use the \c --prefix argument of the \c ./configure script.
  *
  */
#endif // USER_INSTALL_PREFIX

// The VERSION macro can be undefined if configure call never complete
#ifdef VERSION
/** \def VERSION
  * Version number of package
  *
  * Defines the RainbruRPG version. To get the complete release
  * version use : VERSION-BUILD_RELEASE.
  *
  * \todo This value seems to conflict with \ref PACKAGE_VERSION which is
  *       always equal to 0. Should we use it instead ?
  *
  */
#endif // VERSION

#ifdef RB_MULTICOLUMNLIST_TEST
/** \def RB_MULTICOLUMNLIST_TEST
  * A MultiColumnList widget test
  *
  * Defines if we should create a test widget.
  *
  */
#endif //RB_MULTICOLUMNLIST_TEST

#ifdef CLOSEDIR_VOID
/** \def CLOSEDIR_VOID
  * Defined to 1 if the `closedir' function returns void instead of `int'
  *
  *
  */
#endif // CLOSEDIR_VOID

#ifdef BUILD_SERVER
/** \file server/resources.cpp
  * A file generated by Qt that contains graphics data
  *
  * \note This file is generated and its documentation and the
  *       documentation of all its members are in doc/doc.h
  *
  */
/** \var qt_resource_data
  * The array that contains pixels data
  *
  * The pixels data of all images are in this array.
  *
  */
/** \var qt_resource_struct
  * Extra informations about images
  *
  * This array contains extra informations about the images stored in 
  * \ref qt_resource_data.
  *
  */
/** \var qt_resource_name
  * May contains resources names
  *
  */
/** \fn qRegisterResourceData(int, const unsigned char *, 
  *     const unsigned char *, const unsigned char *)
  * Register the datas contains in this file
  * 
  */
/** \fn qUnregisterResourceData(int, const unsigned char *, 
  *     const unsigned char *, const unsigned char *)
  * Unregister the given resources
  * 
  */
/** \fn qInitResources()
  * Initializes the given resources
  * 
  */
/** \fn Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources)) 
  *     int QT_MANGLE_NAMESPACE(qCleanupResources) 
  * An internal Qt function
  *
  */
#endif // BUILD_SERVER

// DEFINED BY INTL IN config.h
#ifdef glthread_once_singlethreaded
/** \def glthread_once_singlethreaded
  * Defined to \c libintl_once_singlethreaded by libintl autoconf functions.
  *
  */
#endif // glthread_once_singlethreaded

#ifdef glthread_once_call
/** \def glthread_once_call
  * Defined to \c libintl_once_call by libintl autoconf functions.
  *
  */
#endif // glthread_once_call

#ifdef glthread_once
/** \def glthread_once
  * Defined to \c libintl_once by libintl autoconf functions.
  *
  */
#endif // glthread_once

#ifdef glthread_recursive_lock_destroy
/** \def glthread_recursive_lock_destroy
  * Defined to \c libintl_recursive_lock_destroy by libintl autoconf functions.
  *
  */
#endif // glthread_recursive_lock_destroy

#ifdef glthread_recursive_lock_unlock
/** \def glthread_recursive_lock_unlock
  * Defined to \c libintl_recursive_lock_unlock by libintl autoconf functions.
  *
  */
#endif // glthread_recursive_lock_unlock

#ifdef glthread_recursive_lock_lock
/** \def glthread_recursive_lock_lock
  * Defined to \c libintl_recursive_lock_lock by libintl autoconf functions.
  *
  */
#endif // glthread_recursive_lock_lock

#ifdef glthread_recursive_lock_init
/** \def glthread_recursive_lock_init
  * Defined to \c libintl_recursive_lock_init by libintl autoconf functions.
  *
  */
#endif // glthread_recursive_lock_init

#ifdef glthread_rwlock_destroy
/** \def glthread_rwlock_destroy
  * Defined to \c libintl_rwlock_destroy by libintl autoconf functions.
  *
  */
#endif // glthread_rwlock_destroy

#ifdef glthread_rwlock_unlock
/** \def glthread_rwlock_unlock
  * Defined to \c libintl_rwlock_unlock by libintl autoconf functions.
  *
  */
#endif // glthread_rwlock_unlock

#ifdef glthread_rwlock_wrlock
/** \def glthread_rwlock_wrlock
  * Defined to \c libintl_rwlock_wrlock by libintl autoconf functions.
  *
  */
#endif // glthread_rwlock_wrlock

#ifdef glthread_rwlock_rdlock
/** \def glthread_rwlock_rdlock
  * Defined to \c libintl_rwlock_rdlock by libintl autoconf functions.
  *
  */
#endif // glthread_rwlock_rdlock

#ifdef glthread_rwlock_init
/** \def glthread_rwlock_init
  * Defined to \c libintl_rwlock_init by libintl autoconf functions.
  *
  */
#endif // glthread_rwlock_init

#ifdef glthread_lock_destroy
/** \def glthread_lock_destroy
  * Defined to \c libintl_lock_destroy by libintl autoconf functions.
  *
  */
#endif // glthread_lock_destroy

#ifdef glthread_lock_unlock
/** \def glthread_lock_unlock
  * Defined to \c libintl_lock_unlock by libintl autoconf functions.
  *
  */
#endif // glthread_lock_unlock

#ifdef glthread_lock_lock
/** \def glthread_lock_lock
  * Defined to \c libintl_lock_lock by libintl autoconf functions.
  *
  */
#endif // glthread_lock_lock

#ifdef glthread_lock_init
/** \def glthread_lock_init
  * Defined to \c libintl_lock_init by libintl autoconf functions.
  *
  */
#endif // glthread_lock_init

#ifdef glthread_in_use
/** \def glthread_in_use
  * Defined to \c libintl_thread_in_use by libintl autoconf functions.
  *
  */
#endif // glthread_in_use

#ifdef __libc_lock_unlock_recursive
/** \def __libc_lock_unlock_recursive
  * Defined to \c gl_recursive_lock_unlock by libintl autoconf functions.
  *
  */
#endif // __libc_lock_unlock_recursive

#ifdef __libc_lock_lock_recursive
/** \def __libc_lock_lock_recursive
  * Defined to \c gl_recursive_lock_lock by libintl autoconf functions.
  *
  */
#endif // __libc_lock_lock_recursive

#ifdef __libc_lock_init_recursive
/** \def __libc_lock_init_recursive
  * Defined to \c gl_recursive_lock_init by libintl autoconf functions.
  *
  */
#endif // __libc_lock_init_recursive
