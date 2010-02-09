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

#include "screenshotmanager.h"

#include "logger.h"
#include "gameengine.h"

/** The default constructor
  *
  */
RainbruRPG::Core::ScreenshotManager::ScreenshotManager(){
  LOGI("Initializing ScreenshotManager...");
}      

/** Tales a screenshot on Microsoft Direct 3D 9.x
  *
  * \param filename The name of the file to save the image
  *
  * \return always \c true
  */
bool RainbruRPG::Core::ScreenshotManager::takeD3D9Screenshot(
                        const char * filename){
  /*   HRESULT hr;

   IDirect3DSurface9 * frontbuf;
   irr::video::SExposedVideoData data = m_pDevice->getVideoDriver()->getExposedVideoData();
   IDirect3DDevice9 * device = data.D3D9.D3DDev9;

   D3DDISPLAYMODE mode;
   if (FAILED(hr = device->GetDisplayMode(0, &mode)))
   {
      return false;
   }

   device->CreateOffscreenPlainSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &frontbuf, 0);

   //copy frontbuffer on surface
   hr = device->GetFrontBufferData(0, frontbuf);

   //error checking
   if(hr != D3D_OK)
   {
      frontbuf->Release(); //release the surface so there is no memory leak
      return false;
   }

   //save surface to file
   D3DXSaveSurfaceToFile(filename.c_str(), D3DXIFF_BMP, frontbuf, NULL, NULL);

   frontbuf->Release();
  */
   return true;
} 

/** Tales a screenshot on Microsoft Direct 3D 8.x
  *
  * \param filename The name of the file to save the image
  *
  * \return always \c true
  */
bool RainbruRPG::Core::ScreenshotManager::takeD3D8Screenshot(
                const char * filename)
{
   LOGW("directx 8 not supported by screenshot manager");
   return false;

   /*
   HRESULT hr;

   IDirect3DSurface8 * frontbuf;
   irr::video::SExposedVideoData data = m_pDevice->getVideoDriver()->getExposedVideoData();
   IDirect3DDevice8 * device = data.D3D8.D3DDev8;

   D3DDISPLAYMODE mode;
   if (FAILED(hr = device->GetDisplayMode(&mode)))
   {
      return false;
   }

   device->CreateImageSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, &frontbuf);

   //copy frontbuffer on surface
   hr = device->GetFrontBuffer(frontbuf);   // error !!!

   //error checking
   if(hr != D3D_OK)
   {
      frontbuf->Release(); //release the surface so there is no memory leak
      return false;
   }

   //save surface to file
   D3DXSaveSurfaceToFile(filename.c_str(), D3DXIFF_BMP, frontbuf, NULL, NULL);

   frontbuf->Release();

   return true;
   */
} 

/** Get the next filename to use
  *
  * \return The next filename
  */
char * RainbruRPG::Core::ScreenshotManager::getFileName(void){
  /*   irr::io::IFileSystem * fs = m_pDevice->getFileSystem();
   irr::u32 i = 0;

   while(true)
   {
      char* name;
      sprintf(name, "media\\screenshots\\screenshot%03d.bmp", i++);
      if(!fs->existFile(name))
      {
         return name;
      }
   }
  */
  
   return "";
} 

/** Tales a screenshot on OpenGL
  *
  * \param filename The name of the file to save the image
  *
  * \return always \c true
  */
bool RainbruRPG::Core::ScreenshotManager::takeOGLScreenshot(
		    char* filename){

  //   ilutGLScreen();
  //  checkILErrors();
   //  ilSave(IL_PNG, filename);

   return true;
} 

/** Takes the screenshot
  *
  *
  * \return Always \c true
  */
bool RainbruRPG::Core::ScreenshotManager::take(){
  irr::video::E_DRIVER_TYPE d=GameEngine::getSingleton().getDriverType();

  switch(d){
  case EDT_DIRECT3D8:
    LOGW("DIRECT3D 8 screenshots not yet implemented");
    break;

  case EDT_OPENGL:
    LOGI("Taking screenshot");
    takeOGLScreenshot("screenshot-OpenGL-000.png");
    break;

  case EDT_DIRECT3D9:
    LOGW("DIRECT3D 9 screenshots not yet implemented");
    break;

  default:
    LOGW("ScreenshotManager enable to define Irrlicht Driver type");
  }

  return true;
}

/** Take a screenshot
  *
  * /param driver The Irrlicht driver in use
  * /param windowed Is the game in windows state
  * /param filename The filename of the image file
  
void irrScreenshot( irr::video::IVideoDriver * driver, 
		    bool const & windowed, std::string const & filename ){

    LPDIRECT3DSURFACE9 Surface = 0;
    if (windowed)    {
      driver->getExposedVideoData().D3D9.D3DDev9->GetBackBuffer(0, 0, 
				    D3DBACKBUFFER_TYPE_MONO, &Surface);
      D3DXSaveSurfaceToFile(filename.c_str(), D3DXIFF_BMP, Surface, 
			    NULL, NULL);
    }
    else{
      int Width  = GetSystemMetrics(SM_CXSCREEN);
      int Height = GetSystemMetrics(SM_CYSCREEN);
      driver->getExposedVideoData().D3D9.D3DDev9->
	CreateOffscreenPlainSurface(Width, Height, D3DFMT_A8R8G8B8, 
				    D3DPOOL_SYSTEMMEM, &Surface, NULL);
      driver->getExposedVideoData().D3D9.D3DDev9->GetFrontBufferData(NULL, 
								     Surface);
      D3DXSaveSurfaceToFile(filename.c_str(), D3DXIFF_BMP, Surface, 
			    NULL, NULL);
    }
    Surface->Release();
}
*/

