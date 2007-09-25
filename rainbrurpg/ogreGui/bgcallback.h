/* 
 * Betajaen's GUI 015
 * Written by Robin "Betajaen" Southern 07-Nov-2006, 
 * http://www.ogre3d.org/wiki/index.php/BetaGUI
 * This code is under the Whatevar! licence. Do what you want; 
 * but keep the original copyright header.
 *
 */

/* Modifications :
 * - 24 sep 2007 : This was the original BetaGUI code. 
 *                 Betajaen's headers added
 *
 */

#ifndef _BETAGUI_CALLBACK_H_
#define _BETAGUI_CALLBACK_H_


namespace BetaGUI {

  // forward declaration
  class BetaGUIListener;
  class Button;
  // end of forward declaration

  class Callback{
  public:
    Callback(){
      type=0;
    }
    
    Callback(void(*functionPointer)(Button *ref)){
      type=1;
      fp=functionPointer;
    }
    
    Callback(BetaGUIListener *L){
      type=2;
      LS=L;
    }
    
    void setType(unsigned char t){ this->type=t; };
    unsigned char getType(void){ return this->type; };

    void(*fp)(Button *r);
    BetaGUIListener *LS;

  protected:
    unsigned char type;
  };

}



#endif // _BETAGUI_CALLBACK_H_
