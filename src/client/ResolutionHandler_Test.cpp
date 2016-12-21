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

#include "ResolutionHandler.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;

class ResolutionHandlerTestClass : public ResolutionHandler
{
public:
  ResolutionHandlerTestClass(){};
  //  virtuel ~ResolutionHandlerTestClass(){};

  bool fromString(const string& str)
  {
    return  this->probeFromString(str);
  }
  bool fromInts(int width, int height)
  {
    return this->probeFromInts(width, height);
  }

  const ResolutionHandlerResult& getResult()
  {
    return *mResult;
  }
};
  
TEST( ResolutionHandler, fromString_Success_1024x768 )
{
  // Normal resolution without any extra whitespace
  ResolutionHandlerTestClass rh;
  bool b = rh.fromString("1024 x 768");
  EXPECT_EQ( rh.getResult().width, 1024 ); 
  EXPECT_EQ( rh.getResult().height,  768 ); 
  ASSERT_TRUE( b ); 
}

TEST( ResolutionHandler, fromString_Success_ExtraSpaces )
{
  // May contain extra spaces
  ResolutionHandlerTestClass rh;
  ASSERT_TRUE( rh.fromString("1024   x 768"));
  EXPECT_EQ( rh.getResult().width, 1024 ); 
  EXPECT_EQ( rh.getResult().height,  768 );
  
  ASSERT_TRUE( rh.fromString("800 x    600")); 
  EXPECT_EQ( rh.getResult().width, 800 ); 
  EXPECT_EQ( rh.getResult().height,  600 );
  
  ASSERT_TRUE( rh.fromString("640   x   480"));
  EXPECT_EQ( rh.getResult().width, 640 ); 
  EXPECT_EQ( rh.getResult().height,  480 ); 
}

TEST( ResolutionHandler, fromString_Success_LeadingSpaces )
{
  // May contain extra spaces
  ResolutionHandlerTestClass rh;
  ASSERT_TRUE( rh.fromString("  1024 x 768"));
  EXPECT_EQ( rh.getResult().width, 1024 ); 
  EXPECT_EQ( rh.getResult().height,  768 );

  ASSERT_TRUE( rh.fromString("24 x 680   "));
  EXPECT_EQ( rh.getResult().width, 24 ); 
  EXPECT_EQ( rh.getResult().height,  680 );
}

TEST( ResolutionHandler, fromStringSuccess_2 )
{
  ResolutionHandlerTestClass rh;
  ASSERT_TRUE( rh.fromString("4 x 8")); // Can't test for res. logic
  EXPECT_EQ( rh.getResult().width, 4 ); 
  EXPECT_EQ( rh.getResult().height, 8 ); 
}

TEST( ResolutionHandler, fromStringFail_NotALetter )
{
  ResolutionHandlerTestClass rh;
  ASSERT_FALSE( rh.fromString("1024 y 768")); // Do not contain 'x'
}

TEST( ResolutionHandler, fromStringFail_OnlyNumbers )
{
  ResolutionHandlerTestClass rh;
  ASSERT_FALSE( rh.fromString("1024 768")); // Do not contain 'x'
}

TEST( ResolutionHandler, fromStringFail_MissingSecondInt )
{
  ResolutionHandlerTestClass rh;
  ASSERT_FALSE( rh.fromString("1024 x")); // Missing second int
}

TEST( ResolutionHandler, fromStringFail_StartWithLetter )
{
  ResolutionHandlerTestClass rh;
  ASSERT_FALSE( rh.fromString("az 24 x")); // Not starting with an int
}
