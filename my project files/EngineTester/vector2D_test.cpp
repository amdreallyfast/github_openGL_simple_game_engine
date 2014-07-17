#include <gtest\gtest.h>

// this is my own vector definition
// Note: I had to edit the EngineTester project properties and add 
// "$(ProjectDir)\..\Engine" to my "Additional Include" directories.
#include <math/Vector2D.h>
using Math::Vector2D;

#ifdef RUN_VECTOR2D_TESTS

TEST(Vector2D, Constructor)
{
   // check default values
   Vector2D v0;
   EXPECT_FLOAT_EQ(0, v0.x);
   EXPECT_FLOAT_EQ(0, v0.y);
   EXPECT_FLOAT_EQ(0, v0.w);

   // a non-default constructor
   Vector2D v1(1, 2, 3);
   EXPECT_FLOAT_EQ(1, v1.x);
   EXPECT_FLOAT_EQ(2, v1.y);
   EXPECT_FLOAT_EQ(3, v1.w);
}


TEST(Vector2D, Magnitude)
{
   // for a 2D vector, the only things that are important to vector length
   // are the X and Y values, and anything else should be ignored
   Vector2D v(3, 4, 5);
   float mag = v.magnitude();

   // equals sqrt(50); value from google calculator
   EXPECT_FLOAT_EQ(7.07106781187f, mag);
}


TEST(Vector2D, Magnitude_Squared)
{
   Vector2D v(3, 4, 5);
   float mag_sq = v.magnitude_squared();

   EXPECT_FLOAT_EQ(50, mag_sq);
}


TEST(Vector2D, Normalization)
{
   Vector2D v(2, 3, 4);
   float original_length = v.magnitude();

   Vector2D result = v.normalize();
   float normalized_length = result.magnitude();

   EXPECT_FLOAT_EQ(1.0f, normalized_length);
   EXPECT_FLOAT_EQ(2.0f / original_length, result.x);
   EXPECT_FLOAT_EQ(3.0f / original_length, result.y);
   EXPECT_FLOAT_EQ(4.0f / original_length, result.w);
}


TEST(Vector2D, Vector_Addition)
{
   Vector2D v1(1, 2, 0);
   Vector2D v2(3, 4, 1);

   Vector2D result;

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
   Vector2D v1(1, 2, 0);
   Vector2D v2(3, 4, 1);
   
   // "w" is implicitly 0
   Vector2D result(5, 10);

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
   Vector2D v1(1, 2, 0);
   Vector2D v2(3, 4, 1);

   Vector2D result;

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
   Vector2D v1(1, 2, 0);
   Vector2D v2(3, 4, 1);

   Vector2D result(5, 10, 0);
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

   Vector2D v1(1, 2, 0);
   Vector2D v2(3, 4, 1);
   Vector2D result;
   
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

   Vector2D v1(1, 2, 0);
   Vector2D v2(3, 4, 1);
   Vector2D result;

   result = v1 * scalar;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(0, result.w);

   result = v2 * scalar;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(10, result.w);
}


TEST(Vector2D, Perpendicularity)
{
   Vector2D v(4, 2);
   
   Vector2D result = v.get_cw_perpendicular_vector();
   EXPECT_FLOAT_EQ(result.x, 2);
   EXPECT_FLOAT_EQ(result.y, -4);
   
   result = v.get_ccw_perpendicular_vector();
   EXPECT_FLOAT_EQ(result.x, -2);
   EXPECT_FLOAT_EQ(result.y, 4);
}


TEST(Vector2D, Dot_Product)
{
   Vector2D first(1, 2, 3);
   Vector2D second(4, 5, 6);

   // Note: Resultes were computed by hand
   float result = first.dot(second);
   EXPECT_FLOAT_EQ(32, result);
}


#endif
