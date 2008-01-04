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


#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include <slang.h>
#include <string>

#include "dialog.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** A Dialog provided for information drawing
      *
      * An information dialog typically has a text (wich is word
      * wrapped) and a OK Button. This Dialog is modal, you can't have
      * access to another widget but the OK button of the Dialog.
      *
      */
    class InfoDialog : public Dialog{
    public:
      InfoDialog();
      InfoDialog( string, int, int );

      virtual void draw();

    private:
      /** The word wrapped message of the dialog */
      string text;
    };

  }
}
#endif // INFO_DIALOG_H
