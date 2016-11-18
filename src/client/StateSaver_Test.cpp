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
#include <CEGUI/Rect.h>   // Uses typedef URect and UDim

/* What can't be tested here :
 * - CEGUI::Window creation result in segfault
 *
 */

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

TEST( StateSaver, urect_ne )
{
  URect a, b = URect(UDim(1.0, 1.2), UDim(1.0, 1.2),
		     UDim(1.0, 1.2), UDim(1.0, 1.2));
  EXPECT_NE(a, b); 
}

TEST( StateSaver, urect_eq )
{
  StateSaver sv;
  URect a, b = URect(UDim(1.0, 1.2), UDim(1.7, 2.2),
		     UDim(3.0, 2.8), UDim(4.0, 5.2));
  sv.save("urect", &b);
  sv.restore("urect", &a);
  EXPECT_EQ(a, b);
}

