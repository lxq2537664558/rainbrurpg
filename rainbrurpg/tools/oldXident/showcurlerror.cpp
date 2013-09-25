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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "showcurlerror.h"

/** Show a fltk fl_alert if a error occured in the given CurlSubmitForm.
  *
  * \param csf The CurlSubmitForm to test.
  */
void RainbruRPG::Gui::ShowCurlError::showError(CurlSubmitForm* csf){
  const char* msg;

  long serverError=csf->getServerResponse();

  if (serverError!=-1){
    HttpResponse hr;
    msg=hr.getMessage(serverError);
  }
  else{
    msg=csf->getCustomErrorMessage();
  }

  fl_alert(msg);

}
