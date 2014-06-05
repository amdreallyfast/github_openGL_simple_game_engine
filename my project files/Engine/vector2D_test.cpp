#include <gtest\gtest.h>

// this is my own vector definition
// Note: I had to edit the EngineTester project properties and add 
// "$(ProjectDir)\..\Engine" to my "Additional Include" directories.
#include <vector2D.h>
using MATH::vector2D;

TEST(Vector2D, Constructor)
{
   vector2D first(1, 2);
   EXPECT_FLOAT_EQ(1, first.x);
   EXPECT_FLOAT_EQ(2, first.y);
}

TEST(Vector2D, Vector_Addition)
{
   vector2D first(1, 2);
   vector2D second(3, 4);
   vector2D result1 = first + second;
   vector2D result2 = second + first;

   EXPECT_FLOAT_EQ(4, result1.x);
   EXPECT_FLOAT_EQ(6, result1.y);
   EXPECT_FLOAT_EQ(result2.x, result1.x);
   EXPECT_FLOAT_EQ(result2.y, result1.y);
}

TEST(Vector2D, Scalar_Multiplication)
{
   float scalar = 10.0f;
   vector2D v(1, 2);
   vector2D result1 = scalar * v;
   vector2D result2 = v * scalar;

   EXPECT_FLOAT_EQ(10, result1.x);
   EXPECT_FLOAT_EQ(20, result1.y);
   EXPECT_FLOAT_EQ(result2.x, result1.x);
   EXPECT_FLOAT_EQ(result2.y, result1.y);
}