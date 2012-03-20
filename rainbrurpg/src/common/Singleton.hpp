/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file Singleton.hpp
  * Implementation of the Meyer's Singleton design pattern
  *
  * Modifications :
  * - 08 aug 2008 : Single file documentation
  *
  */
#ifndef SINGLETON_H
#define SINGLETON_H

namespace RainbruRPG{
  namespace Core{

    /** Implementation of the Meyer's Singleton design pattern
      *
      * To have a singleton subclass named \c Ex you must:
      * - subclass this : <code>class Ex : public Singleton<Ex></code>
      * - make copy and assignment constructor forbidden :
      *   <pre>
      *   private:
      *     Ex(const Ex& obj);
      *     Ex& operator=(const Ex& obj);
      *   </pre>
      * - create a public default constructor (empty or implemented):
      *   <pre>
      *   public:
      *     Ex(){};
      *   </pre>
      *
      * \warning This Singleton implementation is not
      * thread-safe. <b> Do not use it in a multi-thread context</b>.
      *
      * \todo Make sure the Singleton implementation become thread-safe
      */
    template<typename T> class Singleton{
    public:
      /** Get the Singleton unique instance
        *
        * \return The unique instance of the singleton
	* \warning This Singleton implementation is not
	* thread-safe. <b> Do not use it in a multi-thread context</b>.
	*/
      static T& getSingleton(){
	static T theSingleInstance;
	return theSingleInstance;
      }
    };
  }
}

#endif // SINGLETON_H
