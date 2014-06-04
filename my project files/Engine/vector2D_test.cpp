#include <gtest\gtest.h>

// this is my own vector definition
// Note: I had to edit the EngineTester project properties and add 
// "$(ProjectDir)\..\Engine" to my "Additional Include" directories.
#include <vector2D.h>
using MATH::vector2D;

TEST(Vector2D, Constructor)
{
   vector2D first(1, 2);
   EXPECT_EQ(1, first.x);
   EXPECT_EQ(2, first.y);
}

TEST(Vector2D, Vector_Addition)
{
   vector2D first(1, 2);
}

TEST(Vector2D, Scalar_Multiplication)
{

}