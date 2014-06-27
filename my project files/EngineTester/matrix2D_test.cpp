#include <gtest\gtest.h>

#include <math\matrix2D.h>
using Math::matrix2D;

#include <math\vector2D.h>
using Math::vector2D;

// for square root and trig functions
#include <math.h>

#ifdef RUN_MATRIX2D_TESTS

TEST(Matrix2D, Constructor)
{
   // first check the default matrix
   matrix2D identity;
   EXPECT_FLOAT_EQ(1, identity.x0);
   EXPECT_FLOAT_EQ(0, identity.y0);
   EXPECT_FLOAT_EQ(0, identity.x1);
   EXPECT_FLOAT_EQ(1, identity.y1);


   // now non-default constructor
   matrix2D some_matrix(
      2, 3, 
      4, 5);
   EXPECT_FLOAT_EQ(2, some_matrix.x0);
   EXPECT_FLOAT_EQ(4, some_matrix.y0);
   EXPECT_FLOAT_EQ(3, some_matrix.x1);
   EXPECT_FLOAT_EQ(5, some_matrix.y1);
}


TEST(Matrix2D, Matrix_Vector_Multiply)
{
   matrix2D linear_transform(
      2, -3,
      4, -5);
   vector2D v(2, 9);
   //vector2D result = v * linear_transform;  // won't compile, which is good
   vector2D result = linear_transform * v;

   // Expected result:
   // 2*2 + (-3)*9 = -23   // row 0
   // 4*2 + (-5)*9 = -37   // row 1
   EXPECT_FLOAT_EQ(-23, result.x);
   EXPECT_FLOAT_EQ(-37, result.y);
}


TEST(Matrix2D, Matrix_Rotation)
{
   vector2D unit_along_x(1, 0);
   vector2D unit_along_y(0, 1);

   // rotate unit vector along x by +45 degrees (pi / 4)
   // Expected x: root(3) / 2
   // Expected y: 1 / 2
   matrix2D rotation_1 = matrix2D::rotate((1.0f / 4.0f) * 3.14159f);
   vector2D unit_along_x_rotated = rotation_1 * unit_along_x;
   EXPECT_FLOAT_EQ(sqrtf()
}

#endif
