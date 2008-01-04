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

#ifndef OPTIONS_H
#define OPTIONS_H

#include "optionintattribute.h"
#include "optionstringattribute.h"
#include "optionboolattribute.h"
#include "optionlistattribute.h"

namespace RainbruRPG {
  namespace Options{
    /** Defines the screen resolution or the window size to use 
      * 
      * \todo Remove it
      */
    enum tSreenResolution{
      SR_640X480   =0x0001, //!< 640 pixels of width, 480 pixels of height
      SR_800X600   =0x0002, //!< 800 pixels of width, 600 pixels of height
      SR_1024X768  =0x0003, //!< 1024 pixels of width, 768 pixels of height
      SR_1280X1024 =0x0004  //!< 1280 pixels of width, 1024 pixels of height
    };

    /** Define the renderer to use       
      * 
      * \todo Remove it
      */
    enum t3DRenderer{
      GR_OPENGL15    =0x01, //!< OpenGL renderer
      GR_DIRECT3D81  =0x02, //!< Microsoft Direct3D 8.1
      GR_DIRECT3D90C =0x03  //!< Microsoft Direct3D 9.0
    };

    /** Initialize the OptionManager
      *
      * Created and initialized in main.cpp::showLauncher()
      */
    class Options{
    public:
      Options();

      void createAttributes();
      void setDefaultValues();

    private:
      /** An integer attribute test */
      OptionIntAttribute *int1;
      /** A string attribute test */
      OptionStringAttribute* st1;
      /** An bool option test */
      OptionBoolAttribute *boo;
      /** A first list attribute test */
      OptionListAttribute *lst;
      /** A second list attribute test */
      //OptionListAttribute* lst3;
      
    };
  }
}

#endif // OPTIONS_H
