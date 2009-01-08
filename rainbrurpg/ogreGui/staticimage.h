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

/** \file staticimage.h
  * Declares a static image for OgreGui
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
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

#include "quadrenderer.h"

namespace RainbruRPG{
  namespace OgreGui{

    /** Draws a single image
      *
      * This widget does not use any Skin. It directly use QuadRenderer
      * to draw an Ogre texture. It has its own blend mode but it is 
      * by default unused.
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

      void setAlphaMode(tQuadRendererBlendMode);
      tQuadRendererBlendMode getAlphaMode(void) const;

    private:
      /** The name of the texture to draw */
      std::string textureName;

      /** The Ogre texture used to draw the image */
      TexturePtr texture;

      /** The blend mode use by this image */
      tQuadRendererBlendMode alphaMode;
    };

  }
}

#endif // _OGRE_GUI_STATIC_IMAGE_H_
