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

/** \file Drawable.hpp
  *
  * Declare an ogreGui drawable object
  *
  * Modifications :
  * - 19 feb 2010 : Handles deactivation of dirty flag
  * - 23 nov 2009 : Starting implementation
  *
  */

#ifndef _DRAWABLE_HPP_
#define _DRAWABLE_HPP_

#include "config.h"

#include <OgreRectangle.h> // Members are left,top,right,bottom;
#include <OgreTexture.h>

#include "TextureNotFoundException.hpp" // uses in throw() cannot be forwarded
#include "SkinNotFoundException.hpp"

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Brush;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace RainbruRPG::Exception;

namespace RainbruRPG{
  namespace OgreGui{

    /** An ogreGui drawable object
      *
      * This implements the dirty flag and its propagation to parent.
      *
      * \section The drawable layout
      * 
      * \image html drawable.png "The Drawable layout"
      * \image latex drawable.png "The Drawable layout"
      *
      * This graph explains how to deal with included rectangle members.
      * Absolutes coordinates are computed based on the Parent's x and y 
      * absolute positions. You only have to compute absolute rectangle
      * and scissor rectangle using the provided \ref computeAbsolute()
      * and \ref computeAbsolute() fonctions.
      *
      */
    class Drawable{
    public:
      Drawable(Drawable*, const Ogre::Rectangle&, const std::string& vSkinName = "");
      Drawable(Drawable*, int, int, int, int, const std::string& vSkinName = "");
      virtual ~Drawable(void);

      virtual void draw(Brush*);
      void compute(int, int, const Ogre::Rectangle&);

      void setDirty(bool);

      /** Is this object dirty ?
        *
	* \return The value of the dirty flag
	*
	*/
      inline bool isDirty(void) const{ 
#ifdef RB_DIRTY_FLAG
	return mDirty; 
#else
	return true;
#endif
      };

      Drawable* getParent(void) const;
      const Ogre::Rectangle& getAbsolute(void)const;
      const Ogre::Rectangle& getScissor(void)const;

      const std::string& getSkinName(void)const;

      void setTexturePtr(Ogre::TexturePtr);
      const Ogre::TexturePtr& getTexturePtr(void)const;

      void loadTexture(const std::string&)throw(TextureNotFoundException);
      
      void loadSkinnableTexture(const std::string&, const std::string&)
	throw(TextureNotFoundException,SkinNotFoundException);

      void debugAbsolute(const std::string&);

    protected:
      void setSkinName(const std::string&);

      void computeAbsolute(int, int);
      void adjustScissor(const Ogre::Rectangle&);

      std::string mSkinName;     //!< The current skin name
      Ogre::Rectangle mAbsolute; //!< The absolute bounding box
      Ogre::Rectangle mScissor;  //!< The scissor rectangle

    private:
#ifdef RB_DIRTY_FLAG
      bool mDirty;               //!< The dirty flag
#endif
      Drawable* mParent;         //!< The parent
      Ogre::Rectangle mRelative; //!< The relative bounding box

      Ogre::TexturePtr mTexture; //!< The current texture

    };
  }
}

#endif // _DRAWABLE_HPP_
