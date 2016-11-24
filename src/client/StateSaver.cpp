/*
 * Copyright 2011-2016 Jerome Pasquier
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

#include "StateSaver.hpp"

#include <sstream>

#include <CEGUI/Window.h>  // Uses CEGUI::Window

#include "CeguiDialog.hpp"


/** The default constructor */
StateSaver::StateSaver()
{

}

/** Tests if the given key exists in this map
  *
  * \return true if the key doesn't exist, false otherwise.
  *
  */
bool
StateSaver::exists(const string& key)const
{
  if (mStates.find(key) == mStates.end())
    return false;

  return true;
}

/** Create a key:subkey concatenation
  *
  */
string
StateSaver::subkey(const string& key, const string& subkey)const
{
  ostringstream oss;
  oss << key << ':' << subkey;
  return oss.str();
}

void
StateSaver::save(const string& key, UDim* d)
{
  set<float>(subkey(key, "scale"), d->d_scale);
  set<float>(subkey(key, "offset"), d->d_offset);
}

void
StateSaver::restore(const string& key, UDim* d)
{
  d->d_scale = get<float>(subkey(key, "scale") );
  d->d_offset = get<float>(subkey(key, "offset") );
}


/** Save the position and dimensions of a CEGUI::URect
  *
  */
void
StateSaver::save(const string& key, URect* r)
{
  // Avoid invalid conversion from const to non const
  UDim x = r->getPosition().d_x, y = r->getPosition().d_y;
  save(subkey(key, "x"), &x);
  save(subkey(key, "y"), &y);
  // Avoid taking adress of temporary
  UDim w = r->getWidth(), h = r->getHeight();
  save(subkey(key, "width"), &w);
  save(subkey(key, "height"), &h);
}

void
StateSaver::restore(const string& key, URect* r)
{
  UDim x, y, w, h;
  restore(subkey(key, "x"), &x); 
  restore(subkey(key, "y"), &y);
  r->setPosition(UVector2(x, y));
  restore(subkey(key, "width"), &w);
  restore(subkey(key, "height"), &h);
  r->setWidth(w);
  r->setHeight(h);
}


void
StateSaver::save(const string& key, Window* w)
{
  // Save scalars
 set<bool>(subkey(key, "visible"), w->isVisible());

  // Save complex types
  URect area =w->getArea();
  save(subkey(key, "area"), &area);
}

void
StateSaver::restore(const string& key, Window* w)
{
  // Restore scalars
  w->setVisible(get<bool>(subkey(key, "visible")));

  // Restore Complex types
  URect area;
  restore(subkey(key, "area"), &area);
  w->setArea(area);
}

void
StateSaver::save(const string& key, CeguiDialog* d)
{
  // Save scalars
 set<bool>(subkey(key, "visible"), d->isVisible());

  // Save complex types
  URect area =d->getDialog()->getArea();
  save(subkey(key, "area"), &area);
}

void
StateSaver::restore(const string& key, CeguiDialog* d)
{
  // Restore scalars
  d->setVisible(get<bool>(subkey(key, "visible")));

  // Restore Complex types
  URect area;
  restore(subkey(key, "area"), &area);
  d->getDialog()->setArea(area);
}
