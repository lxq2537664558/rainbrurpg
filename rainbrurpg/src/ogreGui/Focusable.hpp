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

/** \file Focusable.hpp
  *
  * Declare an ogreGui focusable object
  *
  * Modifications :
  * - 08 jun 2010 : Starting implementation
  *
  */

#ifndef _FOCUSABLE_HPP_
#define _FOCUSABLE_HPP_

namespace RainbruRPG{
  namespace OgreGui{
    /** A GUI object able to take the keyboard focus (or not)
      *
      */
    class Focusable{
    public:
      Focusable(bool);

      bool canTakeFocus()const;
      void setCanTakeFocus(bool);

    private:
      /** Can this take the keyboard focus */
      bool mCanTakeFocus;

    };
  }
}
#endif // !_FOCUSABLE_HPP_
