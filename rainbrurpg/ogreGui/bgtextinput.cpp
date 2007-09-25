/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgtextinput.h"

#include "bgwindow.h"

#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreMaterialManager.h>

BetaGUI::TextInput::TextInput(Vector4 D,String M,String V,unsigned int L,Window *P)
  :x(D.x),y(D.y),w(D.z),h(D.w),value(V),mmn(M),mma(M),length(L){
  
  ResourcePtr ma=Ogre::MaterialManager::getSingleton().getByName(mmn+".active");

  if(!ma.isNull())
    mma+=".active";

  mO=P->getGUI()->createOverlay(P->getOverLayContainer()->getName()+"t"+StringConverter::toString(P->getGUI()->getUniqueId()) ,Vector2(x,y),Vector2(w,h),M,"",false);
  mCP=P->getGUI()->createOverlay(mO->getName()+"c",Vector2(4,(h-P->getGUI()->getFontSize())/2),Vector2(w,h),"",V,false);
  
  P->getOverLayContainer()->addChild(mO);
  mO->show();
  mO->addChild(mCP);
  mCP->show();
}
