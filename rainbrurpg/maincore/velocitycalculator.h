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

#ifndef VELOCITY_CALCULATOR_H
#define VELOCITY_CALCULATOR_H

#include <OGRE/Ogre.h>
//forward declaration
class EventTarget;
class Cursor;
#include <OGRE/OgreKeyEvent.h>
#include <OGRE/OgreInputEvent.h>
#include <OGRE/OgreEventQueue.h>
#include <OGRE/OgreEventListeners.h>
#include <OGRE/OgreEventTarget.h>
#include <OGRE/OgreInput.h>
#include <OGRE/OgrePlatformManager.h>

#include <OGRE/OgreTimer.h>

namespace RainbruRPG{
  namespace Core{

    /** Defines the translation type 
      *
      * If defines how the velocity will change with the timeline.
      *
      */
    enum tVelocityType{
      VT_INCREASE, //!< The velocity increase with time
      VT_DECREASE, //!< The velocity decrease with time
      VT_INC_DEC,  //!< The velocity Increase and then descrease
      VT_DEC_INC   //!< The velocity first decrease then increase
    };

    /** Superlass for computation of moving velocity
      *
      * The velocity you get by a call to getNextFrame() is the value
      * for the move of the rendering frame, not for the overall timeline.
      *
      * This class use a Ogre Timer for its platform independant facility.
      * You can use in its subclasses either getMilliseconds() or
      * getMicroseconds() to get the time elapsed since the call to start().
      *
      * If the transitionTime is passed, mRunning must be set to false;
      */
    class VelocityCalculator{
    public:
      VelocityCalculator();
      virtual ~VelocityCalculator();

      /** Get the next velocity
        *
	* The bool parameter \b must be set to \c false if the 
	* transition ended.
	*/
      virtual float getNextFrame(bool&)=0;
      virtual void start();


      void setTranslationLenght(float);
      void setTransitionTime(unsigned int);
      void reset();

      bool running();
    protected:
      /** The translation lenght */
      float translationLenght;
      /** The transition time */
      unsigned int transitionTime;
      /** The minimal velocity */
      float minVelocity;
      /** The maximal velocity */
      float maxVelocity;
      /** The type of velocity calculator */
      tVelocityType type;
      /** Is this calculator running */
      bool mRunning;

      /** An Ogre timer used to base the transition in the Ogre timeline */
      Ogre::Timer* timer;

      /** The time get from the Ogre timer for the last frame
        *
	* It can be in milliseconds or microseconds according to
	* what you use. Its default value is 0.
	*
	*/
      unsigned long lastFrameTimeLine;

    };

  }
}


#endif // VELOCITY_CALCULATOR_H
