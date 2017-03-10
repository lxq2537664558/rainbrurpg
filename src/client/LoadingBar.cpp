/*
 * Copyright 2011-2017 Jerome Pasquier
 *
 * This file is part of rainbrurpg-client.
 *
 * rainbrurpg-client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rainbrurpg-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rainbrurpg-client.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "LoadingBar.hpp"

#include <CEGUI/WindowManager.h>

#include <CEGUI/Window.h>
#include <CEGUI/widgets/ProgressBar.h>

#include "Logger.hpp"

static Rpg::Logger static_logger("engine", Rpg::LT_BOTH);

LoadingBar::LoadingBar(const string& vTitle):
  title(vTitle),
  mWmgr(NULL),
  stepLabel(NULL),
  progressbar(NULL),
  stepSize(0.0f),
  currentStep(0)
{
  // Do not instanciate anything Ogre/CEGUI related here

  
}

void
LoadingBar::init()
{
  mWmgr = CEGUI::WindowManager::getSingletonPtr();

  CEGUI::Window* layoutWindow = mWmgr->loadLayoutFromFile("loading_bar.layout");

  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()
    ->addChild(layoutWindow);

  layoutWindow->setVisible(true);

  CEGUI::Window* titleLabel = layoutWindow->getChild("titleLabel");
  titleLabel->setProperty("Text", title);
  
  stepLabel = layoutWindow->getChild("stepLabel");
  stepLabel->setProperty("Text", stepNames[0]);

  progressbar = static_cast<CEGUI::ProgressBar*>
    (layoutWindow->getChild("ProgressBar"));

  
  /*

  // Create the parent window using unique name, makes it fullsize
  // and transparent
  mDialogWindow=mWmgr->createWindow("Vanilla/StaticImage", uniqueName);
  mDialogWindow->setProperty("Size", "{{1,0},{1,0}}");
  mDialogWindow->setProperty("FrameEnabled", "False");
  mDialogWindow->setProperty("BackgroundEnabled", "False");
  
  // Load the given layout file
  CEGUI::Window* layoutWindow = mWmgr->loadLayoutFromFile(mLayoutName);

  mRootWindow = CEGUI::System::getSingleton().getDefaultGUIContext().
    getRootWindow();
  mRootWindow->addChild(mDialogWindow);
  mDialogWindow->addChild(layoutWindow);

  mDialog = mDialogWindow->getChild("nyiRoot/winToolbar");
  
  hide();

  CEGUI::PushButton* btnNetPl = (CEGUI::PushButton *)mDialogWindow->
    getChild("nyiRoot/winToolbar/btnOk");
  btnNetPl->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CeguiDialog::onOk, this));
  */

  
}


LoadingBar::~LoadingBar()
{

}

size_t
LoadingBar::getStepNumber()
{
  return stepNames.size();
}


void
LoadingBar::addStep(const string& name)
{
  stepNames.push_back(name);
  adjustProgress();
}

void
LoadingBar::adjustProgress()
{
  stepSize = 1.0f / getStepNumber();

  if (progressbar)
    progressbar->setStepSize(stepSize);

  
  LOGI("Stepsize = " << stepSize);

}


float
LoadingBar::getStepSize()
{
  return stepSize;
}

void
LoadingBar::step()
{
  ++currentStep;

  if (stepLabel)
    stepLabel->setProperty("Text", stepNames[currentStep]);

  if (progressbar)
    progressbar->step();
}

size_t
LoadingBar::getCurrentStep()
{
  return currentStep;
}

