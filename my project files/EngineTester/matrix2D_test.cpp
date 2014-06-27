#include <gtest\gtest.h>

#include <math\matrix2D.h>
using Math::matrix2D;

#include <math\vector2D.h>
using Math::vector2D;

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
   matrix2D linear_transform = matrix2D::rotate(0);
   vector2D v(2, 9);
}

#endif
