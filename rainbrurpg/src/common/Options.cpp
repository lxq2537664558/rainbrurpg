/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file Options.cpp
  * Implements a class used to initialize OptionManager
  *
  */

#include "Options.hpp"

#include "OptionPanel.hpp"
#include "OptionButton.hpp"
#include "OptionManager.hpp"

/** An empty constructor
  *
  */
RainbruRPG::Options::Options::Options(){

}

/** Creates test attributes
  *
  */
void RainbruRPG::Options::Options::createAttributes(){
  OptionPanel *opGraphics=new OptionPanel("Graphics", _("Graphics"));
  OptionButton* btn1=new OptionButton("Renderer",_("Renderer"),"DawnTime.ico");

      // Example IntAttribute
  int1=new OptionIntAttribute("IntAttribute", _("Integer Attribute"));
      int1->setToolTip(_("A simple example integer value to test the "
			 "layout disposition."));
      btn1->add(int1);

      // Example StringAttribute
      st1=new OptionStringAttribute("String Attribute", _("String Attribute"));
      btn1->add(st1);

      // Example boolAttribute
      boo=new OptionBoolAttribute("Fullscreen", _("Fullscreen"));
      boo->setToolTip(_("Will the game launch in full screen or "
			"windowed mode"));
      btn1->add(boo);

  // Resolution
      lst=new OptionListAttribute("Resolution", _("Resolution"));
	boo->setToolTip(_("Sets the screen size for both fullscreen "
			  "and windowed mode"));

	lst->add("640x480");
	lst->add("800x600");
	lst->add("1024 X 768");
	lst->add("1280 X 960");
	lst->add("1280 X 1024");
	lst->add("1600 X 1200");

        btn1->add(lst);


  //Shadows
	/*	lst2=new OptionListAttribute("Shadows");
	boo->setToolTip("Sets the shadows calculation method");
	lst2->add("none");
 	lst2->add("Stencil additive");
 	lst2->add("Stencil modulative");
 	lst2->add("Texture modulative");
     btn1->add(lst2);
	*/

    opGraphics->add(btn1);
  OptionManager::getSingleton().add(opGraphics);

  OptionPanel *opSounds=new OptionPanel("Sounds", _("Sounds"));
  OptionManager::getSingleton().add(opSounds);
}

/** Set the default values of this attributes
  * 
  *
  */
void RainbruRPG::Options::Options::setDefaultValues(){
  int1->setValueStr("12");
  st1->setValueStr("DefaultValue");
  boo->setValueStr("true");
  lst->setValueStr("800x600");
  // lst2->setValueStr("none");

}
