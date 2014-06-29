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
   EXPECT_FLOAT_EQ(1, v0.t);

   // and check that the last value is 
   // changed to 0 (it is supposed to only be 0 or 1 and defaults to 0
   // if it is not between 0.99 and 1.01)
   vector2D v1(1, 2, 3);
   EXPECT_FLOAT_EQ(1, v1.x);
   EXPECT_FLOAT_EQ(2, v1.y);
   EXPECT_FLOAT_EQ(0, v1.t);

   // check that the last argument's 1 remains a 1
   vector2D v2(3, 4, 1);
   EXPECT_FLOAT_EQ(3, v2.x);
   EXPECT_FLOAT_EQ(4, v2.y);
   EXPECT_FLOAT_EQ(1, v2.t);

   // check that the last argument's 0 remains a 0
   vector2D v3(5, 6, 0);
   EXPECT_FLOAT_EQ(5, v3.x);
   EXPECT_FLOAT_EQ(6, v3.y);
   EXPECT_FLOAT_EQ(0, v3.t);
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
   // implicitly enable translation
   vector2D v1(1, 2);

   // explicitly disable translation
   vector2D v2(3, 4, 0);

   vector2D result;

   // check numerical results first
   result = v1 + v2;
   EXPECT_FLOAT_EQ(4, result.x);
   EXPECT_FLOAT_EQ(6, result.y);

   result = v2 + v1;
   EXPECT_FLOAT_EQ(4, result.x);
   EXPECT_FLOAT_EQ(6, result.y);


   // now check the third value, the "enable translate" value

   // add enabled to enabled and check that resulting vector's flags
   // are enabled
   result = v1 + v1;
   EXPECT_FLOAT_EQ(1, result.t);

   // add disabled to disabled and check that resulting vector's flags 
   // are disabled
   result = v2 + v2;
   EXPECT_FLOAT_EQ(0, result.t);

   // add enabled to disabled and vice versa and check that resulting 
   // vector's flags are enabled
   result = v1 + v2;
   EXPECT_FLOAT_EQ(1, result.t);

   result = v2 + v1;
   EXPECT_FLOAT_EQ(1, result.t);
}


TEST(Vector2D, Vector_Addition_Assignment)
{
   // implicitly enable translation
   vector2D v1(1, 2);

   // explicitly disable translation
   vector2D v2(3, 4, 0);
   
   // check numeric results first
   vector2D result_1(5, 10);
   result_1 += v1;
   EXPECT_FLOAT_EQ(6, result_1.x);
   EXPECT_FLOAT_EQ(12, result_1.y);

   result_1 += v2;
   EXPECT_FLOAT_EQ(9, result_1.x);
   EXPECT_FLOAT_EQ(16, result_1.y);


   // now check the third value, the "enable translate" value

   // add enabled to enabled and check that resulting vector's flags
   // are enabled
   vector2D result_2(0, 0);
   result_2 += v1;
   EXPECT_FLOAT_EQ(1, result_2.t);

   // add disabled to disabled and check that resulting vector's flags 
   // are disabled
   vector2D result_3(0, 0, 0);
   result_3 += v2;
   EXPECT_FLOAT_EQ(0, result_3.t);

   // add enabled to disabled and vice versa and check that resulting 
   // vector's flags are enabled
   vector2D result_4(0, 0);
   result_4 += v2;
   EXPECT_FLOAT_EQ(1, result_4.t);

   vector2D result_5(0, 0, 0);
   result_5 += v1;
   EXPECT_FLOAT_EQ(1, result_5.t);
}


TEST(Vector2D, Vector_Subtraction)
{
   // implicitly enable translation
   vector2D v1(1, 2);

   // explicitly disable translation
   vector2D v2(3, 4, 0);

   vector2D result;

   // check numerical results first
   result = v1 - v2;
   EXPECT_FLOAT_EQ(-2, result.x);
   EXPECT_FLOAT_EQ(-2, result.y);

   result = v2 - v1;
   EXPECT_FLOAT_EQ(2, result.x);
   EXPECT_FLOAT_EQ(2, result.y);


   // now check the third value, the "enable translate" value

   // subtract enabled from enabled and check that resulting vector's flags
   // are enabled
   result = v1 - v1;
   EXPECT_FLOAT_EQ(1, result.t);

   // subtract disabled from disabled and check that resulting vector's flags 
   // are disabled
   result = v2 - v2;
   EXPECT_FLOAT_EQ(0, result.t);

   // subtract enabled from disabled and vice versa and check that resulting 
   // vector's flags are enabled
   result = v1 - v2;
   EXPECT_FLOAT_EQ(1, result.t);

   result = v2 - v1;
   EXPECT_FLOAT_EQ(1, result.t);
}


TEST(Vector2D, Vector_Subtraction_Assignment)
{
   // implicitly enable translation
   vector2D v1(1, 2);

   // explicitly disable translation
   vector2D v2(3, 4, 0);

   // check numeric results first
   vector2D result_1(5, 10);
   result_1 -= v1;
   EXPECT_FLOAT_EQ(4, result_1.x);
   EXPECT_FLOAT_EQ(8, result_1.y);

   result_1 -= v2;
   EXPECT_FLOAT_EQ(1, result_1.x);
   EXPECT_FLOAT_EQ(4, result_1.y);


   // now check the third value, the "enable translate" value

   // subtract enabled from enabled and check that resulting vector's flags
   // are enabled
   vector2D result_2(0, 0);
   result_2 -= v1;
   EXPECT_FLOAT_EQ(1, result_2.t);

   // subtract disabled from disabled and check that resulting vector's flags 
   // are disabled
   vector2D result_3(0, 0, 0);
   result_3 -= v2;
   EXPECT_FLOAT_EQ(0, result_3.t);

   // subtract enabled from disabled and vice versa and check that resulting 
   // vector's flags are enabled
   vector2D result_4(0, 0);
   result_4 -= v2;
   EXPECT_FLOAT_EQ(1, result_4.t);

   vector2D result_5(0, 0, 0);
   result_5 -= v1;
   EXPECT_FLOAT_EQ(1, result_5.t);
}


TEST(Vector2D, Scalar_Times_Vector)
{
   float scalar = 10.0f;

   // implicitly enable translation
   vector2D v1(1, 2);

   // explicitly disable translation
   vector2D v2(3, 4, 0);
   vector2D result;
   
   result = scalar * v1;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(1, result.t);

   result = scalar * v2;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(0, result.t);
}


TEST(Vector2D, Vector_Times_Scalar)
{
   float scalar = 10.0f;

   // implicitly enable translation
   vector2D v1(1, 2);

   // explicitly disable translation
   vector2D v2(3, 4, 0);
   vector2D result;

   result = v1 * scalar;
   EXPECT_FLOAT_EQ(10, result.x);
   EXPECT_FLOAT_EQ(20, result.y);
   EXPECT_FLOAT_EQ(1, result.t);

   result = v2 * scalar;
   EXPECT_FLOAT_EQ(30, result.x);
   EXPECT_FLOAT_EQ(40, result.y);
   EXPECT_FLOAT_EQ(0, result.t);
}


#endif
