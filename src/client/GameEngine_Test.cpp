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

//#include "GameEngine.hpp"

#include "gtest/gtest.h"

int add( int i, int j ) { return i+j; }

TEST( GameEngine, my_test )
{
  // We can't directly test GameEngine here (it launches Ogre...)
  //  GameEngine ge; 
  // seven ways to detect and report the same error:
  EXPECT_EQ( add( 2,2 ), 4 );        // #1 continues on error
}
