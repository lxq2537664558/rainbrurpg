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
