/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file ogreGui/dialog.h
  * Declares a modal dialog for OgreGui
  *
  * Modifications :
  * - 15 oct 2009 : Made messages transatable with gettext
  * - 13 feb 2009 : Fix a bug when moving the dialog in draw()
  * - 11 feb 2009 : Constructor now takes a const Vector4&  
  * - 10 feb 2009 : - draw() now calls QuadRenderer::reset()
  *                 - Constructor now takes a const Vector4&  
  * - 25 aug 2008 : Single file documentation
  * - 13 may 2008 : starting implementation
  *         
  */


#ifndef _OGRE_GUI_DIALOG_H_
#define _OGRE_GUI_DIALOG_H_

#include <ogreimport.h>
#include <rainbrudef.h>    // For the GNU gettext stuff

#include "bgwindow.h"

// Forward declaration
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
  }
}
// End of Forward declaration

namespace RainbruRPG{
  namespace OgreGui{

    /** A Window that can have a border and be modal
      *
      * \note A dialog, by default, can be moved but cannot be resized
      *       it is to provide a coherent border.
      *
      */
    class Dialog : public BetaGUI::Window{
    public:
      Dialog( const Vector4&, const String&, GUI*,
	      RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_DEFAULT );
      virtual ~Dialog();

      virtual void draw(QuadRenderer*);

    private:
      Skin* mSkin;
    };

  }
}

#endif // _OGRE_GUI_DIALOG_H_
