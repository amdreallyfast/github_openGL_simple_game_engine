#include <gtest\gtest.h>

#include "math\matrix2D.h"
#include "math\vector2D.h""
#include "math\constants.h"
using namespace Math;

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
   // make a default one
   // Note: We already confirmed that the assignment operator worked, so use
   // this as the return value for each rotate(...) call.
   matrix2D rotation_matrix;
   vector2D rotated_vector;

   const float my_sqrt2_over_2 = SQRT_2 / 2.0f;
   const float my_sqrt3_over_2 = SQRT_3 / 2.0f;
   const float my_1_over_2 = 0.5f;


   // +pi/4 (45 degrees)
   rotation_matrix = matrix2D::rotate(PI / 4);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.x0);
   EXPECT_FLOAT_EQ((-1) * my_sqrt2_over_2, rotation_matrix.x1);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.y0);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.y1);

   // -pi/3 (45 degrees)
   rotation_matrix = matrix2D::rotate((-1) * PI / 3);
   EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.x0);
   EXPECT_FLOAT_EQ((-1) * (-1) * my_sqrt3_over_2, rotation_matrix.x1);
   EXPECT_FLOAT_EQ((-1) * my_sqrt3_over_2, rotation_matrix.y0);
   EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.y1);

   
   // now try rotating some vectors
   vector2D unit_along_x(1, 0);
   vector2D unit_along_y(0, 1);

   // rotate unit vector along x by +pi/4
   // Expected x: root(2) / 2
   // Expected y: 1 / 2
   rotation_matrix = matrix2D::rotate(PI / 4);
   rotated_vector = rotation_matrix * unit_along_x;
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotated_vector.x);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotated_vector.y);

   // rotate unit vector along y by -60 degrees (- pi/3)
   // Expected x: root(3) / 2
   // Expected y: 1 / 2
   rotation_matrix = matrix2D::rotate((-1) * PI / 3);
   rotated_vector = rotation_matrix * unit_along_y;
   EXPECT_FLOAT_EQ(my_sqrt3_over_2, rotated_vector.x);
   EXPECT_FLOAT_EQ(my_1_over_2, rotated_vector.y);
}

#endif
