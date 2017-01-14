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

#include "GameState.hpp"
#include "StateManager.hpp"

#include <gtest/gtest.h>

#include "EmptyGameState.hpp"


// Test if current is NULL
TEST( StateManager, constructor_state_is_null )
{
  StateManager sm(NULL);   // a NULL GameEngine*
  ASSERT_TRUE(sm.getCurrentState() == NULL);
}

// Chang current state and test if it actually changed it
TEST( StateManager, set_current_state )
{
  EmptyGameState gs("myname");
  StateManager sm(NULL);   // a NULL GameEngine*
  sm.setCurrentState(&gs);
  
  EXPECT_EQ( sm.getCurrentState(), &gs);
}
