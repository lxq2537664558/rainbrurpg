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

/** \file doc_bug27.h
  * A bug documentation file
  *
  * This header does not contain code. It is only a documentation for
  * a bug.
  *
  * Modifications :
  * - 16 feb 2009 : reopened
  * - 01 feb 2009 : Closed
  * - 04 nov 2008 : Starting implementation
  *
  */

/** \page bug27_details Details bug #27
  *
  * \section bug27_identification Identification
  * \subsection bug27_description Description
  *
  * Local test doesn't work, a segmentation fault occurs.
  *
  * \subsection bug27_reproduce How to reproduce
  *
  * Simply click on the <em>Local test</em> button in the main menu screen.
  * The segfault does not occurs every time. Sometimes it failed, sometimes 
  * it works.
  *
  * \subsection bug27_01feb2009 01 feb 2009 update
  *
  * I decided to close this bug. I didn't fix it but I can't reproduce it.
  * However, I keep this detail page for further references.
  *
  * \subsection bug27_06feb2009 16 feb 2009 update
  *
  * The bug is reopened. 
  * <pre>
  * #0  0x0000000000000000 in ?? ()
  * #1  0x00007f84f7ee173d in Ogre::Node::_updateFromParent ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #2  0x00007f84f7ee27b9 in Ogre::Node::translate ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #3  0x00007f84f7dfd192 in Ogre::Camera::rotate ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #4  0x00007f84f7dfd253 in Ogre::Camera::yaw ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #5  0x000000000040c3c6 in RainbruRPG::Core::ExampleFrameListener::moveCamera (
  *     this=0x2b70d70) at exampleframelistener.cpp:252
  * #6  0x0000000000418db2 in RainbruRPG::Events::GuiFrameListener::frameStarted (
  *     this=0x266d1e0, evt=@0x7f84f82c8d44) at guiframelistener.cpp:69
  * #7  0x00007f84f7f546f2 in Ogre::Root::_fireFrameStarted ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #8  0x00007f84f7f5526c in Ogre::Root::_fireFrameStarted ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #9  0x00007f84f7f552e9 in Ogre::Root::renderOneFrame ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #10 0x00007f84f7f55355 in Ogre::Root::startRendering ()
  *    from /usr/lib/libOgreMain-1.4.9.so
  * #11 0x00007f84fe070ade in RainbruRPG::Core::GameEngine::run (
  *     this=<value optimized out>) at gameengine.cpp:113
  * #12 0x0000000000424107 in main (argc=1, argv=0x7fff06725d68) at main.cpp:207
  * </pre>
  *
  * \section bug26_history
  *
  * <TABLE width=100% border="1" cellspacing ="0" cellpadding ="0">
  *   <TR bgcolor="#00CC99">
  *     <TH>Date</TH>
  *     <TH>Comment</TH>
  *   </TR>
  *   <TR class="bugList1">
  *     <TD>01 nov 2008</TD>
  *     <TD>Created this detail page</TD>
  *   </TR>
  *   <TR class="bugList2">
  *     <TD>01 feb 2009</TD>
  *     <TD>Closed</TD>
  *   </TR>
  *   <TR class="bugList1">
  *     <TD>16 feb 2009</TD>
  *     <TD>Reopened</TD>
  *   </TR>
  * </TABLE>
  *
  */
