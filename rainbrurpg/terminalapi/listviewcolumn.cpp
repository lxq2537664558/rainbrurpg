#include "listviewcolumn.h"


/** The default constructor
  *
  * Initialize caption to "" and width to 5.
  *
  */
RainbruRPG::Terminal::ListViewColumn::ListViewColumn(){
  this->caption="";
  this->width=5;
}

/** The named constructor
  *
  * Initialize caption to c and width to 5.
  *
  * \param c The caption of the column
  *
  */
RainbruRPG::Terminal::ListViewColumn::ListViewColumn(const char* c){
  this->caption=c;
  this->width=5;

}


/** The named and sized constructor
  *
  * Initialize caption to c and width to w.
  *
  * \param c The caption of the column
  * \param w The width of the column
  *
  */
RainbruRPG::Terminal::ListViewColumn::ListViewColumn(const char* c, 
						     unsigned int w){
  this->caption=c;
  this->width=w;
}


/** The default destructor
  *
  *
  */
RainbruRPG::Terminal::ListViewColumn::~ListViewColumn(){

}

/** Change the caption of this column
  *
  * \param c The new caption
  *
  */
void RainbruRPG::Terminal::ListViewColumn::setCaption(const char* c){
  this->caption=c;
}

/** Gets the caption of this column
  *
  * \return The caption
  *
  */
const char* RainbruRPG::Terminal::ListViewColumn::getCaption(){
  return this->caption;
}

/** Set the width of this column
  *
  * \param w The new width
  *
  */
void RainbruRPG::Terminal::ListViewColumn::setWidth(unsigned int w){
  this->width=w;
}

/** Returns the width 
  *
  * \return The width value
  *
  */
unsigned int RainbruRPG::Terminal::ListViewColumn::getWidth(){
  return this->width;
}
