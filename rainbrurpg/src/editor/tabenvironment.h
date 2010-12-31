/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file tabenvironment.h
  * Declares the environment parameters tab
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 04 jan 2008 : GNU header added
  *
  */

#ifndef TAB_ENVIRONMENT_H
#define TAB_ENVIRONMENT_H

#include <QWidget>
#include <QToolBox>

namespace RainbruRPG{
  namespace Editor{
    /** The tab parameters environment
      *
      * This Qt widget is used in the editor. It provides an environment
      * customization.
      *
      */
    class TabEnvironment : public QWidget{
      Q_OBJECT
	
	public:
      TabEnvironment(QWidget *parent = 0);
      ~TabEnvironment();

    private:
      /** A toolbox used to separate different parameter */
      QToolBox* toolBox;
      
    };
    
  }
}

#endif // TAB_ENVIRONMENT_H
