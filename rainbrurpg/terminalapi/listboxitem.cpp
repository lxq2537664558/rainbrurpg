#include "listboxitem.h"

/** The default constructor
  *
  * Creates a ListBoxItem with empty caption. The chack value is set
  * to false.
  *
  */
RainbruRPG::Terminal::ListBoxItem::ListBoxItem(){
  this->caption="";
  this->checked=false;
}

/** The named constructor
  *
  * \param caption The caption of the new item
  *
  */
RainbruRPG::Terminal::ListBoxItem::ListBoxItem(const char* caption){
  this->caption=caption;
  this->checked=false;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::ListBoxItem::~ListBoxItem(){

}

/** Is this item checked
  * 
  * \return \c true if this item is checked
  */
bool RainbruRPG::Terminal::ListBoxItem::isChecked(){
  return this->checked;
}

/** Set the checked value
  * 
  * \param b The new value of checked
  *
  */
void RainbruRPG::Terminal::ListBoxItem::setChecked(bool b){
  this->checked=b;
}

/** Get the caption of this item
  *
  * \return The caption of this item
  *
  */
const char* RainbruRPG::Terminal::ListBoxItem::getCaption(){
  return this->caption;
}

/** Set the caption of this item
  *
  * \param caption The new caption
  *
  */
void RainbruRPG::Terminal::ListBoxItem::setCaption(const char* caption){
  this->caption=caption;
}

/** Toggle the checked value
  *
  * If checked was \c true before the call, it will be \c false. If it was
  * \c false, it will be \c true.
  *
  */
void RainbruRPG::Terminal::ListBoxItem::toggle(){
  if (checked)
    this->checked=false;
  else
    this->checked=true;
}

