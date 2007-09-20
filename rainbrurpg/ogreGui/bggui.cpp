

#include "bggui.h"



void BetaGUI::GUI::injectBackspace(unsigned int x, unsigned int y){
  injectKey("!b",x,y);
}

void BetaGUI::GUI::destroyWindow(Window *w){
  mXW=w;
}
