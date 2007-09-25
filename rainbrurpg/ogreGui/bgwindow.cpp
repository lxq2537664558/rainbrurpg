/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

#include "bgwindow.h"

#include "bglistener.h"
#include <OGRE/OgreStringConverter.h>

BetaGUI::Window::Window(Vector4 D,String M, wt t,String C, GUI *G)
  :x(D.x),y(D.y),w(D.z),h(D.w),mGUI(G),mTB(0),mRZ(0),mATI(0),mAB(0){

  mO=G->createOverlay("BetaGUI.w"+StringConverter::toString(G->getWindowUniqueId()),Vector2(D.x,D.y),Vector2(D.z,D.w),M); 
  
  if(t>=2){
    Callback c;
    c.setType(4);
    mRZ=createButton(Vector4(D.z-16,D.w-16,16,16),M+".resize","",c);
  }
  
  if(t==1||t==3){
    Callback c;
    c.setType(3);
    mTB=createButton(Vector4(0,0,D.z,22),M+".titlebar",C,c);
  }
}

BetaGUI::Window::~Window(){
  for(unsigned int i=0;i<mB.size();i++)
    delete mB[i];

  for(unsigned int i=0;i<mT.size();i++)
    delete mT[i];
  
  mGUI->getRootOverlay()->remove2D(mO);
}

BetaGUI::Button* BetaGUI::Window::createButton(Vector4 D,String M,String T,Callback C){
  Button *x=new Button(D,M,T,C,this);
  mB.push_back(x);
  return x;
}

BetaGUI::TextInput* BetaGUI::Window::createTextInput(Vector4 D,String M,String V,unsigned int L){

  TextInput *x=new TextInput(D,M,V,L,this);
  mT.push_back(x);
  return x;
}

void BetaGUI::Window::createStaticText(Vector4 D,String T){
  OverlayContainer* x=mGUI->createOverlay(mO->getName()+StringConverter::toString(mGUI->getStaticTextUniqueId()),Vector2(D.x,D.y),Vector2(D.z,D.w),"", T,false);
  
  mO->addChild(x);
  x->show();
}

bool BetaGUI::Window::checkKey(String k, unsigned int px, unsigned int py){
  if(mATI==0)
    return false;
  
  if(!mO->isVisible())
    return false;
  
  if(!(px>=x&&py>=y)||!(px<=x+w&&py<=y+h))
    return false;
  
  if(k=="!b"){
    mATI->setValue(mATI->getValue().substr(0,mATI->getValue().length()-1));
    return true;
  }
  
  if(mATI->getValue().length() >= mATI->getLength())
    return true;
  

  mATI->setValue(mATI->getValue()+k);
  mATI->getContentOverlay()->setCaption(mATI->getValue());
  return true;
}


bool BetaGUI::Window::check(unsigned int px, unsigned int py, bool LMB){
  if(!mO->isVisible())
    return false;
  
  if(!(px>=x&&py>=y)||!(px<=x+w&&py<=y+h)){
    if(mAB){
      mAB->activate(false);
    }
    return false;
  }
  
  if(mAB){
    mAB->activate(false);
  }
  
  for(unsigned int i=0;i<mB.size();i++){
    if (mB[i]->in(px,py,x,y))
      continue;
    
    if(mAB){
      mAB->activate(false);
    }
    
    mAB=mB[i];
    mAB->activate(true);
    if(!LMB)
      return true;
    
    if(mATI){
      mATI->getFrameOverlay()->setMaterialName(mATI->getMmn());
      mATI=0;
    }
    
    switch(mAB->getCallback().getType()){
    default: 
      return true;
      
    case 1:
      mAB->getCallback().fp(mAB);
      return true;
      
    case 2:
      mAB->getCallback().LS->onButtonPress(mAB);
      return true;
      
    case 3:
      mO->setPosition(x=px-(mAB->getWidth()/2),y=py-(mAB->getHeight()/2));
      return true;
      
    case 4:
      mO->setDimensions(w=px-x+8,h=py-y+8);
      mRZ->setX(w-16);
      mRZ->setY(h-16);
      mRZ->getOverlayContainer()->setPosition(mRZ->getX(),mRZ->getY());
      
      if(mTB){

	mTB->setWidth(w);
	mTB->getOverlayContainer()->setWidth(mTB->getWidth());
      }
      
      return true;
    }
  }
  
  if (!LMB)
    return true;
  
  for(unsigned int i=0;i<mT.size();i++){
    if(mT[i]->in(px,py,x,y))
      continue;
    
    mATI=mT[i];
    mATI->getContentOverlay()->setMaterialName(mATI->getMma());
    return true;
  }
  if(mATI){
    mATI->getContentOverlay()->setMaterialName(mATI->getMmn());
    mATI=0;
  }
  return true;
}
