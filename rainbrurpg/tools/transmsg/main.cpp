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

/** \file tools/transmsg/main.cpp
  * Implements the main entry of the TransMsg tool
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  *
  */

#include <iostream>
#include <fstream>

#include "transfile.h"

using namespace std;
using namespace RainbruRPG::Trans;

// Forward declaration
void showHelp(int);
// End of forward declaration

/** The main entry of the TransMsg tool
  *
  * \param argc The number of command-line arguments
  * \param argv The array of command-line arguments
  *
  */
int main(int argc, char** argv){

  showHelp(argc);

  TransFile tf("essai.txt");

  return 1;
}

/** Show a help message if needed
  *
  * \param argc The number of command-line arguments received by the 
  *        \ref main function
  * 
  */
void showHelp(int argc){
  if (argc != 2){
    cout << "transmsg argument error :" << endl;
    cout << "try transmsg <directory name>" << endl;

  }
}
