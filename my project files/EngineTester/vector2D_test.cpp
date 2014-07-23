#include <gtest\gtest.h>

// this is my own vector definition
// Note: I had to edit the EngineTester project properties and add 
// "$(ProjectDir)\..\Engine" to my "Additional Include" directories.
#include <math/Vector2D.h>
using Math::Vector2D;

#include "math\constants.h"

#ifdef RUN_Vector2D_TESTS

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


TEST(Vector2D, Dot_Product)
{
   Vector2D first(1, 2, 3);
   Vector2D second(4, 5, 6);

   // Note: Resultes were computed by hand
   float result = first.dot(second);
   EXPECT_FLOAT_EQ(32, result);

   // check that the dot product of two normalized vectors from the unit
   // circle is the cosine of the angle between them
   Vector2D a(0.5f, Math::SQRT_3 / 2.0f);
   Vector2D b(Math::SQRT_3 / 2.0f, 0.5f);
   result = a.dot(b);
   EXPECT_FLOAT_EQ(cos(Math::PI / 6.0f), result);
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



void projection_test(
   const Vector2D& source, 
   const Vector2D& target)
{
   // the "normalized" projection approach, which we know works
   Vector2D target_normalized = target.normalize();
   Vector2D old_result = source.dot(target_normalized) * target_normalized;

   // the "no normalization" approach, which we are testing
   Vector2D new_result = source.project_onto(target);

   EXPECT_FLOAT_EQ(old_result.x, new_result.x);
   EXPECT_FLOAT_EQ(old_result.y, new_result.y);
   EXPECT_FLOAT_EQ(old_result.w, new_result.w);
}

TEST(Vector2D, Project_Onto)
{
   // simple case first
   Vector2D source(2, 4);
   Vector2D target(1, 0);
   Vector2D result = source.project_onto(target);
   EXPECT_FLOAT_EQ(2.0f, result.x);
   EXPECT_FLOAT_EQ(0.0f, result.y);
   EXPECT_FLOAT_EQ(0.0f, result.w);

   // more involved results
   // Note: It's okay that we're using the third value.  The math will be the
   // same as with only using x and y.
   Vector2D test_vectors[] = 
   {
      Vector2D(1.0f, 2.0f, 3.0f),
      Vector2D(4.8f, 9.3f, 2.6f),
      Vector2D(-0.2f, -5.9f, -2.3f),
      Vector2D(0.0f, -1.0f, 0.0f),
      Vector2D(-2.4f, +5.1f, -7.5f),
   };
   const int NUM_TEST_VECTORS = sizeof(test_vectors) / sizeof(*test_vectors);

   for (int index = 0; index < (NUM_TEST_VECTORS - 1); index++)
   {
      projection_test(test_vectors[index], test_vectors[index + 1]);
      projection_test(test_vectors[index + 1], test_vectors[index]);
   }
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


TEST(Vector2D, LERP)
{
   Vector2D source(1.2f, 3.4f, 5.6f);
   Vector2D target(7.8f, 9.0f, 14.8f);
   Vector2D diff = target - source;

   float alpha = 0.0f;
   while (alpha <= 1.0f)
   {
      Vector2D lerp_result_1 = lerp(source, target, alpha);
      Vector2D lerp_result_2 = source + (alpha * diff);

      EXPECT_FLOAT_EQ(lerp_result_1.x, lerp_result_2.x);
      EXPECT_FLOAT_EQ(lerp_result_1.y, lerp_result_2.y);
      EXPECT_FLOAT_EQ(lerp_result_1.w, lerp_result_2.w);

      alpha += 0.01f;
   }
}


#endif
