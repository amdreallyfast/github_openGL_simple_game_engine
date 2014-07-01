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
   // check default values
   vector2D v0;
   EXPECT_FLOAT_EQ(0, v0.x);
   EXPECT_FLOAT_EQ(0, v0.y);
   EXPECT_FLOAT_EQ(0, v0.w);

   // a non-default constructor
   vector2D v1(1, 2, 3);
   EXPECT_FLOAT_EQ(1, v1.x);
   EXPECT_FLOAT_EQ(2, v1.y);
   EXPECT_FLOAT_EQ(3, v1.w);
}


TEST(Vector2D, Length)
{
   // for a 2D vector, the only things that are important to vector length
   // are the X and Y values, and anything else should be ignored
   vector2D v(3, 4);
   float length = v.length();

   EXPECT_FLOAT_EQ(5, length);
}


TEST(Vector2D, Vector_Addition)
{
   vector2D v1(1, 2, 0);
   vector2D v2(3, 4, 1);

   vector2D result;

   result = v1 + v2;
   EXPECT_FLOAT_EQ(4, result.x);
   EXPECT_FLOAT_EQ(6, result.y);
   EXPECT_FLOAT_EQ(1, result.w);

   result = v2 + v1 + v2 + v1;
   EXPECT_FLOAT_EQ(8, result.x);
   EXPECT_FLOAT_EQ(12, result.y);
   EXPECT_FLOAT_EQ(2, result.w);
}


TEST(Vector2D, Vector_Addition_Assignment)
{
   vector2D v1(1, 2, 0);
   vector2D v2(3, 4, 1);
   
   // "w" is implicitly 0
   vector2D result(5, 10);

   result += v1;
   EXPECT_FLOAT_EQ(6, result.x);
   EXPECT_FLOAT_EQ(12, result.y);
   EXPECT_FLOAT_EQ(0, result.w);

   result += v2;
   EXPECT_FLOAT_EQ(9, result.x);
   EXPECT_FLOAT_EQ(16, result.y);
   EXPECT_FLOAT_EQ(1, result.w);
}


TEST(Vector2D, Vector_Subtraction)
{
   vector2D v1(1, 2, 0);
   vector2D v2(3, 4, 1);

   vector2D result;

   result = v1 - v2;
   EXPECT_FLOAT_EQ(-2, result.x);
   EXPECT_FLOAT_EQ(-2, result.y);
   EXPECT_FLOAT_EQ(-1, result.w);

   result = v2 - v1 - v2 - v1;
   EXPECT_FLOAT_EQ(-2, result.x);
   EXPECT_FLOAT_EQ(-4, result.y);
   EXPECT_FLOAT_EQ(0, result.w);
}


TEST(Vector2D, Vector_Subtraction_Assignment)
{
   vector2D v1(1, 2, 0);
   vector2D v2(3, 4, 1);

   vector2D result(5, 10, 0);
   result -= v1;
   EXPECT_FLOAT_EQ(4, result.x);
   EXPECT_FLOAT_EQ(8, result.y);
   EXPECT_FLOAT_EQ(0, result.w);

   result -= v2;
   EXPECT_FLOAT_EQ(1, result.x);
   EXPECT_FLOAT_EQ(4, result.y);
   EXPECT_FLOAT_EQ(-1, result.w);
}


TEST(Vector2D, Scalar_Times_Vector)
{
   float scalar = 10.0f;

   vector2D v1(1, 2, 0);
   vector2D v2(3, 4, 1);
   vector2D result;
   
   result = scalar * v1;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(0, result.w);

   result = scalar * v2;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(10, result.w);
}


TEST(Vector2D, Vector_Times_Scalar)
{
   float scalar = 10.0f;

   vector2D v1(1, 2, 0);
   vector2D v2(3, 4, 1);
   vector2D result;

   result = v1 * scalar;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(0, result.w);

   result = v2 * scalar;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(10, result.w);
}


#endif
