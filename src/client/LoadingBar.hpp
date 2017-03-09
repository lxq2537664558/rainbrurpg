/*
 * Copyright 2011-2017 Jerome Pasquier
 *
 * This file is part of rainbrurpg-client.
 *
 * rainbrurpg-client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rainbrurpg-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rainbrurpg-client.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _LOADING_BAR_HPP_
#define _LOADING_BAR_HPP_

#include <string>
#include <vector>
#include <CEGUI/EventArgs.h>  // Used as a reference

// Forward declarations
namespace CEGUI
{
  class ProgressBar;
}
// End of forward declarations

using namespace std;

/** A simple step-based loading bar
  *
  * Do not override CeguiDialog because of the unused Ok button.
  *
  */
class LoadingBar
{
public:
  LoadingBar(const string&);
  ~LoadingBar();

  void addStep(const string&);
  void adjustProgress();
  
private:
  string title;
  vector<string> stepNames;

  CEGUI::ProgressBar* progressbar;
};

#endif // !_LOADING_BAR_HPP_
