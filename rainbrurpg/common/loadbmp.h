#ifndef LOAD_BMP_H
#define LOAD_BMP_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <string>

#include "EasyBMP.h"

using namespace std;

typedef char BYTE;

namespace RainbruRPG {
  namespace Core{

    /* A stenographic decoder class
     *
     *  LoadBMP *l=new LoadBMP();
     *  l->decode();
     *
     *  cout << l->get1() << endl;
     *  cout << l->get2() << endl;
     *  cout << l->get3() << endl;
     *
     * The input BMP filename is designed by input.
     * Output is the filename of a temp file.
     */

    /** A simple facility class for BMP loading
      *
      *
      */
    class LoadBMP{
    public:
      LoadBMP();
      ~LoadBMP();

      void decode();

      // Return the phrasepass for password hashsum
      const char* get1();
      // Return the FTP userName
      const char* get2();
      // Return the FPT password
      const char* get3();

    private:
      /** An internally used string */
      char* input;
      /** An internally used string */
      char* output;

      /** A dummy string */
      std::string a1;
      /** A dummy string */
      std::string a2;
      /** A dummy string */
      std::string a3;
    };
  }
}

#endif // LOAD_BMP_H
