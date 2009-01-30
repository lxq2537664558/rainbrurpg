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

/** \file doc_bug26.h
  * A bug documentation file
  *
  * This header does not contain code. It is only documentation for
  * a bug.
  *
  * Modifications :
  * - 30 jan 2009 : Updated
  * - 01 nov 2008 : Starting implementation
  *
  */

/** \page bug26_details Details bug #26
  *
  * \section bug26_identification Identification
  * \subsection bug26_description Description
  *
  * This bug is a SegFault. It occurs when an OgreGui MessageBox is about 
  * to be shown.
  *
  * \subsection bug26_reproduce How to reproduce
  *
  * In the connection Window (gsConnection) simply enter wrong connection
  * values (username and password) and click on the connect button.
  *
  * \subsection bug_26_30jan2009 30 jan 2009 update
  *
  * I implemented the QuadRenderer's state mechanism and added a log
  * when \ref RainbruRPG::OgreGui::QuadRenderer::begin() QuadRenderer::begin()
  * is started with a NULL viewport.
  * When this viewport is NULL, we log the QuadRenderer's state, 
  * here is the ouput log :
  * <pre>
  *  [quadrenderer.cpp:312]	WW ViewPort was NULL. Trying to get it from GameEngine
  *  [quadrenderer.cpp:316]	-- QuadRenderer is in 'none' state
  * </pre>
  * Then a segfault occurs.
  *
  * Well, I guess or I know that :
  * - The Viewport pointer we got from GameEngine is devalidate;
  * - The 'none' state should never happen.
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
  *   <TR class="bugList1">
  *     <TD>30 jan 2008</TD>
  *     <TD>Updated. QuadRenderer's state improvment</TD>
  *   </TR>
  * </TABLE>
  *
  */
