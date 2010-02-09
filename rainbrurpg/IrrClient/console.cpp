/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

#include "console.h"

#include <logger.h>
#include "stringconv.h"
#include "irrfontmanager.h"

#include <iostream>

/** The singleton's constructor
  *
  * It gets all the Irrlicht values ( device, driver, scene manager
  * and guiEnvironment) from the GameEngine. Then it sets scrollValue
  * to 18, create the Tokenizer and TokenizerDbg instances and call
  * initObjectsVector().
  *
  */
void RainbruRPG::Exception::Console::init(){
  LOGI("Initializing Console...");
  this->irrDevice  = GameEngine::getSingleton().getIrrlichtDevice();
  this->irrDriver  = GameEngine::getSingleton().getIrrlichtDriver();
  this->irrSmgr    = GameEngine::getSingleton().getIrrlichtSmgr();
  this->irrGui     = GameEngine::getSingleton().getIrrlichtGui();

  prompt=L"";
  scrollValue=18;
  cmdIndex=0;

  initObjectsVector();

  tok=new Tokenizer();
  tokDbg=new TokenizerDbg();
}

/** The singleton's style destructor
  *
  * It calls cleanupObjectsVector().
  */
void RainbruRPG::Exception::Console::cleanup(){
  this->irrDevice  = NULL;
  this->irrDriver  = NULL;
  this->irrSmgr    = NULL;
  this->irrGui     = NULL;

  cleanupObjectsVector();

  delete tok;
  tok=NULL;
  delete tokDbg;
  tokDbg=NULL;

  irrTab=NULL;
  consoleEdit=NULL;
  consoleList=NULL;
  consolePrompt=NULL;
  scrollbar=NULL;
  consoleIndex=NULL;
}

/** Graphically creates the console
  *
  * This method creates the console widgets and call initScrollbar().
  */
void RainbruRPG::Exception::Console::createConsole(){
  if (!irrTab){
    LOGI("Creating a new console...");
    rect<s32> r=irrGui->getVideoDriver()->getViewPort( );
    irrTab=irrGui->addTab(r, 0, 1001);
    
    IGUIWindow* window = irrGui->addWindow( 
					   core::rect<s32>(2, 2, 502 , 240), 
					   false, // modal?
					   L"Console", irrTab);
    
    consoleList=irrGui->addListBox( core::rect<s32>(2,22,500,213),
				    window,-1,true);

    consolePrompt=irrGui->addStaticText(prompt.c_str(),
					core::rect<s32>(2,213,82,238),
					true, false, window);

    consoleEdit=irrGui->addEditBox( L"",core::rect<s32>(82,213,460,238),
				    true,window);

    consoleIndex=irrGui->addStaticText(prompt.c_str(),
				       core::rect<s32>(462,213,500,238),
				       true, false, window);

    consoleList->addItem(L"RainbruRPG debugging console");
    consoleList->addItem(L"You can try 'help'");

    this->initScrollbar();
    this->showCmdIndex();

    IrrFontManager::getSingleton().setWidgetFont( consolePrompt, 
						  IFM_COURRIER, 12 );
    IrrFontManager::getSingleton().setWidgetFont( consoleIndex, 
						  IFM_COURRIER, 12 );
    IrrFontManager::getSingleton().setWidgetFont( consoleEdit, 
						  IFM_COURRIER, 12 );

    this->setPrompt();

  }
  else{
    LOGI("A console already exists, simply show it.");
    irrTab->setVisible(true);
  }

  irrGui->setFocus(consoleEdit);
}

/** This method is called by the Events receiver to hide the console */
void RainbruRPG::Exception::Console::hide(){
  if (irrTab);
   irrTab->setVisible(false);
}

/** Write the prompt text in the IGUIStaticText consolePrompt
  *
  *
  */
void RainbruRPG::Exception::Console::setPrompt(){
  stringw a;
  a.append(prompt);
  a.append(L">");
  consolePrompt->setText(a.c_str());
}

/** Print a Command not found message containing the command text
  *
  * \param s the command
  *
  */
void RainbruRPG::Exception::Console::commandNotFound( irr::core::stringw s){
  irr::core::stringw a;
  a=L"Command not found : '";
  a.append( s );
  a.append( "'" );

  showIndentedMessage(a.c_str());
}

/** Remove all the lines of the listbox
  *
  * This method is called when we enter the \c clear command. 
  */
void RainbruRPG::Exception::Console::clearConsole(){
  consoleList->clear();
}

/** Shows a basic help in the lisbBox
  *
  * This method is called when we enter the \c help command.
  */
void RainbruRPG::Exception::Console::showHelp(){
 consoleList->addItem(L"Keyboard usage :");
  showIndentedMessage(L"The PAGEUP and PAGEDOWN keys scroll the console");
  showIndentedMessage(L"The HOME and END keys go to the first and the last line");

  consoleList->addItem(L"The simple commands :");
  this->showIndentedMessage(L"clear : will cleanup the console");
  this->showIndentedMessage(L"count : shows you the number of available commands");
  this->showIndentedMessage(L"help : shows you this help message");
  this->showIndentedMessage(L"list : shows all the commands already passed");
  this->showIndentedMessage(L"show : lists all the ocjects name");
}

/** Return a space to place before the message of all lines
  *
  * Actually, all the messages are indented with 8 spaces.
  *
  * \return the space string
  */
irr::core::stringw RainbruRPG::Exception::Console::getIndentedString(){
  irr::core::stringw a=L"        ";
  return a;
}

/** Add an indented line to the listbox to show a message
  *
  * It use the getIndentedString() function to get the right space
  * number (indentation) and append the message to it. Then adds this
  * new line to the listBox.
  *
  * \param s The message to show
  */
void RainbruRPG::Exception::Console::showIndentedMessage
                                   ( irr::core::stringw s){

  irr::core::stringw a=this->getIndentedString();
  a.append( s );
  consoleList->addItem(a.c_str());
}

/** Set the listbox always showing the last line
  *
  * This code come from the Irrlicht forum. Thanks to jox.
  *
  * In the listbox the scrollbar max depends on the number of items in
  * it. 0x7FFFFFFF is a hexadecimal value. If the int would be
  * unsigned (no minus values possible) the highest value would be
  * 0xFFFFFFFF (all bits set).
An unsigned uses one bit for the (minus) sign. So 0x7FFFFFFF sets all
  * bits exept the sign bit to get the highest positive value. This
  * value is maybe overkill , 10000 would probaly do as well, but its
  * theoretically the most optimal value in this situation.
  */
void RainbruRPG::Exception::Console::setEnd(){
  scrollbar->setPos(0x7FFFFFFF);
}

/** The listbox's scrollbar access initialization
  * 
  * The scrollbar of the listbox is created at the same time but no
  * function in the Irrlicht API provides acces to the scrollbar. So
  * we must keep a pointer to it that we initialize one time by a call
  * in the createConsole() method. 
  *
  */
void RainbruRPG::Exception::Console::initScrollbar(){
  core::list<gui::IGUIElement*>::Iterator it = 
    consoleList->getChildren().getLast();
  scrollbar = static_cast<gui::IGUIScrollBar*>((*it));
}

/** Go to the first line of the listbox
  *
  * When we hit the HOME key, the event receiver
  * (RainbruRPG::Events::erConsole) call this 
  * method to go to the first line of the console.
  */
void RainbruRPG::Exception::Console::setHome(){
  scrollbar->setPos(0);
}

/** Set the scrollbar up according to the \c scrollvalue value
  *
  * This method is called by the console event receiver
  * (RainbruRPG::Events::erConsole) when we hit the UP arrow key.
  *
  */
void RainbruRPG::Exception::Console::setPageUp(){
  int i=scrollbar->getPos();
  i-=scrollValue;
  if (i<0) 
    i=0;
  scrollbar->setPos(i);
}

/** Set the scrollbar down according to the \c scrollvalue value
  *
  * This method is called by the console event receiver
  * (RainbruRPG::Events::erConsole) when we hit the DOWN arrow key.
  *
  */
void RainbruRPG::Exception::Console::setPageDown(){
  int i=scrollbar->getPos();
  scrollbar->setPos(i+scrollValue);
}

/** Treat the simple command
  *
  * simple commands are in only one word :
  * - clear;
  * - help;
  * - list.
  * - show
  * - count
  *
  * \return true if the command is found (we stop all search), false
  *         to continue searching.
  */
bool RainbruRPG::Exception::Console::simpleCommand( irr::core::stringw s){
  LOGI("Simple command treating...");
  bool ret=false;

  if(s==L"clear"){
    LOGI("Clearing console...");
    this->clearConsole();
    ret=true;
  }

  else if (s==L"help"){
    this->showHelp();
    ret=true;
  }

  else if (s==L"list"){
    this->showList();
    ret=true;
  }

  else if (s==L"show"){
    this->showAllObjects();
    ret=true;
  }

  else if (s==L"count"){
    this->showCmdCount();
    ret=true;
  }

  return ret;
}

/** Show the list of all the commands stored in cmdVector
  *
  */
void RainbruRPG::Exception::Console::showList(){
  int indx;
  stringw a,b;

  for (indx = 0; indx < cmdVector.size(); indx++){
    a=stringw(indx+1);
    a+=": ";
    a+=cmdVector[indx].prompt;

    b=cmdVector[indx].cmd;

    a.append(" > " );
    a.append( b );
    this->showIndentedMessage( a );
  } 
}

/** Set the the value of cmdIndex+1 in the consoleIndex staticBox
  *
  */
void RainbruRPG::Exception::Console::showCmdIndex(){
  stringw a;
  a=stringw(cmdIndex+1);
  consoleIndex->setText(a.c_str());
}

/** Provides the previous command mecanism
  *
  * erConsole.cpp call this method if the UP key is pressed.
  *
  *
  */
void RainbruRPG::Exception::Console::setUp(){
  cmdIndex--;

  if(cmdIndex<0)
    cmdIndex=0;

  this->showCmdIndex();

  this->showPrevCmd();

}

/** Provides the next command mecanism
  *
  * erConsole.cpp call this method if the DOWN key is pressed.
  *
  *
  */
void RainbruRPG::Exception::Console::setDown(){

  cmdIndex++;

  if(cmdIndex>cmdVector.size())
    cmdIndex=cmdVector.size();

  this->showCmdIndex();
  this->showPrevCmd();
}

/** Set the previous command and its namespace in the static text
  * widgets
  *
  * Called by setDown().
  */
void RainbruRPG::Exception::Console::showPrevCmd(){
  stringw a, b;

  if (!cmdVector.empty()){
    if (cmdIndex<cmdVector.size()){
      a+=cmdVector[cmdIndex].prompt;
      a+=L">";
      b=cmdVector[cmdIndex].cmd;
      
      consoleEdit->setText( b.c_str() );
      consolePrompt->setText(a.c_str() );
    }
    else {
      setPrompt();
      consoleEdit->setText(L"");
    }
  }
}

/** Load all the ConsoleObjects in the vector 
  *
  */
void RainbruRPG::Exception::Console::initObjectsVector(){
  coCore* c=new coCore();
  objectsVector.push_back(c);
}

/** Show all the objects stored in the objectsVector
  *
  * We print the name and th description of each object.
  */
void RainbruRPG::Exception::Console::showAllObjects(){
  LOGI("Showing objects list...");

  unsigned int indx;
  stringw a;

  if (!objectsVector.empty()){
    
    for (indx = 0; indx < objectsVector.size(); indx++){

      a=objectsVector[indx]->getName();
      a+=L" : ";
      a+=objectsVector[indx]->getDesc();
      
      this->showIndentedMessage( a );
    } 
  }
}

/** Clear the objectVector and the objects it contains
  *
  */
void RainbruRPG::Exception::Console::cleanupObjectsVector(){
  LOGI("Cleaning up objects vector...");

  unsigned int indx;
  if (!objectsVector.empty()){
    
    for (indx = 0; indx < objectsVector.size(); indx++){
      delete objectsVector[indx];
    } 
  }
    objectsVector.clear();
 
}

/** Get the errors returned by the tokenizer
  *
  * Show the errors message in the console
  *
  * return \c true if we must parse the command (no errors), \c false
  *        if the tokenizer has found an error.
  *
  */
bool RainbruRPG::Exception::Console::getTokenizerError( tTokentizerReturn* t){
  bool ret =false;

  LOGI("Treating Tokenizer errors...");

  switch(t->err){
  case TET_EMPTY: 
    //   showIndentedMessage(L"The command is empty");
    LOGI("The command is empty");
    ret=false;
    break;

  case TET_MISSING_QUOTE:
    showIndentedMessage(L"A quote is missing");
    ret=false;
    break;

  case TET_MISSING_BRACKET:
    showIndentedMessage(L"A bracket is missing");
    ret=false;
    break;

  case TET_UNKNOW_SEPARATOR_MISSING:
    showIndentedMessage(L"An unknown separator (?) is missing");
    ret=false;
    break;

  default:
    ret=true;
  }

  return ret;
}

/** ISN'T IN USE
  *
  * \param t the answer of the tokenizer
  * \todo Use this method
  */
void RainbruRPG::Exception::Console::treatCommandType(tTokentizerReturn* t ){
  LOGI("Debugging command type :");
  switch(t->cmdType){
  case TCT_SIMPLE: 
   LOGI("  command type is SIMPLE COMMAND");
    break;

  case TCT_DOUBLE:
    LOGI("  command type is DOUBLE COMMAND");
    break;

  case TCT_TRIPLE:
    LOGI("  command type is TRIPLE COMMAND");
    break;

  case TCT_QUAD:
    LOGI("  command type is QUAD COMMAND");
    break;

  case TCT_QUINT:
    LOGI("  command type is QUINT COMMAND");
    break;

  default:
    LOGI("  WARNING : no command type defined");

  }
}

/** Treat a double command
  *
  *
  *
  */
bool RainbruRPG::Exception::Console::doubleCommand( tTokentizerReturn* r){
  bool ret=true;

  LOGI("Treating a double command");

  if (r->cmd=="show"){
    LOGI("  This is a show command");
    commandShowObject( r->obj );
  }
  else if (r->cmd=="using"){
    LOGI("  This is a using command");
    commandUsingObject( r->obj );
  }
  else{
    LOGI("  Unknown Double command");
    ret=false;
  }


  return ret;
}



/** show an ObjectAttribute in the console
  *
  * This method is called by the commandshowObject method for each
  * attribute found
  */
void RainbruRPG::Exception::Console::showObjectAttribute(ObjectAttribute* a){
  std::string b;
  b.append(a->getAccessText());
  b.append(" ");
  b.append(a->getTypeText());
  b.append(" ");
  b.append(a->getName());
  b.append(" ");
  b.append(a->getValueText());

  this->showIndentedMessage(StringConv::getSingleton().stow(b));
}

/** Count the exact number of command available in the console and show
  * the total
  *
  *
  */
void RainbruRPG::Exception::Console::showCmdCount(){
  ConsoleObject*   co=0;
  int c=0;

  // The simple commands
  // count the if block in the Console::simpleCommand method
  c+=5;

  // one show command for each object
  c+=objectsVector.size();

  // one using command for each object
  c+=objectsVector.size();

  // The using none command
  c++;

  // For each Object
  unsigned int indx;
  for (indx = 0; indx < objectsVector.size(); indx++) {
    co=objectsVector[indx];
    c+=showObjCount(co);
  } 


  // The output message
  irr::core::stringw a=c;
  irr::core::stringw b="Total available console commands : ";

  b.append(a);
  showIndentedMessage( b );

}

/** Count the exact number of command available for an ConsoleObject
  *
  * This function is used by showCmdCount() for any objects.
  *
  */
int RainbruRPG::Exception::Console::showObjCount(ConsoleObject* co){
  int ret=0;

  tAttrbList*      al=0;

  tAttrbList::iterator alIter;

  al=co->getAttrbList();

  for (alIter=al->begin(); alIter != al->end(); alIter++){
   ret+=(*alIter)->count();
  }

  cout << "Console::showObjCount(ConsoleObject* co)" << ret << endl;
  return ret;
}

/** the \c show \c object command implementation
  *
  * This function is called by doubleCommand( tTokentizerReturn* ) if
  * the first token is a show
  */
void RainbruRPG::Exception::Console::commandShowObject( std::string s){
  ConsoleObject*   co=0;
  tAttrbList*      al=0;
  ObjectAttribute* oa=0;
  tAttrbList::iterator alIter;

  co=getObjectByName(s);

  // We haven't found any object name
  if (co==0){
    LOGI("  No Object name matches the show command argument");
  }
  else{
    LOGI("  show Object name matches");
    // All the attributes of the found object

    al=co->getAttrbList();

    for (alIter=al->begin(); alIter != al->end(); alIter++)  {
      //    *nums_iter = *nums_iter + 3; // Modify each element.

      showObjectAttribute(*alIter);
    }
  }

  co=NULL;
  al=NULL;
  oa=NULL;

}

/** Treat the \c using \c object command
  *
  * If the s parameter is none, we set prompt to L"".
  *
  * We check if the object exists. If it exists, the name is
  * passed to the prompt.
  */
void RainbruRPG::Exception::Console::commandUsingObject( std::string s){
  ConsoleObject*   co=0;

  if (s=="none"){
    prompt=L"";
    this->setPrompt();
  }
  else{
    co=getObjectByName(s);
    
    // We haven't found any object name
    if (co==0){
      LOGI("  No Object name matches the using command argument");
      showIndentedMessage("The parameter doesn't match any object name");
    }
    else{
      LOGI("  using Object name matches");
      
      this->prompt=StringConv::getSingleton().stow(s);
      this->setPrompt();
    

    }
  }
  co=NULL;
}


/** A method called when the user hit the Enter key
  *
  */
void RainbruRPG::Exception::Console::enter(){
  irr::core::stringw a,c;

  bool found;

  a=prompt;
  a.append(L" > ");
  c=consoleEdit->getText();
  c.make_lower();

  a.append( c );
  consoleList->addItem(a.c_str());
  consoleEdit->setText(L"");
  this->setPrompt();

  // Add the command to the cmdVector
  consoleCmd cCmd;
  cCmd.prompt=prompt;
  cCmd.cmd=c;
  cmdVector.push_back(cCmd);

  // The command is passed to the Tokenizer and the tokenizer debugger
  tTokentizerReturn tokRet=tok->setText( 
		      StringConv::getSingleton().wtoc( c ) );
  StringConv::getSingleton().freeTte();

  tok->clear();
  if (c.size()!=0){

    treatCommandType(&tokRet);

    // The command string pass into all command searching functions
    found=simpleCommand(c);
    
    // If a simple command hasn't been found, we test the
    // doubleCommand fonction

    if (!found){
      found=doubleCommand(&tokRet);

      if (!found){
	found=tripleCommand(&tokRet);

	if (!found){
	  found=quadCommand(&tokRet);

	  if (!found)
	    commandNotFound(c);
	}
      }
    }    
    
    // show index of current 
    cmdIndex++;
    showCmdIndex();
  }
  this->setEnd();
}

/** Treat a triple command (with 3 tokens)
  *  
  * The first type of triple command is \c get \c obj.attrb 
  * 
  *
  * \return true if the command is found (used), false if we must
  *         continue parsing the tokens (command not found)
  */
bool RainbruRPG::Exception::Console::tripleCommand( tTokentizerReturn* r ){
  LOGI( "Treating triple comand" );
  bool ret=true;

  if (r->cmd=="get"){
    LOGI("  This is a get command");
    commandGetObjectAttribute( r );
  }
  else{
    LOGW("  Unknown Double command");
    ret=false;
  }

  return ret;
}

/** Treat a quad command (with 3 tokens)
  *
  * The first type of quad command is \c set \c obj.attrb \c val
  *
  * \return true if the command is found (used), false if we must
  *         continue parsing the tokens (command not found)
  */
bool RainbruRPG::Exception::Console::quadCommand  ( tTokentizerReturn* ){
  LOGI( "Treating quad comand" );
  return false;
}

/** Return a pointer to the ConsoleObject wich name is s
  *
  * \return a pointer to the rigth ConsoleObject or 0
  */
RainbruRPG::Exception::ConsoleObject* RainbruRPG::Exception::Console::
                                      getObjectByName( std::string s ){

  ConsoleObject*   co=0;

  // Get all object's name;
  unsigned int indx;
  for (indx = 0; indx < objectsVector.size(); indx++) {
    
    if (s==objectsVector[indx]->getName())
      co=objectsVector[indx];
    
  } 

  return co;
  co=NULL;
}

/** Return a pointer to the \c co's attribute named \c s
  *
  */
RainbruRPG::Exception::ObjectAttribute* RainbruRPG::Exception::Console::
                   getAttributeByName(ConsoleObject* co, std::string s){

  LOGI("Console::getAttributeByName method");

  ObjectAttribute* oa=0;
  tAttrbList::iterator alIter;
  tAttrbList*      al=0;

  al=co->getAttrbList();
  
  for (alIter=al->begin(); alIter != al->end(); alIter++)  {

    if (s==(*alIter)->getName()){

      
      oa=(*alIter);
    }
  }
  return oa;
  
}
/** treat the <code>get obj.attrb</code> command
  *
  * this method is called by tripleCommand( tTokentizerReturn* r ) if
  * it found the \c get command.
  *
  */
void RainbruRPG::Exception::Console::commandGetObjectAttribute
 			      ( RainbruRPG::Core::tTokentizerReturn* r ){

  LOGI("Console::commandGetObjectAttribute method");
  ObjectAttribute* oa=0;
  ConsoleObject*   co=0;

  // get the object
  co=getObjectByName(r->obj);

  // We haven't found any object name
  if (co==0){
    LOGI("  No Object name matches the get command argument");
    showIndentedMessage("The parameter doesn't match any object name");
  }
  else{
    LOGI("  get command Object name matches");

    // We must now have the attribute    
    oa=getAttributeByName( co, r->att );
    
    // The attribute name doesn't match any attribute in this object
    if (oa==0){
      LOGI("  The attribute passed to the GET command doesn't exist in this object");
    
    }
    else{
      LOGI("  The attribute passed to the GET has been found");
      this->showIndentedMessage(oa->getValueText());
    }
  }
  
  co=NULL;
}
