#include <gtest\gtest.h>

#include "math\matrix2D.h"
#include "math\vector2D.h"
#include "math\constants.h"
using namespace Math;

#ifdef RUN_MATRIX2D_TESTS

TEST(Matrix2D, Constructor)
{
   // first check the default matrix
   matrix2D identity;
   EXPECT_FLOAT_EQ(1, identity.x0);    // row 0
   EXPECT_FLOAT_EQ(0, identity.x1);
   EXPECT_FLOAT_EQ(0, identity.x_translate);
   EXPECT_FLOAT_EQ(0, identity.y0);    // row 1
   EXPECT_FLOAT_EQ(1, identity.y1);
   EXPECT_FLOAT_EQ(0, identity.y_translate); // row 3
   EXPECT_FLOAT_EQ(0, identity.row2_col0);
   EXPECT_FLOAT_EQ(0, identity.row2_col1);
   EXPECT_FLOAT_EQ(1, identity.row2_col2);


   // now non-default constructor
   // Note: Ordinarily we would not create a matrix this way but would instead
   // summon one through a function like rotate(...) or translate(...), but this
   // is a test for the constructor, so we will test all the arguments.
   matrix2D some_matrix(
      2, 3, 4,
      5, 6, 7,
      8, 9, 10);
   EXPECT_FLOAT_EQ(2, some_matrix.x0);
   EXPECT_FLOAT_EQ(3, some_matrix.x1);
   EXPECT_FLOAT_EQ(4, some_matrix.x_translate);
   EXPECT_FLOAT_EQ(5, some_matrix.y0);
   EXPECT_FLOAT_EQ(6, some_matrix.y1);
   EXPECT_FLOAT_EQ(7, some_matrix.y_translate);
   EXPECT_FLOAT_EQ(8, some_matrix.row2_col0);
   EXPECT_FLOAT_EQ(9, some_matrix.row2_col1);
   EXPECT_FLOAT_EQ(10, some_matrix.row2_col2);
}


TEST(Matrix2D, Matrix_Matrix_Multiply)
{
   // again, we would not normally instialize a matrix this way, but this is a
   // controlled test, so we will make controlled matrices and check for a known
   // multiplication result

   matrix2D mat2d_1(
      1, 2, 3,
      4, 5, 6,
      7, 8, 9);
   matrix2D mat2d_2(
      9, 8, 7,
      6, 5, 4,
      3, 2, 1);

   matrix2D result;

   result = mat2d_1 * mat2d_2;
   EXPECT_FLOAT_EQ(30, result.x0);
   EXPECT_FLOAT_EQ(24, result.x1);
   EXPECT_FLOAT_EQ(18, result.x_translate);
   EXPECT_FLOAT_EQ(84, result.y0);
   EXPECT_FLOAT_EQ(69, result.y1);
   EXPECT_FLOAT_EQ(54, result.y_translate);
   EXPECT_FLOAT_EQ(138, result.row2_col0);
   EXPECT_FLOAT_EQ(114, result.row2_col1);
   EXPECT_FLOAT_EQ(90, result.row2_col2);

   result = mat2d_2 * mat2d_1;
   EXPECT_FLOAT_EQ(90, result.x0);
   EXPECT_FLOAT_EQ(114, result.x1);
   EXPECT_FLOAT_EQ(138, result.x_translate);
   EXPECT_FLOAT_EQ(54, result.y0);
   EXPECT_FLOAT_EQ(69, result.y1);
   EXPECT_FLOAT_EQ(84, result.y_translate);
   EXPECT_FLOAT_EQ(18, result.row2_col0);
   EXPECT_FLOAT_EQ(24, result.row2_col1);
   EXPECT_FLOAT_EQ(30, result.row2_col2);
}


TEST(Matrix2D, Matrix_Vector_Multiply)
{
   matrix2D linear_transform(
      1, 2, 3,
      4, 5, 6,
      7, 8, 9);
   vector2D v_t_disable(2, 9, 0);
   vector2D v_t_enable(2, 9, 1);
   
   //vector2D result = v * linear_transform;  // won't compile, which is good
   vector2D result;

   result = linear_transform * v_t_disable;
   // Expected result:
   // 1*2 + 2*9 + 3*0 = 20
   // 4*2 + 5*9 + 6*0 = 53
   // 7*2 + 8*9 + 9*0 = 86
   EXPECT_FLOAT_EQ(20, result.x);
   EXPECT_FLOAT_EQ(53, result.y);
   EXPECT_FLOAT_EQ(86, result.enable_translate);

   result = linear_transform * v_t_enable;
   // Expected result:
   // 1*2 + 2*9 + 3*1 = 23
   // 4*2 + 5*9 + 6*1 = 59
   // 7*2 + 8*9 + 9*1 = 95
   EXPECT_FLOAT_EQ(23, result.x);
   EXPECT_FLOAT_EQ(59, result.y);
   EXPECT_FLOAT_EQ(95, result.enable_translate);
}


TEST(Matrix2D, Matrix_Rotation)
{
   matrix2D rotation_matrix;

   const float my_sqrt2_over_2 = SQRT_2 / 2.0f;
   const float my_sqrt3_over_2 = SQRT_3 / 2.0f;
   const float my_1_over_2 = 0.5f;


   // +pi/4 (45 degrees)
   rotation_matrix = matrix2D::rotate(PI / 4);
   
   // check x
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.x0);
   EXPECT_FLOAT_EQ((-1) * my_sqrt2_over_2, rotation_matrix.x1);
   EXPECT_FLOAT_EQ(0, rotation_matrix.x_translate);

   // check y
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.y0);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.y1);
   EXPECT_FLOAT_EQ(0, rotation_matrix.y_translate);

   // check last row
   EXPECT_FLOAT_EQ(0, rotation_matrix.row2_col0);
   EXPECT_FLOAT_EQ(0, rotation_matrix.row2_col1);
   EXPECT_FLOAT_EQ(1, rotation_matrix.row2_col2);


   // -pi/3 (45 degrees)
   rotation_matrix = matrix2D::rotate((-1) * PI / 3);
   
   // check x
   EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.x0);
   EXPECT_FLOAT_EQ((-1) * (-1) * my_sqrt3_over_2, rotation_matrix.x1);
   EXPECT_FLOAT_EQ(0, rotation_matrix.x_translate);

   // check y
   EXPECT_FLOAT_EQ((-1) * my_sqrt3_over_2, rotation_matrix.y0);
   EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.y1);
   EXPECT_FLOAT_EQ(0, rotation_matrix.y_translate);

   // check last row
   EXPECT_FLOAT_EQ(0, rotation_matrix.row2_col0);
   EXPECT_FLOAT_EQ(0, rotation_matrix.row2_col1);
   EXPECT_FLOAT_EQ(1, rotation_matrix.row2_col2);

   
   // now try rotating some vectors
   vector2D unit_along_x(1, 0);
   vector2D unit_along_y(0, 1);
   vector2D rotated_vector;

   // rotate unit vector along x by +pi/4
   // Expected x: root(2) / 2
   // Expected y: 1 / 2
   rotation_matrix = matrix2D::rotate(PI / 4);
   rotated_vector = rotation_matrix * unit_along_x;
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotated_vector.x);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotated_vector.y);
   EXPECT_FLOAT_EQ(0, rotated_vector.enable_translate);

   // rotate unit vector along y by -60 degrees (- pi/3)
   // Expected x: root(3) / 2
   // Expected y: 1 / 2
   rotation_matrix = matrix2D::rotate((-1) * PI / 3);
   rotated_vector = rotation_matrix * unit_along_y;
   EXPECT_FLOAT_EQ(my_sqrt3_over_2, rotated_vector.x);
   EXPECT_FLOAT_EQ(my_1_over_2, rotated_vector.y);
   EXPECT_FLOAT_EQ(0, rotated_vector.enable_translate);
}


TEST(Matrix2D, Matrix_Translate)
{
   matrix2D translation_matrix;
   float delta_x;
   float delta_y;

   // translation check 1 (x_delta = -3, y_delta = +3)
   delta_x = -3;
   delta_y = +3;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // check x
   EXPECT_FLOAT_EQ(1, translation_matrix.x0);
   EXPECT_FLOAT_EQ(0, translation_matrix.x1);
   EXPECT_FLOAT_EQ(delta_x, translation_matrix.x_translate);

   // check y
   EXPECT_FLOAT_EQ(0, translation_matrix.y0);
   EXPECT_FLOAT_EQ(1, translation_matrix.y1);
   EXPECT_FLOAT_EQ(delta_y, translation_matrix.y_translate);

   // check last row
   EXPECT_FLOAT_EQ(0, translation_matrix.row2_col0);
   EXPECT_FLOAT_EQ(0, translation_matrix.row2_col1);
   EXPECT_FLOAT_EQ(1, translation_matrix.row2_col2);


   // translation check 1 (x_delta = -3, y_delta = +3)
   delta_x = +2;
   delta_y = -19;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // check x
   EXPECT_FLOAT_EQ(1, translation_matrix.x0);
   EXPECT_FLOAT_EQ(0, translation_matrix.x1);
   EXPECT_FLOAT_EQ(delta_x, translation_matrix.x_translate);

   // check y
   EXPECT_FLOAT_EQ(0, translation_matrix.y0);
   EXPECT_FLOAT_EQ(1, translation_matrix.y1);
   EXPECT_FLOAT_EQ(delta_y, translation_matrix.y_translate);

   // check last row
   EXPECT_FLOAT_EQ(0, translation_matrix.row2_col0);
   EXPECT_FLOAT_EQ(0, translation_matrix.row2_col1);
   EXPECT_FLOAT_EQ(1, translation_matrix.row2_col2);


   // now try translating some vectors
   vector2D v1_t_disable(2, 2, 0);     // translation disabled
   vector2D v1_t_enable(2, 2, 1);      // translation enabled
   vector2D v2_t_disable(-3, -3, 0);   // translation disabled
   vector2D v2_t_enable(-3, -3, 1);    // translation disabled
   vector2D translated_vector;

   delta_x = +4;
   delta_y = -5;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // shouldn't change
   translated_vector = translation_matrix * v1_t_disable;
   EXPECT_FLOAT_EQ(v1_t_disable.x, translated_vector.x);
   EXPECT_FLOAT_EQ(v1_t_disable.y, translated_vector.y);

   // now it should translate 
   translated_vector = translation_matrix * v1_t_enable;
   EXPECT_FLOAT_EQ(v1_t_enable.x + delta_x, translated_vector.x);
   EXPECT_FLOAT_EQ(v1_t_enable.y + delta_y, translated_vector.y);



   delta_x = -12;
   delta_y = +67;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // shouldn't change
   translated_vector = translation_matrix * v2_t_disable;
   EXPECT_FLOAT_EQ(v2_t_disable.x, translated_vector.x);
   EXPECT_FLOAT_EQ(v2_t_disable.y, translated_vector.y);

   // now it should translate 
   translated_vector = translation_matrix * v2_t_enable;
   EXPECT_FLOAT_EQ(v2_t_enable.x + delta_x, translated_vector.x);
   EXPECT_FLOAT_EQ(v2_t_enable.y + delta_y, translated_vector.y);

}

#endif
