/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file netflooder/floodpanel.cpp
  * Implements the options panel of the flooding tool
  *
  */

#include "floodpanel.h"

#include <logger.h>
#include <fox-1.6/FXMessageBox.h>

/** To avoid multiple definition of PI (defined by fxdefs.h 
  * and common/chartbase.h)
  */
#undef PI

#include "ftreliable.h"
#include "chartviewer.h"

/** The Fox-toolkit event mapping 
  *
  * This map is needed by the Fox-Toolkit event model. It defines
  * the event used by the 
  * \ref RainbruRPG::Gui::FloodPanel "FloodPanel" class.
  *
  */
FXDEFMAP(RainbruRPG::Gui::FloodPanel) FloodPanelMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FloodPanel::ID_NYI, RainbruRPG::Gui::FloodPanel::onNotYetImplemented),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FloodPanel::ID_TEST_COMBO, RainbruRPG::Gui::FloodPanel::onTestComboChanged),
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::FloodPanel::ID_RUN, RainbruRPG::Gui::FloodPanel::onRunClicked),

};

/** Declares the implementation of the class 
  *
  * This statement tells to Fox-Toolkit that the 
  * \ref RainbruRPG::Gui::FloodPanel "FloodPanel" class
  * uses the FloodPanelMap event map.
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::FloodPanel,FXPacker,FloodPanelMap,ARRAYNUMBER(FloodPanelMap));

/** The constructor
  *
  * The parent must not be NULL
  *
  * \param parent The parent composite
  * \param opts The FOX construction parameter
  * \param c The enet client used for connection
  *
  */
RainbruRPG::Gui::FloodPanel::
FloodPanel(FXComposite *parent,FXuint opts, EnetFlooderClient* c)
  :FXPacker(parent, opts)
{
  selectedTest=0;
  client=c;

  FXVerticalFrame *root = new FXVerticalFrame(this,
             LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // The help label
  FXString lab="The connection to the server is successfull. You can now "
    "choose flooding options.";
  FXLabel* labHelp=new FXLabel(root, lab);

  // The progress bar frame
  FXVerticalFrame *frProg = new FXVerticalFrame(root,
             LAYOUT_FILL_X);
  pgGlobal=new  FXProgressBar(frProg, this, ID_NYI, 
	PROGRESSBAR_NORMAL|LAYOUT_FILL_X|PROGRESSBAR_PERCENTAGE );
  pgGlobal->setTotal(5);

  pgStep=new  FXProgressBar(frProg, this, ID_NYI, 
	PROGRESSBAR_NORMAL|LAYOUT_FILL_X|PROGRESSBAR_PERCENTAGE );
  pgStep->setTotal(5);

  // The test combobox
  FXLabel* labTests=new FXLabel(frProg, "Available tests :");
  FXComboBox* cbTest=new FXComboBox(frProg, 0, this, ID_TEST_COMBO, 
				    COMBOBOX_STATIC|LAYOUT_FILL_X);

  cbTest->appendItem("All test - Perform all available tests (may be long)");
  cbTest->appendItem("---------------");
  cbTest->setNumVisible(5);

  // The buttons
  FXHorizontalFrame *frButtons = new FXHorizontalFrame(frProg,
             LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
  FXButton* btnRun=new FXButton(frButtons, "Flood", NULL, this, 
				ID_RUN, BUTTON_NORMAL|LAYOUT_CENTER_X);


  // TestList
  testList=new tFlooderTestList();
  ftReliable* testReliable=new ftReliable();
  testList->push_back(testReliable);

  testReliable->sigProgressOneStep.connect(sigc::mem_fun(this, 
     &RainbruRPG::Gui::FloodPanel::slotProgressOneStep));


  feedTestCombo(cbTest);
}

/** The destructor
 *
 */
RainbruRPG::Gui::FloodPanel::~FloodPanel(){
  delete pgGlobal;
  delete pgStep;

  delete testList;
}

/** The FOX-Toolkit create method
  *
  * It creates and execute a FloodPanel instance.
  *
  */
void RainbruRPG::Gui::FloodPanel::create(){
  FXPacker::create();
  this->show();
}


/** The NotYetImplemented callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FloodPanel::
onNotYetImplemented(FXObject * o,FXSelector s,void* v){
  LOGW("Not yet implemented");
  return 1;
}

/** Feed the combobox containing all test with the content of the testList
  *
  * \param cb The combo box to feed
  *
  */
void RainbruRPG::Gui::FloodPanel::feedTestCombo(FXComboBox* cb){
  LOGI("feedTestCombo called");

  tFlooderTestList::const_iterator iter;
  // Iterate through list and output each element.
  for (iter=testList->begin(); iter != testList->end(); iter++){
    LOGI("One test found");
    FXString s;
    s=(*iter)->getName();
    s+=" (";
    s+=(*iter)->getDescription();
    s+=")";
    cb->appendItem(s);
  }
}

/** The test list combobox callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FloodPanel::
onTestComboChanged(FXObject* o,FXSelector s,void* v){
  LOGI("onTestComboChanged called");

  FXComboBox* comb=(FXComboBox*)o;
  int i= comb->getCurrentItem();
  LOGCATS("Selected item :");
  LOGCATI(i);
  LOGCAT();
}

/** The flood button callback
  *
  *
  * \param o A parameter used for FOX callbacks
  * \param s A parameter used for FOX callbacks
  * \param v A parameter used for FOX callbacks
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::FloodPanel::
onRunClicked(FXObject* o,FXSelector s,void* v){
  LOGI("onRunClicked called");

  if (selectedTest>-1){

    if (selectedTest==0){
      performAllTests();
    }
    else{
      performTest(selectedTest-2);
    }

  }
  else{
    LOGW("Cannot performs tests, no test selected");
  }
}

/** Performs the given test
  *
  * The given parameter is the index of the text in the list, not in the
  * combo.
  *
  * \param i The index of the test in the list
  *
  */
void RainbruRPG::Gui::FloodPanel::performTest(int i){
  int j=0;

  tFlooderTestList::const_iterator iter;
  // Iterate through list and output each element.
  for (iter=testList->begin(); iter != testList->end(); iter++){
    if (j==i){
      pgStep->setTotal((*iter)->getTotalSteps());
      pgStep->setProgress(0);
      (*iter)->run(client);
      break;
    }
    else{
      j++;
    }
  }
}

/** Performs all tests
  *
  */
void RainbruRPG::Gui::FloodPanel::performAllTests(){
  tFlooderTestList::const_iterator iter;
  // Iterate through list and output each element.
  for (iter=testList->begin(); iter != testList->end(); iter++){
    pgStep->setTotal((*iter)->getTotalSteps());
    pgStep->setProgress(0);
    (*iter)->run(client);

  }

  // Show the result of all tests
  for (iter=testList->begin(); iter != testList->end(); iter++){
    ChartViewer cw(getApp(), (*iter)->getImageFilename(), 
		   (*iter)->getImageWidth(), (*iter)->getImageHeight());

    cw.execute(PLACEMENT_SCREEN);
  }
}

/** Changes the client flooded
  *
  * \param c The client to be flooded
  *
  */
void RainbruRPG::Gui::FloodPanel::setClient(EnetFlooderClient* c){
  this->client=c;
}

/** The tests are in progress
  *
  */
void RainbruRPG::Gui::FloodPanel::slotProgressOneStep(){
  LOGI("slotProgressOneStep called");
  pgStep->increment(1);

}
