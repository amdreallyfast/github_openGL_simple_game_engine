#include <gtest\gtest.h>

// this is my own vector definition
// Note: I had to edit the EngineTester project properties and add 
// "$(ProjectDir)\..\Engine" to my "Additional Include" directories.
#include <math/vector2D.h>
using Math::vector2D;

#include <math.h>

#ifdef RUN_VECTOR2D_TESTS

TEST(Vector2D, Constructor)
{
   vector2D first(1, 2);
   
   EXPECT_FLOAT_EQ(1, first.x);
   EXPECT_FLOAT_EQ(2, first.y);
}

TEST(Vector2D, Copy_Constructor)
{
   vector2D source(1, 1234.5678f);
   vector2D the_copy(source);

   EXPECT_FLOAT_EQ(the_copy.x, 1);
   EXPECT_FLOAT_EQ(the_copy.y, 1234.5678f);
}

TEST(Vector2D, Length)
{
   vector2D v(3, 4);
   float length = v.length();

   EXPECT_FLOAT_EQ(length, 5);
}

TEST(Vector2D, Assignment)
{
   vector2D first(1, 2);
   vector2D result(3, 4);
   result = first;

   EXPECT_FLOAT_EQ(result.x, 1);
   EXPECT_FLOAT_EQ(result.y, 2);
}

TEST(Vector2D, Vector_Addition)
{
   vector2D first(1, 2);
   vector2D second(3, 4);
   vector2D result1 = first + second;
   vector2D result2 = second + first;

   EXPECT_FLOAT_EQ(result1.x, 4);
   EXPECT_FLOAT_EQ(result1.y, 6);
   EXPECT_FLOAT_EQ(result2.x, result1.x);
   EXPECT_FLOAT_EQ(result2.y, result1.y);
}

TEST(Vector2D, Vector_Addition_Assignment)
{
   vector2D first(5, 1234.5678f);
   vector2D second(1, 1);
   second += first;
   
   EXPECT_FLOAT_EQ(second.x, 6);
   EXPECT_FLOAT_EQ(second.y, 1235.5678f);
}

TEST(Vector2D, Vector_Subtraction)
{
   vector2D first(1, 2);
   vector2D second(3, 4);
   vector2D result1 = first - second;
   vector2D result2 = second - first;

   EXPECT_FLOAT_EQ(result1.x, -2);
   EXPECT_FLOAT_EQ(result1.y, -2);
   EXPECT_FLOAT_EQ(result2.x, 2);
   EXPECT_FLOAT_EQ(result2.y, 2);
}

TEST(Vector2D, Vector_Subtraction_Assignment)
{
   vector2D first(5, 1234.5678f);
   vector2D second(1, 1);
   second -= first;

   EXPECT_FLOAT_EQ(second.x, -4);
   EXPECT_FLOAT_EQ(second.y, -1233.5678f);
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

#endif
