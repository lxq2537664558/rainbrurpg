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

/** \file Label.hpp
  *
  * Declare an ogreGui label widget.
  *
  * Modifications :
  * - 19 nov 2010 : Starting implementation
  *
  */

#ifndef _LABEL_HPP_
#define _LABEL_HPP_

#include "Widget.hpp"
#include <string>

using namespace std;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Brush;
  }
}
// End of forward declarations


namespace RainbruRPG{
  namespace OgreGui{

    /** A simple text drawing widget
      *
      */
    class Label : public Widget
    {
    public:
      Label(Widget*, int, int, int, int, const string&);
      virtual ~Label();

      void setCaption(const string&);
      const string& getCaption(void);

      virtual void Draw(Brush*);

    private:
      /** The text to be drawn */
      string mCaption;

    };
  }
}

#endif // !_LABEL_HPP_
