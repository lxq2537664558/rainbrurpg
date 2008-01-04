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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */
#include "terminalapp.h"

#include "logger.h"

/** The private default constructor
  *
  */
RainbruRPG::Terminal::TerminalApp::TerminalApp(){

}

/** The private default destructor
  *
  */
RainbruRPG::Terminal::TerminalApp::~TerminalApp(){

}

/** The initializer of the Singleton
  *
  * It sets the timeout private variable to 2, initialize the message
  * string and draw the message box.
  *
  */
void RainbruRPG::Terminal::TerminalApp::init(){
  timeout=2;
  keycodeboxWidth=6;
  message="Hit F10 for menubar";
  lastKeycode=-1;
  currentMenu=0;
  currentSubMenu=0;
  altKeycode=false;
  inMenu=false;
  inSubMenu=false;
  showingDialog=false;

  initTerminal (1, 1);
  initColors();
  draw();
}

/** The destructor of the singleton
  *
  */
void RainbruRPG::Terminal::TerminalApp::cleanup(){

}

/** Initialization of the signal handlers
  * 
  * each signal call a c function declared in hook.h
  */
void RainbruRPG::Terminal::TerminalApp::initSignals (void){
#ifdef SIGTSTP
   SLsignal (SIGTSTP, sigtstp_handler);
#endif
#ifdef SIGINT
   SLsignal (SIGINT, sigint_handler);
#endif
#ifdef SIGWINCH
   SLsignal (SIGWINCH, sigwinch_handler);
#endif
}

/** init the SLang terminal
  *
  * \param tty enable the tty terminal if not 0.
  * \param smg enable utf8 if not equal to 0.
  */
int RainbruRPG::Terminal::TerminalApp::initTerminal (int tty, int smg){
   /* Initialize an error handlee in case of error
    */
   SLang_Exit_Error_Hook = exit_error_hook;

   /* It is wise to block the occurance of display  related signals
    * while we are initializing. 
    */
   SLsig_block_signals ();
   SLtt_get_terminfo ();
   
   /* SLkp_init assumes that SLtt_get_terminfo has been called. */
   if (tty && (-1 == SLkp_init ())){
     SLsig_unblock_signals ();
     return -1;
   }
   
   initSignals ();
   
   if (tty) SLang_init_tty (-1, 0, 1);
#ifdef REAL_UNIX_SYSTEM
   if (tty) SLtty_set_suspend_state (1);
#endif
   if (smg){
     //     (void) SLutf8_enable (-1);
     
     if (-1 == SLsmg_init_smg ()) {
       SLsig_unblock_signals ();
       return -1;
     }
   }
	
   SLsig_unblock_signals ();

   return 0;
}

/** Initialize the SLang colors
  *
  * - Color 0 is White on Blue  : the desktop 
  * - Color 1 is Blue on White  : it is used for the message box
  * - Color 2 is Black on Cyan  : it is the menu color
  * - Color 3 is Red on Cyan    : it is the menu highlight color
  * - Color 4 is White on Black : it is a selected menu
  * - Color 5 is Cyan on Black  : it is a selected menu highlight
  * - Color 6 is Green on blue  : it is a selected window
  * - Color 7 is Blue on gray   : it is use for the text widgets
  * - Color 8 is white on lightgray : it is used as dialog border 1
  * - Color 9 is black on lightgray : it is used as dialog border 2 and title
  * - Color 10 is white on cyan : it is used in the listview headers
  */
void RainbruRPG::Terminal::TerminalApp::initColors(){
  SLtt_set_color (0, NULL,  "white", "blue" );
  SLtt_set_color (1, NULL,  "blue",  "lightgray" );
  SLtt_set_color (2, NULL,  "black", "cyan" );
  SLtt_set_color (3, NULL,  "red",   "cyan" );
  SLtt_set_color (4, NULL,  "white", "black" );
  SLtt_set_color (5, NULL,  "cyan",  "black" );
  SLtt_set_color (6, NULL,  "green", "blue" );
  SLtt_set_color (7, NULL,  "blue",  "lightgray" );
  SLtt_set_color (8, NULL,  "white", "lightgray" );
  SLtt_set_color (9, NULL,  "black", "lightgray" );
  SLtt_set_color (10, NULL,  "white", "cyan" );
}

/** Refresh the message box according to the char* message string
  *
  */
void RainbruRPG::Terminal::TerminalApp::drawMessageBox(){
  int row = SLtt_Screen_Rows - 1;

  SLsmg_gotorc (row, 0);
  SLsmg_set_color (1);
  SLsmg_write_string ( this->message );
  SLsmg_erase_eol ();
  SLsmg_set_color (0);

  drawKeycodeBox();
}

/** Get a caractère from the SLang terminal
  *
  * \return the keycode from the SLkp_getkey() function.
  */
int RainbruRPG::Terminal::TerminalApp::getch(){
   int ch;
   
   while (0 == SLang_input_pending (1000))
     continue;
   
   //   ch = SLang_getkey ();
   ch =  SLkp_getkey();
   if (ch == 033){		       /* escape */
     if (0 == SLang_input_pending (this->timeout))
       return 033;
   }
   SLang_ungetkey (ch);
  
   if (ch==195){
     altKeycode=true;
     currentMenu=0;
     message="ALT key pressed";
     drawMessageBox();
   }

   return SLkp_getkey();
}

/** Called to run the server
  *
  */
void RainbruRPG::Terminal::TerminalApp::run(){
  tShortCut* menuSC;
  createMenuBarShortcut();
  keyHit();
}

/** Set the menubar pointer to m
  *
  * \param m the menubar
  */
void RainbruRPG::Terminal::TerminalApp::setMenubar( 
                RainbruRPG::Terminal::MenuBar* m ){
  this->menubar=m;
}

/** Get the pointer to the menubar 
  *
  * \return the menubar
  */
RainbruRPG::Terminal::MenuBar* RainbruRPG::Terminal::TerminalApp::getMenubar(){
  return this->menubar;
}

/** Draw the keycode box
  *
  * The keycode box is a little space at the roght of the messagebox,
  * providing the last pressed keycode to be printed.
  */
void RainbruRPG::Terminal::TerminalApp::drawKeycodeBox(){
  int row = SLtt_Screen_Rows - 1;
  int col=SLtt_Screen_Cols - keycodeboxWidth;

  SLsmg_gotorc (row, col-1);
  SLsmg_set_color (1);
  SLsmg_draw_vline (1);
  SLsmg_gotorc (row, col);

  if (lastKeycode!=-1 && lastKeycode!=195){
    if (altKeycode){
      SLsmg_printf( "A+%d", lastKeycode );
      altKeycode=false;
    }
    else
      SLsmg_printf( "  %d", lastKeycode );
  }

  SLsmg_erase_eol();
  SLsmg_set_color(0);
}



/** Highlight temporaly the text for menus if b is true
  *
  * The menu is highlight with the color 3. A normal menu is drawn
  * with the color 2.
  *
  * \param b if true, set the menu highlight color, otherwise, set the
  *          normal menu index.
  */
void RainbruRPG::Terminal::TerminalApp::high(bool b){
  if (b)
    SLsmg_set_color(3);
  else
    SLsmg_set_color(2);
}

/** Writes the menu caption, including the shortcut at the x, y
  * position
  *
  * \param x The x coordonate of the first character
  * \param y The y coordonate of the first character
  * \param c The caption of the menu to be drawn
  */
void RainbruRPG::Terminal::TerminalApp::drawMenuCaption(int x, int y, 
							string c){
  int i;
  bool sc=false; //is the next char the shortcut

  for (i=0; i<c.size(); i++){
    if (c[i]=='&'){
      sc=true;
    }
    else{
      if (sc){

	high( true );

	SLsmg_gotorc (y,x);
	SLsmg_printf( "%c", c[i] );
       
	x++;
	high( false );

	sc=false;
      }
      else{
	SLsmg_set_color (2);
	SLsmg_gotorc (y,x);
	SLsmg_printf( "%c", c[i] );
	
	x++;
	SLsmg_set_color (0);
      }
    }
  }
}

/** Draw an empty menu bar 
  *
  * it draws a cyan-colored background in the first
  * line.
  *
  */
void RainbruRPG::Terminal::TerminalApp::drawEmptyMenuBar(){
  SLsmg_gotorc(0, 0);
  SLsmg_set_color(2);
  SLsmg_erase_eol();
  SLsmg_set_color(0);
}

/** Writes the menu caption, including the shrotcut at the x, y
  * position
  *
  * \param x The x coordonate of the first character
  * \param y The y coordonate of the first character
  * \param c The caption of the menu to be drawn
  */
void RainbruRPG::Terminal::TerminalApp::drawSelectedMenuCaption(int x, int y, 
								string c){
  int i;
  bool sc=false; //is the next char the shortcut

  for (i=0; i<c.size(); i++){
    if (c[i]=='&'){
      sc=true;
    }
    else{
      if (sc){

	SLsmg_set_color (5);

	SLsmg_gotorc (y,x);
	SLsmg_printf( "%c", c[i] );
       
	x++;
	SLsmg_set_color (4);

	sc=false;
      }
      else{
	SLsmg_set_color (4);
	SLsmg_gotorc (y,x);
	SLsmg_printf( "%c", c[i] );
	
	x++;
	SLsmg_set_color (0);
      }
    }
  }
}


/** Add the menubar shortcuts to the currentShortcut 
  *
  */
void RainbruRPG::Terminal::TerminalApp::createMenuBarShortcut(){

  tMenuList::const_iterator iter;
  string s, te;
  int i,y=5, w=12, xpos=0;
  bool sc=false;

  tMenuList* ml=this->menubar->getMenuList();

  // Iterate through list
  for (iter=ml->begin(); iter != ml->end(); iter++)  {
    
    s=(*iter)->getName();

    // Get the '&' char
    for (i=0; i<s.size(); i++){
      if (s[i]=='&'){
	sc=true;
      }
      else{
	if (sc){
	  // Add the shortcut :
	  tShortCut* t;
	  t=new tShortCut;
	  // Avoir la minuscule
	  te=s;

	  // A boost algorithm
	  to_lower(te);

	  t->sc=te[i];

	  /// Get the xpos of the menu
	  t->xPos=xpos;
	  xpos+=te.size();
	  xpos++;
	
	  t->menu=(*iter);

	  currentShortcut.push_back(t);
	  sc=false;
	}
      }
    }
  }
}

/** Get the pointer to he tShortCut designed by the index o
  *
  */
RainbruRPG::Terminal::tShortCut* 
RainbruRPG::Terminal::TerminalApp::getShortcutFromIndex(int o){

  tShortcutList::const_iterator iter;
  tShortCut* ret=0;
  int i=0;

  for (iter=currentShortcut.begin(); iter != currentShortcut.end(); iter++){
    if (i==o)
      ret=(*iter);

    i++;
  }
  return ret;
}

/** Draw the menuBar 
  *
  */
void RainbruRPG::Terminal::TerminalApp::drawMenuBar(){
  tMenuList::const_iterator iter;
  string s;
  int x=0;
  // If menu==currentMenu, menu is selected
  int menu=0;
  int col=SLtt_Screen_Cols;

  SLsmg_set_color (2);
  SLsmg_gotorc (x, col);

  tMenuList* ml=this->menubar->getMenuList();

  // Iterate through list and output each element.
  for (iter=ml->begin(); iter != ml->end(); iter++)  {
    
    s=(*iter)->getName();

    if (inMenu & menu==currentMenu & !inSubMenu)
      drawSelectedMenuCaption(x, 0, s);
    else
      drawMenuCaption(x, 0, s);

    x+=s.size();
    x++;
    menu++;
  }
  SLsmg_refresh();
 
}

/** Draw the creen 
  *
  */
void RainbruRPG::Terminal::TerminalApp::draw(){
  eraseScreen();
  drawMessageBox();
  drawEmptyMenuBar();

  drawWindows();


  if (menubar) // Segfault if not
    drawMenuBar();


  if (inSubMenu)
    drawMenu(getShortcutFromIndex(currentMenu));


  if (showingDialog)
    dialog->draw();
}

/** Print a message in the message box
  *
  */
void RainbruRPG::Terminal::TerminalApp::showMessage(char* m){
  message=m;
  draw();
}
 
/** Erase the entire screen but the menubar in blue
  *
  */
void RainbruRPG::Terminal::TerminalApp::eraseScreen(){
  SLsmg_set_color(0);
  SLsmg_gotorc (1,0);
  SLsmg_erase_eos();
}

/** Draw a menu item 
  *
  * Draw the string at the given position. If hl is true, the
  * Item is currently selected.
  *
  * \param x the x coordonate of the menu item
  * \param y the y coordonate of the menu item
  * \param c the caption of the menu item
  * \param hl is the menu item selected
  */
void RainbruRPG::Terminal::TerminalApp::drawItemCaption(int x, int y, 
							string c ,
							bool hl){

  int i, co, co2;
  bool sc=false; //is the next char the shortcut

  // Set the drawing color
  if (hl){
    co=4;
    co2=5;

    // Draw the black bar
    tShortCut* menuSC;
    menuSC= getShortcutFromIndex(currentMenu);

    SLsmg_set_color_in_region (5, y, x, 1, menuSC->menu->getWidth());
  }
  else{
    co=2;
    co2=3;
  }

  for (i=0; i<c.size(); i++){
    if (c[i]=='&'){
      sc=true;
    }
    else{
      if (sc){
	SLsmg_set_color(co2);
	SLsmg_gotorc (y,x);
	SLsmg_printf( "%c", c[i] );
	SLsmg_set_color(0);
	x++;
	high( false );

	sc=false;
      }
      else{

	SLsmg_set_color (co);

	SLsmg_gotorc (y,x);
	SLsmg_printf( "%c", c[i] );

	x++;
	SLsmg_set_color (0);
      }
    }
  }
}

/** Draw a menu box with items according to its tShortCut
  *
  * Call drawMenuBackground. 
  *
  * If the menu is taller than the screen, it provides a scrolling function
  */
void RainbruRPG::Terminal::TerminalApp::drawMenu( tShortCut* s ){
  tMenuItemList::const_iterator iter;
  string s2;
  int x=2, y=2;
  // Set to true if the the next item has to de highlighted
  // Then passed to drawItemCaption
  bool hl=false; 

  // Is the menu is bigger than the screen
  bool bigOne=false;

  // If the menu is taller
  if (s->menu->getHeight()+3>SLtt_Screen_Rows)
    bigOne=true;
  

  // Draws the background of the menu
  SLsmg_set_color_in_region (2, 1, s->xPos, s->menu->getHeight()+2,  
		   s->menu->getWidth()+4);

  SLsmg_set_color (2);

  // Draw the box
  SLsmg_draw_box ( 1, s->xPos, s->menu->getHeight()+2,  
		   s->menu->getWidth()+4);
  SLsmg_refresh ();
  
  // SLsmg_gotorc (x, col);

  // Draw menu items
  tMenuItemList* ml=s->menu->getItemList();

  // Iterate through list and output each element.
  for (iter=ml->begin(); iter != ml->end(); iter++)  {
    
    s2=(*iter)->getName();

    if (currentSubMenu==y-2)
      hl=true;
    else
      hl=false;
    if (bigOne & (y>SLtt_Screen_Rows-1)){
      drawBiggerMenuIndicatorBotton( s->xPos+1 );
    }
    else{
      drawItemCaption( s->xPos+2, y, s2, hl );
      y++;
    }
  }
}

/** Draw the indicator that the menu is taller that the screen 
  *
  */
void RainbruRPG::Terminal::TerminalApp::drawBiggerMenuIndicatorBotton(int x){
  int y=SLtt_Screen_Rows-1;

  SLsmg_gotorc (y,x);
  SLsmg_write_char( SLSMG_DARROW_CHAR );
}

/** Action the current selected menu item
  * 
  */
void RainbruRPG::Terminal::TerminalApp::actionMenu(){
  tShortCut* s=getShortcutFromIndex( currentMenu );

  // Get the right menuItem instance
  tMenuItemList::const_iterator iter;

  int y=0, ret=0;

  // Set to true if the the next item has to de highlighted
  // Then passed to drawItemCaption
  bool hl=false; 

  // Is the menu is bigger than the screen
  bool bigOne=false;

  // If the menu is taller
  if (s->menu->getHeight()+3>SLtt_Screen_Rows){
    bigOne=true;
  }

  // Draws the background of the menu
  SLsmg_set_color_in_region (2, 1, s->xPos, s->menu->getHeight()+2,  
		   s->menu->getWidth()+4);

  SLsmg_set_color (2);

  // Draw the box
  SLsmg_draw_box ( 1, s->xPos, s->menu->getHeight()+2,  
		   s->menu->getWidth()+4);
  SLsmg_refresh ();
  
  // SLsmg_gotorc (x, col);

  // Draw menu items
  tMenuItemList* ml=s->menu->getItemList();

  // Iterate through list and fire the action
  for (iter=ml->begin(); iter != ml->end(); iter++)  {
    
    if (y==currentSubMenu){
      ret=(*iter)->fireAction();
      if (ret==-1)
	showMessage("No action has been set to this menu item!!!");
    }
    y++;
  }
}

/** Add a Window to the windows internal STL list
  *
  */
void RainbruRPG::Terminal::TerminalApp::addWindow(Window* w){
  windowList.push_back( w );
  w->setSelected( true );
}

/** Call the draw method to all the windows
  *
  */
void RainbruRPG::Terminal::TerminalApp::drawWindows(){
  tWindowList::const_iterator iter;

  // Iterate through list and fire the action
  for (iter=windowList.begin(); iter != windowList.end(); iter++)  {
    (*iter)->draw();
  }
}

/** Add a Window to the windows internal STL list
  *
  * If b is true, the window is used as fullscreen
  */
void RainbruRPG::Terminal::TerminalApp::addWindow(Window* w, bool b){
  this->addWindow( w );
  if (b)
    w->setState( MAXIMIZED );
}

/** Treats the keyboard entry
  *
  * If the TAB key is hitten, it calls keyTabHit(), otherwise, it
  * calls keyArrowInMenu( int ).
  */
void RainbruRPG::Terminal::TerminalApp::keyHit(){
  int ch;

  while ('q' != (ch = getch ()))     {
    lastKeycode=ch;
    drawKeycodeBox();

    if (showingDialog){
      dialog->receiveKeyEvent( ch );
    }
    else{
      if (ch==9) //TAB
	keyTabHit();
      
      
      if (ch==10){ //F10
	inMenu=!inMenu;
	drawMenuBar();
      }
      
      if (inMenu)
	keyArrowInMenu(ch);
      else
	sendKeyToCurrentWindow(ch);

    }
    draw();
    SLsmg_refresh();
  }
}

/** Treats the arrow keys if inMenu is \c true
  *
  */
void RainbruRPG::Terminal::TerminalApp::keyArrowInMenu(int ch){
  tShortCut* menuSC;

  if (ch==4){ // droite
    currentMenu++;
    currentSubMenu=0;

    if ( currentMenu>menubar->getSize()-1)
      currentMenu=0;
  }
  if (ch==3){ // gauche
    currentMenu--;
    currentSubMenu=0;
    if (currentMenu<0)
      currentMenu=menubar->getSize()-1;
  }
  if (ch==2){ // bas
    menuSC= getShortcutFromIndex(currentMenu);
    // If we are not in the menu...
    if (!inSubMenu){
      inSubMenu=true;
      currentSubMenu=0;
    }
    // We are in the menu...
    else{
      currentSubMenu++;
      if (currentSubMenu > menuSC->menu->getHeight()-1)
	currentSubMenu=0;
    }
  }
  
  if (ch==1){ // haut
    menuSC= getShortcutFromIndex(currentMenu);
    // If we are not in the menu...
    if (!inSubMenu){
      inSubMenu=true;
      currentSubMenu=menuSC->menu->getHeight()-1;
    }
    // We are in the menu...
    else{
      currentSubMenu--;
      if (currentSubMenu < 0)
	currentSubMenu= menuSC->menu->getHeight()-1;
    }
  }
  if (ch==13){ // enter
    if (inSubMenu){
      inMenu=false;
      inSubMenu=false;
      actionMenu();
    }
  }
  //  draw();
}

/** Send the keycodes received to the current Window
  * 
  * Iterates through windowList and if a Window::isSelected() returns
  * \c true, send it the keycode.
  *
  * \param ch the keycode to send to teh selected Window
  */
void RainbruRPG::Terminal::TerminalApp::sendKeyToCurrentWindow( int ch ){

  tWindowList::const_iterator iter;

  if (!inMenu && !inSubMenu){
    // Iterate through list and if it is selected, call the 
    for (iter=windowList.begin(); iter != windowList.end(); iter++)  {
      if( (*iter)->isSelected() ){
	(*iter)->getLayout()->getFocusedWidget()->receiveKeyEvent(ch);
      }
    }
  }
}

/** The TAB key event holder
  *
  * It call the current Window's Layout::getNextFocus() method.
  */
void RainbruRPG::Terminal::TerminalApp::keyTabHit(){
  tWindowList::const_iterator iter;

  if (!inMenu && !inSubMenu){

    // Iterate through list and if it is selected, call the 
    //  Layout::getNextFocus() method.
    for (iter=windowList.begin(); iter != windowList.end(); iter++)  {
      if( (*iter)->isSelected() ){
	(*iter)->getLayout()->getNextFocus();
      }
    }
  }
}

/** Set the current Dialog to \c d and shows it
  *
  * \param d The Dialog to show
  */
void RainbruRPG::Terminal::TerminalApp::showDialog(Dialog* d){
  this->dialog=d;
  showingDialog=true;
}

/** Close the current dialog
  *
  * The showingDialog value is set to \c false. The dialog is destructed
  * and its pointer is set to \c NULL.
  *
  */
void RainbruRPG::Terminal::TerminalApp::closeDialog(){
  delete this->dialog;
  this->dialog=NULL;

  showingDialog=false;
}

/** Returns the number of window
  *
  * It simply returns the size of the windowList.
  *
  * \return The number of windows
  *
  */
unsigned int RainbruRPG::Terminal::TerminalApp::windowCount(){
  return windowList.size();
}

/** Gets the current Dialog
  *
  * \return The current Dialog
  *
  */
RainbruRPG::Terminal::Dialog* 
RainbruRPG::Terminal::TerminalApp::getCurrentDialog(){

  return this->dialog;
}
