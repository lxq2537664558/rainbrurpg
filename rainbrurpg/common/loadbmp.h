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

/** Modifications :
  * - 10 jul 2008 : output now is a std::string (fix a warning)
  *
  */
#ifndef LOAD_BMP_H
#define LOAD_BMP_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <string>

#include "EasyBMP.h"
#include "rainbrudef.h"

using namespace std;

#ifndef WIN32
  // Cause redefined symbol when cross-compiling to Win32 
  typedef char BYTE;
#endif

namespace RainbruRPG {
  namespace Core{

    /** A stenographic decoder class
      *
      * This class uses EasyBMP (http://easybmp.sourceforge.net/)
      * to decode text in BMP (4 or 8 bits) images. To encode the text I
      * uses the example found in this archive 
      * http://easybmp.sourceforge.net/downloads/samples/Steganography3.zip.
      *
      * Usage axample :
      * \code
      * LoadBMP *l=new LoadBMP();
      * l->decode();
      *
      * cout << l->get1() << endl;
      * \endcode
      *
      * The input BMP filename is designed by input.
      * Output is the filename of a temp file.
      *
      * This class is used by \ref
      * RainbruRPG::Network::Ident::CurlGetFile::writeToFile()
      * "CurlGetFile::writeToFile()" to retrieve the username
      * and password for HTTP authentification.
      *
      * To work, it need a 4-bits or 8-bits BMP image format. To get
      * a compatible image, use The Gimp and use the Image/Mode/Indexed
      * menu.
      *
      */
    class RAINBRU_EXPORT LoadBMP{
    public:
      LoadBMP();
      ~LoadBMP();

      void decode();

      const char* get1();


    private:
      /** The filename of the input image
        *
	* This filename (with path) should point to a 
	* encoded image.
	*
	*/
      char* input;
      /** The filename of the output stream
        *
	* The text extracted from the image will be placed here before
	* getting returned to the program then removed from the hard drive.
	*
	*/
      std::string output;

      /** The string that contains the decoded text
        *
	* That's the text you can get by calling get1().
	*
        */
      std::string a1;

    };
  }
}

#endif // LOAD_BMP_H
