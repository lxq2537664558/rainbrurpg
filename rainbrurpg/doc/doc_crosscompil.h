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

/** \file doc_crosscompil.h
  * A cross comilation documentation file
  *
  * This header does not contain code. It is only documentation for
  * namespaces and other members that cannot be documented in other places.
  *
  * \note Some macro from \c config.h are documented here because they
  *       use conditionnal compilation to avoid doxygen warnings. That's why
  *       we need to include the config.h file.
  *
  * Modifications :
  * - 08 oct 2008 : Starting implementation
  *
  */

/** \page win32_cross_compil Cross compilation to win32
  *
  * \section win32_intro Introduction
  *
  * Cross compilation is the ability to create executable for a platform 
  * other than the one on which the compiler is run. It is the way I choose
  * to provide a Win32 version of <em>RainbruRPG</em>.
  *
  * \sa http://en.wikipedia.org/wiki/Cross_compilation
  *
  * \section win32_current_line Current command line
  *
  * Here is current command-line I use for cross-compilation to win32 :
  * <code>
  * export CPPFLAGS="-I/usr/cross/include/ -mwindows" &&
  * export LDFLAGS=-L/usr/cross/lib/  &&
  * export OGRE_CFLAGS=-I/usr/cross/include/OGRE/ &&
  * ./configure --host=i586-mingw32msvc --prefix=/usr/cross/
  * </code>
  *
  * To create the shared library (.dll), I use a shell script called 
  * \c create_dll.sh but we do not need to call it. It is integrated
  * to the Makefile.am files. Please see common/Makefile.am for
  * integration example. To create the common/ shared library, please go to
  * the common/ directory and call <code>make dll</code>.
  *
  * \todo Test the rainbrurpg-common.dll shared library created by the 
  *       common/make.sh script.
  *
  * \warning When cross-compiling, the \c ./configure script does not test
  *          libraries or headers presence, the calls to the \c AC_CHECK_LIB
  *          and the \c AC_CHECK_HEADER m4 macros are deactivated in
  *          the \c acinclude.m4 file. I add manually the needed libraries
  *          and compiler/linker flags, so you need to set the base path
  *          for cross-compilation in \c configure.in as parameter of the
  *          \c RB_HANDLE_CROSS_COMPIL m4 macro call. You should set 
  *          \c /usr/cross if your filesystem contains the \c /usr/cross/lib
  *          and \c /usr/cross/include directories.
  *
  * Last modified 2008/10/08.
  *
  * \section win32_troubleshooting Troubleshooting
  *
  * I have many troubles when cross compiling to win32. Here is the
  * problems that occurs for each versions I have tried to cross compile.
  *
  * \subsection win32_troubles_186 v0.0.5-186
  *
  * The \c common/ correctly build but I cannot build the \c maincore
  * one.
  *
  * \subsubsection win32_troubles_186_errors The errors
  *
  * The following command line :
  * <code>
  * export CPPFLAGS="-I/usr/cross/include/ -mwindows" &&
  * export LDFLAGS=-L/usr/cross/lib/  &&
  * export OGRE_CFLAGS=-I/usr/cross/include/OGRE/ &&
  * ./configure --host=i586-mingw32msvc 
  * --prefix=/usr/cross/</code>
  *
  * Give many <code>`has not been declared'</code> errors in \c maincore/ :
  * <code>::iswblank, __gnu_cxx::wcstoull, __gnu_cxx::wcstoll, ::wcstoull
  * </code>
  * 
  * And some <code>`redefinition (or conflicting) of'</code> with these :
  * <code>struct timeval, typedef struct fd_set fd_set</code>
  *
  * \subsubsection win32_troubles_186_cause1 The possible cause
  *
  * The first object that causes these issues is <em>GameEngine.o</em>.
  * Here is the command-line generated to cross-compile it : 
  * <code>i586-mingw32msvc-g++ -DHAVE_CONFIG_H -I. -I. -I.. -I../common 
  * -I../ogreGui -I/usr/cross/include/OGRE/ -I/usr/local/include 
  * -I/usr/local/include/CEGUI -I/usr//include/OIS -I/usr//include 
  * -I/usr/include/sigc++-2.0 -I/usr/lib/sigc++-2.0/include 
  * -I/usr/cross/include/ -mwindows -mthreads -lstdc++ -g -O2 -MT 
  * gameengine.lo -MD -MP -MF .deps/gameengine.Tpo -c gameengine.cpp  
  * -DDLL_EXPORT -DPIC -o .libs/gameengine.o</code>
  *
  * The possible cause of the issie could be the 
  * <code>-I/usr/local/include</code> flag. It should reslt in this error, 
  * that occurs when cross compiling <em>GameEngine.o</em> :
  * <pre>
  * In file included from /usr//include/sys/select.h:46,
  *                 from /usr//include/sys/types.h:220,
  *                 from /usr//include/stdlib.h:320,
  *                 from /usr/lib/gcc/i586-mingw32msvc/4.2.1-sjlj/../../../../i586-mingw32msvc/include/objbase.h:12,
  *                 from /usr/lib/gcc/i586-mingw32msvc/4.2.1-sjlj/../../../../i586-mingw32msvc/include/ole2.h:9,
  *                 from /usr/lib/gcc/i586-mingw32msvc/4.2.1-sjlj/../../../../i586-mingw32msvc/include/windows.h:114,
  *                 from gameengine.cpp:29:
  * </pre>
  * 
  * \subsubsection win32_troubles_186_search Searching for a solution
  *
  * When searching for the include path in \c config.log, I found these :
  * <pre>
  * pkg_cv_OIS_CFLAGS='-I/usr//include/OIS -I/usr//include  '
  * pkg_cv_OIS_LIBS='-L/usr//lib -lOIS  '
  * </pre>
  *
  * \subsubsection win32_troubles_186_solving Solving the problem
  *
  * The content of the \c /usr/lib/pkgconfig/OIS.pc was :
  * <pre>
  * prefix=/usr/
  * exec_prefix=${prefix}
  * libdir=${exec_prefix}/lib
  * includedir=${prefix}/include
  *
  * Name: OIS
  * Description: Crossplatform C++ Input Framework
  * Version: 1.0.0
  * Libs: -L${libdir} -lOIS
  * Cflags: -I${includedir}/OIS -I${includedir}
  * </pre>
  *
  * The way to solve the problem I found is to set the \c prefix to
  * \c /usr/cross.
  *
  * \subsection win32_troubles_186_time_h v0.0.5-186 time.h issue
  *
  * I have had a problem at the very start of the compilation of common/ :
  * <pre>
  * error: '::clock_t' has not been declared
  * error: '::tm' has not been declared
  * error: '::clock' has not been declared
  * error: '::difftime' has not been declared
  * error: '::mktime'
  * </pre>
  * and so on...
  *
  * This problem comes when I include a standard header (iostream that 
  * include ctime and time.h). Here is the solution :
  * - many standard header use \c time.h;
  * - the enet library defines its own time.h
  * - when setting \c -L/path/to/enet/ it include enet's \c time.h instead of 
  *   the system's one
  * 
  * The solution : 
  * - setting a \c -L/path/to/ flag at compile time;
  * - using a scoped \c include <enet/enet.h> in the code.
  *
  * \subsection win32_troubles_186_exesize v0.0.5-186 Client size
  *
  * \subsubsection win32_troubles_186_exesize_exesize Client executable size
  *
  * I cross-compile the client but its size in very big : 310Mo. With
  * a custom script trying to emulate \c ldd for mingw32 I found that
  * client's executable was linked with the following libraries :
  * <pre>
  * rainbrurpg.exe	-> ./rainbrurpg.exe
  * freetype6.dll	-> not found
  * fox.dll	-> not found
  * ois.dll	-> not found
  * boost-filesystem.dll	-> not found
  * libcurl-4.dll	-> not found
  * freeimage.dll	-> not found
  * libsigc-2.0-0.dll	-> not found
  * libzzip-0-13.dll	-> not found
  * kernel32.dll	-> not found
  * msvcrt.dll	-> not found
  * user32.dll	-> not found
  * </pre>
  *
  * I think the libraries that are not in this list (OgreMain, common, 
  * ogregui...)
  * are statically compiled.
  *
  * In the g++ command line ther is some lib*.a :
  *
  * <code>i586-mingw32msvc-g++ -g -O2 -o rainbrurpg.exe exampleframelistener.o gsconnection.o gscreateaccount.o gsmainmenu.o gsmenubase.o gsserverlist.o gsupdatedatafiles.o guiframelistener.o guimanager.o launcher.o launcheroptions.o main.o languageselector.o  -L/home/mouse/programmation/rainbrurpg/common/.libs -L/home/mouse/programmation/rainbrurpg/maincore/.libs -L/usr/cross/lib -L/home/mouse/programmation/rainbrurpg/common -L/home/mouse/programmation/rainbrurpg/maincore -L/home/mouse/programmation/rainbrurpg/ogreGui <b>/home/mouse/programmation/rainbrurpg/maincore/.libs/librainbrurpg-core.a /home/mouse/programmation/rainbrurpg/common/.libs/librainbrurpg-common.a</b> -lcurl <b>/home/mouse/programmation/rainbrurpg/ogreGui/.libs/librainbrurpg-ogregui.a</b> -lFOX-1.6 -lOgreMain -lfreeimage -lzzip -lfreetype6 -lOIS -lboost_filesystem -lboost_thread -lenet -lglib-2.0 -lsigc-2.0 -lgd -lgnet-2.0
</code>
  *
  * \subsubsection win32_troubles_186_exesize_core Core library size
  *
  * In the same way, I manage to create the maincore/ library with the
  * create_dll shell script but its size is 192Mo.
  *
  */
