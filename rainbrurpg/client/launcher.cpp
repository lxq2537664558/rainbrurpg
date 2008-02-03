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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */


#include "launcher.h"

#include <iostream>

#include "launcheroptions.h"
#include "languageselector.h"
#include "xmloptions.h"
#include "gameengine.h"

#include <fox-1.6/FXPNGImage.h>
#include <fox-1.6/FXMessageBox.h>

#include "config.h"

FXDEFMAP(RainbruRPG::Gui::Launcher) LauncherMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::Launcher::ID_BTN_PLAY, RainbruRPG::Gui::Launcher::onPlayButtonPressed),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::Launcher::ID_BTN_OPTS, RainbruRPG::Gui::Launcher::onOptionsButtonPressed),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::Launcher::ID_BTN_QUIT, RainbruRPG::Gui::Launcher::onQuitButtonPressed),
  FXMAPFUNC(SEL_CLICKED, RainbruRPG::Gui::Launcher::ID_RENDERER, RainbruRPG::Gui::Launcher::onRenderComboPressed),
  FXMAPFUNC(SEL_DOUBLECLICKED, RainbruRPG::Gui::Launcher::ID_RENDERER, RainbruRPG::Gui::Launcher::onRenderComboDoubleClick),

};

FXIMPLEMENT(RainbruRPG::Gui::Launcher,FXMainWindow,LauncherMap,ARRAYNUMBER(LauncherMap));


/** The constructor
  *
  * \param a The fox application instance the launcher will be used with
  *
  */
RainbruRPG::Gui::Launcher::Launcher(FXApp * a)
   :FXMainWindow(a,"RainbruRPG launcher",NULL,NULL,DECOR_ALL,0,0,413,300){

  cbQuality=NULL;
  lbRend=NULL;
  criticalError=false;
  criticalMsg="";


  const char* banFN=USER_INSTALL_PREFIX"/share/RainbruRPG/data/fox/baniere.tga";
  FXImage *img=this->loadImage(banFN);

  // frame construction
  FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X);
  // The image
  new FXImageFrame( frame, img);

  FXMatrix* frMatrix=new FXMatrix(frame, 2, 
		   LAYOUT_FILL_X|MATRIX_BY_COLUMNS|LAYOUT_BOTTOM, 0, 0, 0, 
				  0, DEFAULT_SPACING, DEFAULT_SPACING, 
				  DEFAULT_SPACING,DEFAULT_SPACING,  
				  DEFAULT_SPACING, 20);



  // The quality static text
  new FXLabel(frMatrix, "Quality snapshot",  NULL,LAYOUT_FILL_COLUMN);


  // The snapshot combobox
  createSnapCombo( frMatrix );

  // The buttons
  FXMatrix* frButtons=new FXMatrix(frMatrix,LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
  FXButton* btnPlay= new FXButton(frButtons,"Play",
				  NULL,this,Launcher::ID_BTN_PLAY, 
				  BUTTON_NORMAL|LAYOUT_FIX_WIDTH,0,0,120);

  FXButton* btnOpt= new FXButton(frButtons,"Options", NULL,this,
				 Launcher::ID_BTN_OPTS,
				 LAYOUT_FILL_X|BUTTON_NORMAL);
  if (criticalError){
    btnOpt->disable();
    btnPlay->disable();
  }

  new FXButton(frButtons,"Quit", NULL,this,Launcher::ID_BTN_QUIT, 
	       LAYOUT_FILL_X|BUTTON_NORMAL);

  createRenderCombo( frMatrix );

 }


/** The default destructor
  *
  *
  */
RainbruRPG::Gui::Launcher::~Launcher(){
  //  delete wm_icon_small;
  //  delete wm_icon_big;
}


/** The FOX-Toolkit create method
  *
  * It creates and execute a LanguageSelector instance.
  *
  */
void RainbruRPG::Gui::Launcher::create(){
   FXMainWindow::create();
   show(PLACEMENT_SCREEN);

   if (criticalError){
     FX::FXMessageBox::error(getParent(), FX::MBOX_OK,
			     "Critical error",criticalMsg); 
   }
   else{
     xmlLanguage xl;
     if (xl.isLastUsedEmpty()){
       LanguageSelector ls( getApp());
       ls.execute(PLACEMENT_SCREEN);
     }
   }
 }


/** The signal receiver for the Play button
  *
  * \param obj Internally used by FOX toolkit
  * \param sel Internally used by FOX toolkit
  * \param ptr Internally used by FOX toolkit
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::Launcher::
onPlayButtonPressed(FXObject * obj , FXSelector sel ,void* ptr) {

  OptionManager::getSingleton().setLastUse( cbQuality->getText().text() );
  getApp()->stop(999);

  return 1;
} 


/** A TGA image loading generic function
  *
  * \param filename The filename of the image to load
  *
  * \return A pointer to a FXImage structure containing the tga image datas
  *
  */
FX::FXImage* RainbruRPG::Gui::Launcher::loadImage(const char* filename){

  FX::FXImage* img=new FX::FXTGAImage(getApp(),
			NULL,IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
  if(img){
    FXFileStream stream;
    if(stream.open(filename,FXStreamLoad)){
      img->loadPixels(stream);
      stream.close();
      img->create();
    }
  }

  return img;
}

/** The signal receiver for the Options button
  *
  * It creates a LauncherOptions instance, asks the OptionManager to load
  * the first snapshot found and execute the LauncherOptions dialog.
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::Launcher::
onOptionsButtonPressed(FXObject *o,FXSelector s,void* v){
  LauncherOptions lo( getApp());
  
  // get the snapshot list
  tSnapshotList::const_iterator iter;
  xmlOptions xmlo;
  tSnapshotList* snapList=xmlo.getSnapshotList();
  
  // set the first snapshot as current one
  if (snapList){
    const char* firstOne=(*snapList->begin());
    OptionManager::getSingleton().loadSnapshot(firstOne);
  }
  
  lo.update();
  bool ret=lo.execute();
  
  if (ret)
    std::cout << "LauncherOptions returns TRUE" << std::endl;
  else
    std::cout << "LauncherOptions returns FALSE" << std::endl;
  
  
  // Update the snapshot list combobox
  createSnapCombo(NULL);
  
  return 1;

}

/** The signal receiver for the Quit button
  *
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::Launcher::
onQuitButtonPressed(FXObject * o,FXSelector s,void* v){
  getApp()->exit();

  return 1;
}

/** Creates the snapshot combobox
  *
  * \param parent The parent of the Combobox (where it is created)
  *
  */
void RainbruRPG::Gui::Launcher::createSnapCombo(FXComposite* parent){
  // The snapshots comboBox
  if (!cbQuality){
    cbQuality=new FXComboBox( parent, 31, NULL, 0, 
			      COMBOBOX_STATIC||LAYOUT_FIX_WIDTH|LAYOUT_RIGHT,
			      0, 0, 200 );
  }
  else{
    cbQuality->clearItems();
  }    

  // get the snapshot list
  tSnapshotList::const_iterator iter;
  xmlOptions xmlo;
  tSnapshotList* snapList=xmlo.getSnapshotList();
  if (!snapList){
    LOGE("Cannot get the snapshot list");
    criticalError=true;
    criticalMsg="Cannot locate or load the options.xml file.\n\n"
                "The play and options buttons are disabled\n"
                "to prevent SEGFAULT crash.\n\n"
                "Please examine the log file and try again.";
    cbQuality->appendItem("disabled");
    cbQuality->disable();
  }
  else{
    // setting the number of visible elements
    int i=snapList->size();
    if (i>10) i=10;
    cbQuality->setNumVisible(i);

    // populate the combo box
    if (snapList){
      for (iter=snapList->begin(); iter != snapList->end(); iter++){
	cbQuality->appendItem((*iter));
      }
    }

    // Preselect the lastUsed snapshot
    const char* lastUsed = OptionManager::getSingleton().getLastUse();
    FXint it= cbQuality->findItem(lastUsed);
    cbQuality->setCurrentItem(it);
  }
}

/** Creates and feed the renderes combobox
  *
  * \param parent The layout the combobox will be created in
  *
  */
void RainbruRPG::Gui::Launcher::createRenderCombo(FXComposite* parent){ 

  // The renderers list box
  lbRend =new FXList(parent, this,ID_RENDERER,LIST_SINGLESELECT|
		     LAYOUT_FILL_Y|LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);

 
  Ogre::RenderSystemList* renderList=Ogre::Root::getSingleton()
    .getAvailableRenderers();


  Ogre::RenderSystemList::iterator renderIterator;	
    
  for( renderIterator= renderList->begin(); 
       renderIterator != renderList->end();
       renderIterator++){
    
    lbRend->appendItem((*renderIterator)->getName().c_str());

  } 
  
}

/** The callback of the Rnderers combobox (click event)
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::Launcher::
onRenderComboPressed(FXObject *o,FXSelector s,void* v){
  LOGI("Renderer selection changed");
  FXint i=lbRend->getCurrentItem();

  GameEngine::getSingleton().setRender(lbRend->getItemText(i).text());

  return 1;
}

/** The callback of the Renderers combobox (double click event)
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::Launcher::
onRenderComboDoubleClick(FXObject *o,FXSelector s,void* v){
  LOGI("Renderer selection double-clicked");

  return 1;
}
