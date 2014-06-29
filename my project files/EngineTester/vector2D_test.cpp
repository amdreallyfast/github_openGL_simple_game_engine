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
   // no arguments
   vector2D default_constructor;
   EXPECT_FLOAT_EQ(0, default_constructor.x);
   EXPECT_FLOAT_EQ(0, default_constructor.y);
   EXPECT_FLOAT_EQ(0, default_constructor.enable_translate);
   EXPECT_FLOAT_EQ(0, default_constructor.enable_non_origin_rotation);

   // only the numical arguments
   vector2D v_with_only_numbers(1, 2);
   EXPECT_FLOAT_EQ(1, v_with_only_numbers.x);
   EXPECT_FLOAT_EQ(2, v_with_only_numbers.y);
   EXPECT_FLOAT_EQ(0, v_with_only_numbers.enable_translate);
   EXPECT_FLOAT_EQ(0, v_with_only_numbers.enable_non_origin_rotation);

   // explicitly enable both translate and non-zero rotation flags
   vector2D v1(1, 2, true, true);
   EXPECT_FLOAT_EQ(1, v1.x);
   EXPECT_FLOAT_EQ(2, v1.y);
   EXPECT_FLOAT_EQ(1, v1.enable_translate);
   EXPECT_FLOAT_EQ(1, v1.enable_non_origin_rotation);

   // explicitly disable both translate and non-zero rotation flags
   vector2D v2(1, 2, false, false);
   EXPECT_FLOAT_EQ(1, v2.x);
   EXPECT_FLOAT_EQ(2, v2.y);
   EXPECT_FLOAT_EQ(0, v2.enable_translate);
   EXPECT_FLOAT_EQ(0, v2.enable_non_origin_rotation);
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
   // let one vector have translation and non-origin rotation disabled,
   // and let the other have them enabled
   vector2D v1(1, 2, false, false);
   vector2D v2(5, 6, true, true);
   vector2D result;

   // add disabled to disabled and check that resulting vector's flags 
   // are disabled
   result = v1 + v1;
   EXPECT_FLOAT_EQ(2, result.x);
   EXPECT_FLOAT_EQ(4, result.y);
   EXPECT_FLOAT_EQ(0, result.enable_translate);
   EXPECT_FLOAT_EQ(0, result.enable_non_origin_rotation);

   // add enabled to enabled and check that resulting vector's flags
   // are enabled
   result = v2 + v2;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(12, result.y);
   EXPECT_FLOAT_EQ(1, result.enable_translate);
   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);

   // add enabled to disabled and vice versa and check that resulting 
   // vector's flags are enabled
   result = v1 + v2;
   EXPECT_FLOAT_EQ(6, result.x);
   EXPECT_FLOAT_EQ(8, result.y);
   EXPECT_FLOAT_EQ(1, result.enable_translate);
   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);

   result = v2 + v1;
   EXPECT_FLOAT_EQ(6, result.x);
   EXPECT_FLOAT_EQ(8, result.y);
   EXPECT_FLOAT_EQ(1, result.enable_translate);
   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);
}


TEST(Vector2D, Vector_Addition_Assignment)
{
   // let one vector have translation and non-origin rotation disabled,
   // and let the other have them enabled
   vector2D v1(1, 2, false, false);
   vector2D v2(3, 4, true, true);
   
   // add a (disabled, disabled) vector to a (disabled, disabled) vector
   // Expected result: (disabled, disabled)
   vector2D result_1(0, 0, false, false);
   result_1 += v1;
   EXPECT_FLOAT_EQ(1, result_1.x);
   EXPECT_FLOAT_EQ(2, result_1.y);
   EXPECT_FLOAT_EQ(0, result_1.enable_translate);
   EXPECT_FLOAT_EQ(0, result_1.enable_non_origin_rotation);

   // add a (disabled, disabled) vector to an (enabled, enabled) vector
   // Expected result: (enabled, enabled)
   vector2D result_2(0, 0, false, false);
   result_2 += v2;
   EXPECT_FLOAT_EQ(3, result_2.x);
   EXPECT_FLOAT_EQ(4, result_2.y);
   EXPECT_FLOAT_EQ(1, result_2.enable_translate);
   EXPECT_FLOAT_EQ(1, result_2.enable_non_origin_rotation);

   // add an (enabled, enabled) vector to a (disabled, disabled) vector
   // Expected result: (enabled, enabled)
   vector2D result_3(0, 0, true, true);
   result_3 += v1;
   EXPECT_FLOAT_EQ(1, result_3.x);
   EXPECT_FLOAT_EQ(2, result_3.y);
   EXPECT_FLOAT_EQ(1, result_3.enable_translate);
   EXPECT_FLOAT_EQ(1, result_3.enable_non_origin_rotation);

   // add an (enabled, enabled) vector to a (enabled, enabled) vector
   // Expected result: (enabled, enabled)
   vector2D result_4(0, 0, true, true);
   result_4 += v2;
   EXPECT_FLOAT_EQ(3, result_4.x);
   EXPECT_FLOAT_EQ(4, result_4.y);
   EXPECT_FLOAT_EQ(1, result_4.enable_translate);
   EXPECT_FLOAT_EQ(1, result_4.enable_non_origin_rotation);
}


TEST(Vector2D, Vector_Subtraction)
{
   // let one vector have translation and non-origin rotation disabled,
   // and let the other have them enabled
   vector2D v1(1, 2, false, false);
   vector2D v2(5, 6, true, true);
   vector2D result;

   // subtract disabled from disabled and check that resulting vector's flags 
   // are disabled
   result = v1 - v1;
   EXPECT_FLOAT_EQ(0, result.x);
   EXPECT_FLOAT_EQ(0, result.y);
   EXPECT_FLOAT_EQ(0, result.enable_translate);
   EXPECT_FLOAT_EQ(0, result.enable_non_origin_rotation);

   // subtract enabled from enabled and check that resulting vector's flags
   // are enabled
   result = v2 - v2;
   EXPECT_FLOAT_EQ(0, result.x);
   EXPECT_FLOAT_EQ(0, result.y);
   EXPECT_FLOAT_EQ(1, result.enable_translate);
   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);

   // subtract enabled from disabled and vice versa and check that resulting 
   // vector's flags are enabled
   result = v1 - v2;
   EXPECT_FLOAT_EQ(-4, result.x);
   EXPECT_FLOAT_EQ(-4, result.y);
   EXPECT_FLOAT_EQ(1, result.enable_translate);
   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);

   result = v2 - v1;
   EXPECT_FLOAT_EQ(4, result.x);
   EXPECT_FLOAT_EQ(4, result.y);
   EXPECT_FLOAT_EQ(1, result.enable_translate);
   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);
}


TEST(Vector2D, Vector_Subtraction_Assignment)
{
   // let one vector have translation and non-origin rotation disabled,
   // and let the other have them enabled
   vector2D v1(1, 2, false, false);
   vector2D v2(3, 4, true, true);

   // subtract a (disabled, disabled) vector from a (disabled, disabled) vector
   // Expected result: (disabled, disabled)
   vector2D result_1(0, 0, false, false);
   result_1 -= v1;
   EXPECT_FLOAT_EQ(-1, result_1.x);
   EXPECT_FLOAT_EQ(-2, result_1.y);
   EXPECT_FLOAT_EQ(0, result_1.enable_translate);
   EXPECT_FLOAT_EQ(0, result_1.enable_non_origin_rotation);

   // subtract a (disabled, disabled) vector from an (enabled, enabled) vector
   // Expected result: (enabled, enabled)
   vector2D result_2(0, 0, false, false);
   result_2 -= v2;
   EXPECT_FLOAT_EQ(-3, result_2.x);
   EXPECT_FLOAT_EQ(-4, result_2.y);
   EXPECT_FLOAT_EQ(1, result_2.enable_translate);
   EXPECT_FLOAT_EQ(1, result_2.enable_non_origin_rotation);

   // subtract an (enabled, enabled) vector from a (disabled, disabled) vector
   // Expected result: (enabled, enabled)
   vector2D result_3(0, 0, true, true);
   result_3 -= v1;
   EXPECT_FLOAT_EQ(-1, result_3.x);
   EXPECT_FLOAT_EQ(-2, result_3.y);
   EXPECT_FLOAT_EQ(1, result_3.enable_translate);
   EXPECT_FLOAT_EQ(1, result_3.enable_non_origin_rotation);

   // subtract an (enabled, enabled) vector from a (enabled, enabled) vector
   // Expected result: (enabled, enabled)
   vector2D result_4(0, 0, true, true);
   result_4 -= v2;
   EXPECT_FLOAT_EQ(-3, result_4.x);
   EXPECT_FLOAT_EQ(-4, result_4.y);
   EXPECT_FLOAT_EQ(1, result_4.enable_translate);
   EXPECT_FLOAT_EQ(1, result_4.enable_non_origin_rotation);
}


TEST(Vector2D, Scalar_Times_Vector)
{
   float scalar = 10.0f;
   vector2D v1(1, 2, false, false);
   vector2D v2(3, 4, true, true);
   vector2D result;
   
   result = scalar * v1;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(0, result.enable_translate);
   EXPECT_FLOAT_EQ(0, result.enable_non_origin_rotation);

   result = scalar * v2;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(true, result.enable_translate);
   EXPECT_FLOAT_EQ(true, result.enable_non_origin_rotation);
}


TEST(Vector2D, Vector_Times_Scalar)
{
   float scalar = 10.0f;
   vector2D v1(1, 2, false, false);
   vector2D v2(3, 4, true, true);
   vector2D result;

   result = v1 * scalar;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(0, result.enable_translate);
   EXPECT_FLOAT_EQ(0, result.enable_non_origin_rotation);

   result = v2 * scalar;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(true, result.enable_translate);
   EXPECT_FLOAT_EQ(true, result.enable_non_origin_rotation);
}


#endif
