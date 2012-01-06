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

/** \file terminalapi/label.h
  * Declares a label widget
  *
  * Modifications :
  * - 06 sep 2008 : Single file documentation
  * - 11 jul 2008 : Now use std::string member
  *
  */

#ifndef LABEL_H
#define LABEL_H

#include <slang.h>
#include <string>

#include "widget.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** The simpliest widget
      *
      * The label is a text renderer.
      */
    class Label : public Widget{
    public:
      Label();
      Label( const std::string& );
      Label( const std::string&, int, int );

      ~Label();

      void setText( const std::string& );
      const std::string& getText()const;

      virtual void draw( int x, int y );
      virtual void receiveKeyEvent(int){};
    private:
      /** The caption of the label */
      std::string caption;

    };
  }
}

#endif // LABEL_H
