/*
 *  Copyright 2006 Jerome PASQUIER
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

/* Modifications :
 * - 20 jul 2007 : Starting implementation
 *
 */

#include <iostream>
#include <string>

#include <hashfile.h>
#include <hashpassword.h>

#include <sigc++/sigc++.h>

using namespace std;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;

int oldPercent=-1;

// forward declaration
void showHelp();

void fileProgress(int size, int dled, double percent){
  if ((int)percent!=oldPercent){
    cout << "fileProgress : "<< (int)percent << "% \t("
	 << dled << "/" << size <<" bytes)" <<endl;
    oldPercent=(int)percent;
  }
}

/** The HashSum program main function
  *
  */
int main(int argc, char** argv){

  if (argc!=3){
    showHelp();
  }
  else if(strcmp(argv[1], "-f")!=0 && strcmp(argv[1], "-p")!=0){
    showHelp();
  }
  else if(strcmp(argv[1], "-f")==0){
    std::string s(argv[2]);
    cout << "Computing hashsum for file '" << s << "'"
	 << " using HashFile" <<  endl;
    HashFile hf;
    hf.progress.connect( sigc::ptr_fun(fileProgress) );
    cout << hf.getHashSum(s)<< endl;
  }
  else if(strcmp(argv[1], "-p")==0){
    std::string s(argv[2]);
    cout << "Computing hashsum for string '" << s << "'"
	 << " using HashPassword" <<  endl;
    HashPassword hp;
    cout << hp.encryptString(s.c_str())<< endl;

  }
  return 1;
}

/** Show a help message if needed
  *
  *
  *
  */
void showHelp(){
  cout << "hashsum argument error :" << endl;
  cout << "  transmsg -f <file_name> to get SHA-1 hashsum of a file" << endl
       << "  transmsg -p <password> to get it for a string" << endl;

}
