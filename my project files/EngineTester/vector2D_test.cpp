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
   vector2D default_constructor;
   EXPECT_FLOAT_EQ(0, default_constructor.x);
   EXPECT_FLOAT_EQ(0, default_constructor.y);
   EXPECT_FLOAT_EQ(0, default_constructor.enable_translate);

   vector2D v1(1, 2, 3);
   EXPECT_FLOAT_EQ(1, v1.x);
   EXPECT_FLOAT_EQ(2, v1.y);
   EXPECT_FLOAT_EQ(3, v1.enable_translate);
}

TEST(Vector2D, Length)
{
   vector2D v(3, 4);
   float length = v.length();

   EXPECT_FLOAT_EQ(5, length);
}

TEST(Vector2D, Vector_Addition)
{
   vector2D v1(1, 2, 3);
   vector2D v2(4, 5, 6);
   vector2D result;

   result = v1 + v2;
   EXPECT_FLOAT_EQ(5, result.x);
   EXPECT_FLOAT_EQ(7, result.y);
   EXPECT_FLOAT_EQ(9, result.enable_translate);

   result = v2 + v1;
   EXPECT_FLOAT_EQ(5, result.x);
   EXPECT_FLOAT_EQ(7, result.y);
   EXPECT_FLOAT_EQ(9, result.enable_translate);
}

TEST(Vector2D, Vector_Addition_Assignment)
{
   vector2D v1(5, 1234.5678f, -15);
   vector2D v2(1, 1);   // use default "enable_translate" value of 0
   v2 += v1;
   
   EXPECT_FLOAT_EQ(6, v2.x);
   EXPECT_FLOAT_EQ(1235.5678f, v2.y);
   EXPECT_FLOAT_EQ(-15, v2.enable_translate);
}

TEST(Vector2D, Vector_Subtraction)
{
   vector2D v1(1, 2, 3);
   vector2D v2(4, 5, 6);
   vector2D result;

   result = v1 - v2;
   EXPECT_FLOAT_EQ(-3, result.x);
   EXPECT_FLOAT_EQ(-3, result.y);
   EXPECT_FLOAT_EQ(-3, result.enable_translate);

   result = v2 - v1;
   EXPECT_FLOAT_EQ(3, result.x);
   EXPECT_FLOAT_EQ(3, result.y);
   EXPECT_FLOAT_EQ(3, result.enable_translate);
}

TEST(Vector2D, Vector_Subtraction_Assignment)
{
   vector2D v1(5, 1234.5678f, -15);
   vector2D v2(1, 1);   // use default "enable_translate" value of 0
   v2 -= v1;

   EXPECT_FLOAT_EQ(-4, v2.x);
   EXPECT_FLOAT_EQ(-1233.5678f, v2.y);
   EXPECT_FLOAT_EQ(15, v2.enable_translate);
}

TEST(Vector2D, Scalar_Multiplication)
{
   float scalar = 10.0f;
   vector2D v(1, 2, 3);
   vector2D result;
   
   result = scalar * v;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(30, result.enable_translate);

   result = v * scalar;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(30, result.enable_translate);
}

#endif
