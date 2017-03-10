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

#include "LoadingBar.hpp"

#include <gtest/gtest.h>

TEST( LoadingBar, vectorSize )
{
  // Normal resolution without any extra whitespace
  LoadingBar lb("Testing loadingbar");
  lb.addStep("Step 1");
  lb.addStep("Step 2");
  ASSERT_EQ( lb.getStepNumber(), 2 ); 
}


TEST( LoadingBar, stepSize )
{
  // Normal resolution without any extra whitespace
  LoadingBar lb("Testing loadingbar");
  lb.addStep("Step 1");
  lb.addStep("Step 2");
  ASSERT_EQ( lb.getStepSize(), 0.5f ); 
}
