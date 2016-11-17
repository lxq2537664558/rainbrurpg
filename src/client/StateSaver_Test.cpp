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

#include <gtest/gtest.h>
#include <CEGUI/Rect.h> // Uses typedef URect and UDim

TEST( StateSaver, set_get )
{
  StateSaver sv;
  sv.set<int>("an_int", 12);
  EXPECT_EQ( sv.get<int>("an_int"), 12);
}

TEST( StateSaver, exists_false )
{
  StateSaver sv;
  EXPECT_EQ( sv.exists("aze"), false);
}

TEST( StateSaver, exists_true )
{
  StateSaver sv;
  sv.set<int>("an_int", 12);
  EXPECT_EQ( sv.exists("an_int"), true);
}

TEST( StateSaver, already_exists )
{
  StateSaver sv;
  sv.set<int>("an_int", 12);
  ASSERT_THROW(sv.set<int>("an_int", 64) , std::exception);
}

TEST( StateSaver, cant_be_found )
{
  StateSaver sv;
  ASSERT_THROW( sv.get<int>("an_int"), RainbrurpgException);
}

TEST( StateSaver, cast_error )
{
  StateSaver sv;
  sv.set<int>("an_int", 12);
  ASSERT_THROW(sv.get<string>("an_int") , boost::bad_get);
}

TEST( StateSaver, udim_ne )
{
  // More a test the UDim equality
  UDim b, d = UDim(1.2, 8.3);
  EXPECT_NE(b, d); 
}

TEST( StateSaver, udim_eq )
{
  StateSaver sv;
  UDim b, d = UDim(1.2, 8.3);
  sv.save("udim", &d);
  sv.restore("udim", &b);
  EXPECT_EQ(b, d);
}
