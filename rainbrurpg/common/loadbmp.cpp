#include "loadbmp.h"

/** The default constructor */
RainbruRPG::Core::LoadBMP::LoadBMP(){
  input= "data/3d/mzearth.bmp";
  output="steg.txt";

}

/** The default destructor */
RainbruRPG::Core::LoadBMP::~LoadBMP(){
  input= 0;
  output=0;

}

/* Decode the unbeded text and set it in the output file.
 *
 */
/** Decode the BMP buffer */
void RainbruRPG::Core::LoadBMP::decode(){
  char temp1[100];
  char temp2[100];
  char temp3[100];

  // open the bmp file
  BMP Image;
  Image.ReadFromFile( input );
  
  // prep the output stream
  
  fstream OutputText( output , ios::out );
  int k = 1;
  int MaxCharacters = Image.TellWidth() * Image.TellHeight();
  
  int i=0;
  int j=0;
  
  bool Stop = false;
  int BlankCount = 0;
  
  while( 2*k <= MaxCharacters && !Stop )
  {
   unsigned int CharacterInt = (unsigned int) (Image(i,j)->Red % 3)*243 
                             + (unsigned int) (Image(i,j)->Green % 3)*81
			     + (unsigned int) (Image(i,j)->Blue % 3)*27;
   			     
			     
   i++;
   if( i >= Image.TellWidth() )
   { i = 0; j++; }		
   
   CharacterInt += (unsigned int) (Image(i,j)->Red % 3)*9
                 + (unsigned int) (Image(i,j)->Green % 3)*3
      	         + (unsigned int) (Image(i,j)->Blue % 3);
			     
   i++;
   if( i >= Image.TellWidth() )
   { i = 0; j++; }		 
 			     
   char Character = (char) CharacterInt;  
   
   if( CharacterInt != 0 )
   {
    OutputText.put( Character );
   }
   else
   {
    Stop = true; 
   }
     
   k++;  
  }

  OutputText.close(); 


  // Get all the lines
  fstream InputText( output , ios::in );

  InputText.getline(temp1, 100);
  InputText.getline(temp2, 100);
  InputText.getline(temp3, 100);

  InputText.close();

  // Set the temp? value in stl string a?
  a1=temp1;
  a2=temp2;
  a3=temp3;

  // remove the temp file
  remove( output );
}

/** Get a dummy test string
  *
  * \return A dummy string
  *
  */
const char* RainbruRPG::Core::LoadBMP::get1(){
  return a1.c_str();
}

/** Get a dummy test string
  *
  * \return A dummy string
  *
  */
const char* RainbruRPG::Core::LoadBMP::get2(){
  return a2.c_str();
}

/** Get a dummy test string
  *
  * \return A dummy string
  *
  */
const char* RainbruRPG::Core::LoadBMP::get3(){
  return a3.c_str();
}
