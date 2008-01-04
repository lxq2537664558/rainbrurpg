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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** Modifications :
  * - 26 jul 2007 : Including formulas in documentation
  *
  */

#ifndef VELOCITY_CALCULATOR_CONSTANT_H
#define VELOCITY_CALCULATOR_CONSTANT_H

#include "velocitycalculator.h"

using namespace std;

namespace RainbruRPG{
  namespace Core{

    /** A very simple constant velocity calculator
      *
      * It uses translationLenght and transitionTime to give 
      * the velocity value for each frame. It attemps to give
      * a constant velocity according to the time of the last
      * given lenght. According to the time elapsed between two
      * calls, getNextFrame(bool&) give a lenght.
      *
      * A Ogre timer object (defined in VelocityCalculator) is used for
      * time calculation.
      *
      * \sa VelocityCalculator
      *
      */
    class vcConstant : public VelocityCalculator{
    public:
      vcConstant();

      virtual float getNextFrame(bool&);

    private:
      float getLenghtByTime(double);
    };

  }
}

#endif // VELOCITY_CALCULATOR_CONSTANT_H
