/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "chartviewer.h"

#include <fox-1.6/FXPNGImage.h>



FXDEFMAP(RainbruRPG::Gui::ChartViewer) ChartViewerMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ChartViewer::ID_NYI, 
	    RainbruRPG::Gui::ChartViewer::onNotImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::ChartViewer::ID_CLOSE, 
	    RainbruRPG::Gui::ChartViewer::onClose),


};

FXIMPLEMENT(RainbruRPG::Gui::ChartViewer,FXDialogBox,
	    ChartViewerMap,ARRAYNUMBER(ChartViewerMap));



/** Default constructor
  *
  * \param a The FXApp pointer needed to create the widget
  * \param filename The filename of the image to show
  * \param width The width of the image to show
  * \param height The height of the image to show
  *
  */
RainbruRPG::Gui::ChartViewer::
ChartViewer(FXApp * a, const char* filename, int width, int height)
   :FXDialogBox(a,"Netflooder chart's viewer", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER|DECOR_SHRINKABLE|DECOR_STRETCHABLE|DECOR_MENU, 100, 100, 
		width+30, height+30+25, 10, 10, 10, 10, 4, 4){
 
  FXImage *img=this->loadImage(filename);

  // frame construction
  FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y);
  // The image
  new FXImageFrame( frame, img);

  FXButton* btnRun=new FXButton(frame, "Close", NULL, this, 
				ID_CLOSE, BUTTON_NORMAL|LAYOUT_CENTER_X);

}


/** Default destructor
  *
  */
RainbruRPG::Gui::ChartViewer::~ChartViewer(){
}


/** A method needed by the FOX-toolkit
  *
  */
void RainbruRPG::Gui::ChartViewer::create(){
  FXDialogBox::create();
   show(PLACEMENT_DEFAULT );
 }

/** An event receiver used during development
  *
  * The widgets that send a usefull signal that have unimplemented
  * event handler are connected to this to avoid compilation errors.
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  */
long RainbruRPG::Gui::ChartViewer::onNotImplemented(FXObject * o,
							FXSelector s,
							void* v){
  LOGW("This slot is not implemented");
  return 1;

}

/** A PNG image loading generic function
  *
  * \param filename The filename of the image to load
  *
  * \return A pointer to a FXImage structure containing the PNG image datas
  *
  */
FX::FXImage* RainbruRPG::Gui::ChartViewer::loadImage(const char* filename){

  FX::FXImage* img=new FX::FXPNGImage(getApp(),
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

/** An event receiver used during development
  *
  * The widgets that send a usefull signal that have unimplemented
  * event handler are connected to this to avoid compilation errors.
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  */
long RainbruRPG::Gui::ChartViewer::onClose(FXObject *o,FXSelector s,void* v){

  this->handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_CANCEL), NULL);

}
