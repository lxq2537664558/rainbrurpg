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
  * - 12 feb 2008 : Closed
  * - 01 feb 2009 : Added a sequence diagram
  * - 30 jan 2009 : Updated
  * - 01 nov 2008 : Starting implementation
  *
  * \page bug26_details [Closed] Details bug #26
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
  * \subsection bug_26_01_feb2009 01 feb 2009 update
  *
  * The following image is the sequence diagram of the drawing process.
  * It shows the methods called from RenderQueueListener to GUI and
  * RainbruRPG.
  *
  * \image html bug26-drawing-sequence.png
  * \image latex bug26-drawing-sequence.png
  *
  * \subsection bug_26_03_feb2009 03 feb 2009 update
  *
  * After many tests, here's my conclusion : I through the segfault came from
  * the drawing process of the dialog (SimpleDialog created in the 
  * onConnectClicked() callback of gsConnection) but now I think it occurs
  * at the SimpleDialog costruction.
  *
  * I decided to comment the <em>SimpleDialog->show()</em> statement and
  * several segfaults comes randomly when I clicked on the <em>connect</em>
  * button. So, the segfaults are not due to the drawing process but the
  * RbMessageBox class instanciation could be the cause.
  *
  * Another stuff I notice is when I have luck enough, I can see the
  * the Dialog drawn, the ResizeGrip quad was ugly. It was a whole white
  * square instead of the ResizeGrip image. Maybe the bug is here...
  *
  * Note : I said the segmentation fault was due to the Dialog creation
  * but it happens in the drawing queue, not in the creation sequence.
  * If the dialog is created, the segfault occured, if the dialog is not
  * created, no segfault in drawing sequence.
  *
  * \subsection bug_26_11feb2009 11 feb 2009 update
  * 
  * The segfault seems to come from the RbMessageBox instanciation.The
  * following code in GuiManager::showMessageBox() works perfectly :
  * <pre>
  * Dialog* dlg = new Dialog(Vector4(10, 10,100, 100), title, &GUI::getSingleton());
  * dlg->show();
  * GUI::getSingleton().addDialog(dlg);
  * </pre>
  * 
  * \subsection bug_26_112eb2009 12 feb 2009 update
  *
  * I manage to get a RbMessageBox drawn when it became a subclass
  * of Dialog. The segfault did not occur anymore. Closed.
  *
  * \section bug26_history History
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
  *     <TD>30 jan 2009</TD>
  *     <TD>Updated. QuadRenderer's state improvment</TD>
  *   </TR>
  *   <TR class="bugList1">
  *     <TD>01 feb 2009</TD>
  *     <TD>Added a sequence diagram</TD>
  *   </TR>
  *   <TR class="bugList2">
  *     <TD>03 feb 2009</TD>
  *     <TD>Updated for the construction/not drawing precision</TD>
  *   </TR>
  *   <TR class="bugList1">
  *     <TD>09 feb 2009</TD>
  *     <TD>Updated the drawing sequence</TD>
  *   </TR>
  *   <TR class="bugList2">
  *     <TD>11 feb 2009</TD>
  *     <TD>Updated with the Dialog code</TD>
  *   </TR>
  *   <TR class="bugList1">
  *     <TD>12 feb 2009</TD>
  *     <TD>Closed</TD>
  *   </TR>
  * </TABLE>
  *
  */
