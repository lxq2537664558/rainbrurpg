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

#ifndef SCREEN_SHOT_MANAGER_H
#define SCREEN_SHOT_MANAGER_H

/*
#pragma comment(lib, "D3DX8.lib")
#pragma comment(lib, "D3D8.lib")
#include <D3DX8.h>
#include <D3D8.h>
*/

/*
#pragma comment(lib, "D3DX9.lib")
#pragma comment(lib, "D3D9.lib")
#include <D3DX9.h>
#include <D3D9.h>
*/

//#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "Glu32.lib")
//#include <GL/glu.h>
//#include <GL/gl.h>

#include <irrlicht.h>
#include <cstdio>

#include "singleton.h"

using namespace std;

namespace RainbruRPG{
  namespace Core{

    /** NOT YET IMPLEMENTED. A test of screenshot manager
      *
      */
    class ScreenshotManager : public Singleton<ScreenshotManager>{
    public:
      ScreenshotManager();

      bool take();
    private:
      /** Unimplemented copy constructors 
        *
	* In a singleton the use of this methos must be forbidden.
	* 
	* \param obj A ScreenshotManager
	*/
      ScreenshotManager(const ScreenshotManager& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this methos must be forbidden.
	* \param obj A ScreenshotManager
	*/
      ScreenshotManager& operator=(const ScreenshotManager& obj);

      bool takeOGLScreenshot(char* filename); 
      bool takeD3D8Screenshot(const char* filename);
      bool takeD3D9Screenshot(const char* filename);

      char * getFileName(void);
    };
  }
}

#endif // SCREEN_SHOT_MANAGER_H
