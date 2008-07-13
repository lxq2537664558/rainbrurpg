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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */


#include "infodialog.h"

#include "pushbutton.h"

/** The default constructor
  *
  * Creates an information dialog with width and height set to 10 and
  * a default title : 'Info Dialog'.
  *
  */
RainbruRPG::Terminal::InfoDialog::InfoDialog():
  Dialog(10, 10)
{
  this->setTitle( "Info Dialog" );
  this->addButton(new PushButton("Ok"));

}


/** The constructor of a centered information dialog with a title
  *
  * \param s The title of the dialog
  * \param w The width of the dialog in column
  * \param h The height of the dialog in lines
  */
RainbruRPG::Terminal::InfoDialog::InfoDialog( string s, int w, int h )
                                 :Dialog( w, h ){
  this->setTitle( s );
  this->addButton(new PushButton("Ok"));
}

void RainbruRPG::Terminal::InfoDialog::draw(){
  drawDialog();
}
