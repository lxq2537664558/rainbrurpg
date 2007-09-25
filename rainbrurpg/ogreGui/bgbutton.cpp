/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgbutton.h"

#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreStringConverter.h>

BetaGUI::Button::Button(Vector4 D, String M, String T, Callback C, Window *P)
                :x(D.x),
		 y(D.y),
		 w(D.z),
		 h(D.w),
		 mmn(M),
		 mma(M){


  
  ResourcePtr ma=MaterialManager::getSingleton()
    .getByName(mmn+".active");

  if(!ma.isNull())
    mma+=".active";
  
  // Get a unique name for the overlay
  Ogre::String uniqueName=P->getOverLayContainer()->getName()+"b"
    +StringConverter::toString(P->getGUI()->getUniqueId());

  mO=P->getGUI()->createOverlay(uniqueName,Vector2(x,y),Vector2(w,h),M,"",false);
  
  mCP=P->getGUI()->createOverlay(mO->getName()+"c",Vector2(4,(h-P->getGUI()->getFontSize())/2),Vector2(w,h),"",T,false);
  
  P->getOverLayContainer()->addChild(mO);
  mO->show();
  mO->addChild(mCP);
  mCP->show();
  callback=C;
}
