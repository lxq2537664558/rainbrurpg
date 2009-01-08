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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "irrfontmanager.h"

#include <string>

#include "logger.h"
#include "gameengine.h"

/** Create the filename string for the font
  *
  * The font is in the \c data/fonts directory. Its name is \c name_size.bmp
  *
  * \param fontName The fontname type
  * \param size The font size
  *
  * \return A string representing the filename containing the font
  */
char* RainbruRPG::Core::IrrFontManager::createFontFileName(tIrrFont fontName, unsigned int size ){
  char* ret="";

  switch(fontName){

    //////////////////////////////////// COURRIER
  case IFM_COURRIER:
    if (size==10){
      LOGI("Loading COURRIER font size 10");
      ret="../data/fonts/courrier_new_10.bmp";
    }
    else if (size==11){
      LOGI("Loading COURRIER font size 11");
      ret="../data/fonts/courrier_new_11.bmp";
    }
    else if (size==12){
      LOGI("Loading COURRIER font size 12");
      ret="../data/fonts/courrier_new_12.bmp";
    }
    else if (size==14){
      LOGI("Loading COURRIER font size 14");
      ret="../data/fonts/courrier_new_14.bmp";
    }
    else if (size==16){
      LOGI("Loading COURRIER font size 16");
      ret="../data/fonts/courrier_new_16.bmp";
    }
    else{
      LOGW("Font size for COURRIER not supported");
      ret="../data/fonts/courrier_new_16.bmp";
    }

    break;

    //////////////////////////////////// IFM_SHA_BLACK

  case IFM_SHA_BLACK:
    if (size==20){
      LOGI("Loading SHADOWED BLACK font size 20");
      ret="../data/fonts/shadowed_black_20.bmp";
    }
    else{
      LOGW("Font size for SHADOWED BLACK not supported");
     ret="../data/fonts/shadowed_black_20.bmp";
    }
    break;

   //////////////////////////////////// IFM_PLA_BLACK

  case IFM_PLA_BLACK:
    if (size==20){
      LOGI("Loading PLAIN BLACK font size 20");
      ret="../data/fonts/plain_black_20.bmp";
    }
    else{
      LOGW("Font size for PLAIN BLACK not supported");
     ret="../data/fonts/plain_black_20.bmp";
    }
    break;

   //////////////////////////////////// IFM_INC_BLACK

  case IFM_INC_BLACK:
    if (size==20){
      LOGI("Loading INCISED BLACK font size 20");
      ret="../data/fonts/incised_black_20.bmp";
    }
    else{
      LOGW("Font size for INCISED BLACK not supported");
     ret="../data/fonts/incised_black_20.bmp";
    }
    break;


   //////////////////////////////////// IFM_CRUMBLE

  case IFM_CRUMBLE:
    if (size==26){
      LOGI("Loading CRUMBLE font size 20");
      ret="../data/fonts/crumble_26.bmp";
    }
    else{
      LOGW("Font size for CRUMBLE not supported");
     ret="../data/fonts/crumble_26.bmp";
    }
    break;




  } // Fermeture du case

  return ret;
}

/** Set the global font of Irrlicht engine
  *
  * This font will be use for every text that is no override.
  *
  * \param fontName The fontname type
  * \param size The font size
  *
  */
void RainbruRPG::Core::IrrFontManager::setGlobalFont(tIrrFont fontName, unsigned int size ){

  IGUISkin* skin =GameEngine::getSingleton().getIrrlichtGui()->getSkin();

  IGUIFont* font = loadFont(fontName, size);
  if (font)
    skin->setFont(font);

};

/** The static text method to override Irrlicht font
  *
  * \param w The widget to set the font
  * \param fontName The fontname type
  * \param size The font size
  */
void RainbruRPG::Core::IrrFontManager::setWidgetFont(irr::gui::IGUIStaticText 
		 *w, tIrrFont fontName, unsigned int size ){

  IGUIFont* font = loadFont(fontName, size);
  if (font)
    w->setOverrideFont(font);
}

/** The edit box method to override Irrlicht font
  *
  * \param w The widget to set the font
  * \param fontName The fontname type
  * \param size The font size
  */
void RainbruRPG::Core::IrrFontManager::setWidgetFont(irr::gui::IGUIEditBox *w, 
                 tIrrFont fontName, unsigned int size ){

  IGUIFont* font = loadFont(fontName, size);
  if (font)
    w->setOverrideFont(font);
}

/** The button method to override Irrlicht font
  *
  * \param w The widget to set the font
  * \param fontName The fontname type
  * \param size The font size
  */
void RainbruRPG::Core::IrrFontManager::setWidgetFont(irr::gui::IGUIButton *w, 
                 tIrrFont fontName, unsigned int size ){

  IGUIFont* font = loadFont(fontName, size);
  if (font)
    w->setOverrideFont(font);
}

/** The function that loads a font
  *
  * Here we ask Irrlicht to load a font.
  *
  * \param fontName The fontname type
  * \param size The font size
  *
  * \return The Irrlicht font
  */
irr::gui::IGUIFont* RainbruRPG::Core::IrrFontManager::loadFont(
                    tIrrFont fontName, unsigned int size ){

  IGUIFont* font = GameEngine::getSingleton().getIrrlichtGui()->
                               getFont(createFontFileName(fontName, size));

  if (!font){
    LOGE("Failed to load a font");
//    LOGE(createFontFileName(fontName, size).c_str());
  }
else{
    LOGI("New font loaded successfully");
//    LOGI(createFontFileName(fontName, size).c_str());
}
  return font;
}
