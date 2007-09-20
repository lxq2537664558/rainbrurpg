
#include "betagui.h"
using namespace Ogre;
using namespace std;


namespace BetaGUI {
  GUI::GUI(String font, unsigned int fontSize)
 :mXW(0), mMP(0),mFont(font),mFontSize(fontSize),wc(0),bc(0),tc(0){
    mO=OverlayManager::getSingleton().create("BetaGUI");
    mO->show();
  }

  GUI::~GUI(){
    for(unsigned int i=0;i < WN.size();i++)
      delete WN[i];WN.clear();
  }

  bool GUI::injectMouse(unsigned int x,unsigned int y,bool LMB){
    if(mMP)mMP->setPosition(x,y);

    if(mXW){
      for(vector<Window*>::iterator i=WN.begin();i!=WN.end();i++){
	if(mXW==(*i)){delete mXW;WN.erase(i);mXW=0;return false;}
      }
    }
	for(unsigned int i=0;i<WN.size();i++){if(WN[i]->check(x,y,LMB)){return true;}}return false;}

bool GUI::injectKey(String key, unsigned int x,unsigned int y){
  for(unsigned int i=0;i<WN.size();i++){
    if(WN[i]->checkKey(key,x,y)){
      return true;
    }
  }return false;
}

OverlayContainer* GUI::createOverlay(String N,Vector2 P,Vector2 D,String M,String C,bool A){
  String t="Panel";
  if (C!="")
    t="TextArea";

  OverlayContainer* e=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement(t, N));

  e->setMetricsMode(GMM_PIXELS);
  e->setDimensions(D.x,D.y);
  e->setPosition(P.x,P.y);

  if (M!="")
    e->setMaterialName(M);

  if (C!=""){
    e->setCaption(C);
    e->setParameter("font_name",mFont);
    e->setParameter("char_height",StringConverter::toString(mFontSize));
  }

  if(A){
    mO->add2D(e);
    e->show();
  }
  return e;
}

  OverlayContainer* GUI::createMousePointer(Vector2 d, String m){
    Overlay* o=OverlayManager::getSingleton().create("BetaGUI.MP");
    o->setZOrder(649);
    mMP=createOverlay("bg.mp",Vector2(0,0),d,m,"", false);

    o->add2D(mMP);
    o->show();
    mMP->show();
    return mMP;
  }

  Window* GUI::createWindow(Vector4 D,String M, wt T,String C){
    Window* w=new Window(D,M,T,C,this);
    WN.push_back(w);
    return w;
  }

  Window::Window(Vector4 D,String M, wt t,String C, GUI *G)
    :x(D.x),y(D.y),w(D.z),h(D.w),mGUI(G),mTB(0),mRZ(0),mATI(0),mAB(0){
    mO=G->createOverlay("BetaGUI.w"+StringConverter::toString(G->wc++),Vector2(D.x,D.y),Vector2(D.z,D.w),M); 

    if(t>=2){
      Callback c;
      c.t=4;mRZ=createButton(Vector4(D.z-16,D.w-16,16,16),M+".resize","",c);
    }

    if(t==1||t==3){
      Callback c;
      c.t=3;
      mTB=createButton(Vector4(0,0,D.z,22),M+".titlebar",C,c);
    }
  }

Window::~Window(){
  for(unsigned int i=0;i<mB.size();i++)
    delete mB[i];

  for(unsigned int i=0;i<mT.size();i++)
    delete mT[i];
  
  mGUI->mO->remove2D(mO);
}

Button* Window::createButton(Vector4 D,String M,String T,Callback C){
  Button *x=new Button(D,M,T,C,this);
  mB.push_back(x);
  return x;
}
  
  Button::Button(Vector4 D, String M, String T, Callback C, Window *P)
    :x(D.x),y(D.y),w(D.z),h(D.w),mmn(M),mma(M){

    ResourcePtr ma=MaterialManager::getSingleton()
      .getByName(mmn+".active");if(!ma.isNull())mma+=".active";

    mO=P->mGUI->createOverlay(P->mO->getName()+"b"+StringConverter::toString(P->mGUI->bc++),Vector2(x,y),Vector2(w,h),M,"",false);

    mCP=P->mGUI->createOverlay(mO->getName()+"c",Vector2(4,(h-P->mGUI->mFontSize)/2),Vector2(w,h),"",T,false);

    P->mO->addChild(mO);
    mO->show();
    mO->addChild(mCP);
    mCP->show();
    callback=C;
  }

  TextInput* Window::createTextInput(Vector4 D,String M,String V,unsigned int L){

    TextInput *x=new TextInput(D,M,V,L,this);
    mT.push_back(x);
    return x;
  }

  void Window::createStaticText(Vector4 D,String T){
    OverlayContainer* x=mGUI->createOverlay(mO->getName()+StringConverter::toString(mGUI->tc++),Vector2(D.x,D.y),Vector2(D.z,D.w),"", T,false);

    mO->addChild(x);
    x->show();
  }

  TextInput::TextInput(Vector4 D,String M,String V,unsigned int L,Window *P)
    :x(D.x),y(D.y),w(D.z),h(D.w),value(V),mmn(M),mma(M),length(L){

    ResourcePtr ma=Ogre::MaterialManager::getSingleton().getByName(mmn+".active");
    if(!ma.isNull())mma+=".active";
    mO=P->mGUI->createOverlay(P->mO->getName()+"t"+StringConverter::toString(P->mGUI->tc++) ,Vector2(x,y),Vector2(w,h),M,"",false);
    mCP=P->mGUI->createOverlay(mO->getName()+"c",Vector2(4,(h-P->mGUI->mFontSize)/2),Vector2(w,h),"",V,false);
    
    P->mO->addChild(mO);
    mO->show();
    mO->addChild(mCP);
    mCP->show();
  }

  bool Window::checkKey(String k, unsigned int px, unsigned int py){
    if(mATI==0)
      return false;

    if(!mO->isVisible())
      return false;

    if(!(px>=x&&py>=y)||!(px<=x+w&&py<=y+h))
      return false;

    if(k=="!b"){
      mATI->setValue(mATI->value.substr(0,mATI->value.length()-1));
      return true;
    }

    if(mATI->value.length() >= mATI->length)
      return true;
    
    mATI->mCP->setCaption(mATI->value+=k);
    return true;
  }

  bool Window::check(unsigned int px, unsigned int py, bool LMB){
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
	mATI->mO->setMaterialName(mATI->mmn);
	mATI=0;
      }
      
      switch(mAB->callback.t){
      default: 
	return true;

      case 1:
	mAB->callback.fp(mAB);
	return true;
      
      case 2:
	mAB->callback.LS->onButtonPress(mAB);
	return true;

      case 3:
	mO->setPosition(x=px-(mAB->w/2),y=py-(mAB->h/2));
	return true;
      
      case 4:
	mO->setDimensions(w=px-x+8,h=py-y+8);
	mRZ->mO->setPosition(mRZ->x=w-16,mRZ->y=h-16);
	
	if(mTB){
	  mTB->mO->setWidth(mTB->w=w);
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
      mATI->mO->setMaterialName(mATI->mma);
      return true;
    }
    if(mATI){
      mATI->mO->setMaterialName(mATI->mmn);
      mATI=0;
    }
    return true;}
} // End of Betajaen's GUI. Normal programming can resume now.
