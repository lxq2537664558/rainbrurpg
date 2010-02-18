/*
 *  Copyright 2006-2010 Jerome PASQUIER
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
  * - 23 nov 2009 : Starting implementation
  *
  */

#ifndef _DRAWABLE_HPP_
#define _DRAWABLE_HPP_

#include <OgreRectangle.h> // Members are left,top,right,bottom;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declarations

using namespace Ogre;

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
      Drawable(Drawable*, const Rectangle&);
      Drawable(Drawable*, int, int, int, int);
      virtual ~Drawable(void);

      // Cannot be purely virtual to provide unit tests
      /// Draw the object
      virtual void draw(QuadRenderer*){};
      void compute(int, int, const Rectangle&);

      void setDirty(bool);

      /** Is this object dirty ?
        *
	* \return The value of the dirty flag
	*
	*/
      bool isDirty(void) const{ return mDirty; };

      Drawable* getParent(void) const;
      const Rectangle& getAbsolute(void)const;
      const Rectangle& getScissor(void)const;

    protected:
      void computeAbsolute(int, int);
      void adjustScissor(const Rectangle&);

    private:
      bool mDirty;         //!< The dirty flag
      Drawable* mParent;   //!< The parent
      Rectangle mScissor;  //!< The scissor rectangle
      Rectangle mRelative; //!< The relative bounding box
      Rectangle mAbsolute; //!< The absolute bounding box
    };
  }
}

#endif // _DRAWABLE_HPP_