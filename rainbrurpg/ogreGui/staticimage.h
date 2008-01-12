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

/* Modifications :
 * - 19 dec 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_STATIC_IMAGE_H_
#define _OGRE_GUI_STATIC_IMAGE_H_

#include "widget.h"

#include <string.h>
#include <OgreTexture.h>

// Forward declaration
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declaration

using namespace Ogre;
using namespace RainbruRPG::OgreGui;


namespace RainbruRPG{
  namespace OgreGui{

    /** Draws a single image
      *
      * This widget does not use any Skin. It directly use QuadRenderer
      * to draw an Ogre texture.
      *
      * \note This widget was created for gsMenuBase dybamic background menu.
      *
      */
    class StaticImage : public Widget{
    public:
      StaticImage(Vector4, Widget*, OgreGuiSkinID sid=OSI_PARENT);    
      ~StaticImage();

      virtual void draw(QuadRenderer*);

      void setTextureName(const std::string&);
      const std::string& getTextureName(void)const;

      void setPosition(int, int);
      void resize(int, int);

    private:
      /** The name of the texture to draw */
      std::string textureName;

      /** The Ogre texture used to draw the image */
      TexturePtr texture;
    };

  }
}

#endif // _OGRE_GUI_STATIC_IMAGE_H_
