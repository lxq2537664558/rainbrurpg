/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

#include "LoadBmp.hpp"
#include "GlobalUri.hpp"

#include "BoostImport.hpp"

#include <vector>

namespace fs = boost::filesystem;

/** The default constructor 
  *
  */
RainbruRPG::Core::LoadBMP::LoadBMP(){

  RainbruRPG::Network::GlobalURI gu;
  input = gu.getShareFile("data/main.bmp");

  output="steg.txt";

}

/** The default destructor 
  *
  */
RainbruRPG::Core::LoadBMP::~LoadBMP(){

}

/** Decode the embedded text and set it in the output file.
  *
  * The code will be in a1 when this fucntion return.
  *
  */
void RainbruRPG::Core::LoadBMP::decode(){
  char temp1[100];

  // open the bmp file
  BMP Image;

  int len=input.length()+1;
  std::vector<char> raw(len);
  const char* str = input.c_str();
  std::copy(str, str + len, raw.begin());
  Image.ReadFromFile( &(raw[0]) );
  
  // prep the output stream
  
  std::fstream OutputText( output.c_str() , ios::out );
  int k = 1;
  int MaxCharacters = Image.TellWidth() * Image.TellHeight();
  
  int i=0;
  int j=0;
  
  bool Stop = false;
  int BlankCount = 0;
  
  while( 2*k <= MaxCharacters && !Stop ){
    unsigned int CharacterInt = (unsigned int) (Image(i,j)->Red % 3)*243 
      + (unsigned int) (Image(i,j)->Green % 3)*81
      + (unsigned int) (Image(i,j)->Blue % 3)*27;
   			     
			     
    i++;
    if( i >= Image.TellWidth() ){ 
      i = 0; 
      j++; 
    }		
   
    CharacterInt += (unsigned int) (Image(i,j)->Red % 3)*9
      + (unsigned int) (Image(i,j)->Green % 3)*3
      + (unsigned int) (Image(i,j)->Blue % 3);
			     
    i++;
    if( i >= Image.TellWidth() ){ 
      i = 0; 
      j++; 
    }		 
 			     
    char Character = (char) CharacterInt;  
    
    if( CharacterInt != 0 ){
      OutputText.put( Character );
    }
    else{
      Stop = true; 
    }
     
    k++;  
  }

  OutputText.close(); 


  // Get all the lines
  std::fstream InputText( output.c_str() , ios::in );

  InputText.getline(temp1, 100);

  InputText.close();

  // Set the temp? value in stl string a?
  a1=temp1;

  // remove the temp file
  fs::remove( output );
}

/** Return the phrasepass for getting xml files from admin website
  *
  * \return The user:password string
  *
  */
const char* RainbruRPG::Core::LoadBMP::get1(){
  return a1.c_str();
}

/** Return the current input filename
  *
  * \return the input filename
  *
  */
const std::string& RainbruRPG::Core::LoadBMP::getInputFilename(void)const{
  return input;
}

/** Change the input filename
  *
  * \param vFilename The new file name
  *
  */
void RainbruRPG::Core::LoadBMP::setInputFilename(const std::string& vFilename){
  input= vFilename;  
}
