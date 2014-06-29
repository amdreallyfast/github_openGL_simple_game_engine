#include <gtest\gtest.h>

#include "math\matrix2D.h"
#include "math\vector2D.h"
#include "math\constants.h"
using namespace Math;

#ifdef RUN_MATRIX2D_TESTS

//TEST(Matrix2D, Constructor)
//{
//   // default constructor
//   // Note: This matrix is intended for test purposes only, but it is still
//   // tested before any other functions are tested for good measure.
//   matrix2D identity;
//
//   // row 0
//   EXPECT_FLOAT_EQ(1, identity.a00);
//   EXPECT_FLOAT_EQ(0, identity.a01);
//   EXPECT_FLOAT_EQ(0, identity.a02);
//   EXPECT_FLOAT_EQ(0, identity.a03);
//
//   // row 1
//   EXPECT_FLOAT_EQ(0, identity.a10);
//   EXPECT_FLOAT_EQ(1, identity.a11);
//   EXPECT_FLOAT_EQ(0, identity.a12);
//   EXPECT_FLOAT_EQ(0, identity.a13);
//
//   // row 2
//   EXPECT_FLOAT_EQ(0, identity.a20);
//   EXPECT_FLOAT_EQ(0, identity.a21);
//   EXPECT_FLOAT_EQ(1, identity.a22);
//   EXPECT_FLOAT_EQ(0, identity.a23);
//
//   // row 3
//   EXPECT_FLOAT_EQ(0, identity.a30);
//   EXPECT_FLOAT_EQ(0, identity.a31);
//   EXPECT_FLOAT_EQ(0, identity.a32);
//   EXPECT_FLOAT_EQ(1, identity.a33);
//
//
//
//   // now non-default constructor
//   // Note: Ordinarily we would not create a matrix this way but would instead
//   // summon one through a function like rotate(...) or translate(...), which
//   // use private constructors to make a very specific matrix with the 
//   // remaining diagonals being 1 and everything else 0, but this is a test 
//   // for the constructor so that future tests, such as matrix multiply, can
//   // build what they want, so we will test all the arguments. 
//   matrix2D some_matrix(
//      1, 2, 3, 4,
//      5, 6, 7, 8, 
//      9, 10, 11, 12, 
//      13, 14, 15, 16);
//
//   // row 0
//   EXPECT_FLOAT_EQ(1, some_matrix.a00);
//   EXPECT_FLOAT_EQ(2, some_matrix.a01);
//   EXPECT_FLOAT_EQ(3, some_matrix.a02);
//   EXPECT_FLOAT_EQ(4, some_matrix.a03);
//
//   // row 1
//   EXPECT_FLOAT_EQ(5, some_matrix.a10);
//   EXPECT_FLOAT_EQ(6, some_matrix.a11);
//   EXPECT_FLOAT_EQ(7, some_matrix.a12);
//   EXPECT_FLOAT_EQ(8, some_matrix.a13);
//
//   // row 2
//   EXPECT_FLOAT_EQ(9, some_matrix.a20);
//   EXPECT_FLOAT_EQ(10, some_matrix.a21);
//   EXPECT_FLOAT_EQ(11, some_matrix.a22);
//   EXPECT_FLOAT_EQ(12, some_matrix.a23);
//
//   // row 3
//   EXPECT_FLOAT_EQ(13, some_matrix.a30);
//   EXPECT_FLOAT_EQ(14, some_matrix.a31);
//   EXPECT_FLOAT_EQ(15, some_matrix.a32);
//   EXPECT_FLOAT_EQ(16, some_matrix.a33);
//}
//
//
//TEST(Matrix2D, Matrix_Matrix_Multiply)
//{
//   // again, we would not normally instialize a matrix this way, but this is a
//   // controlled test, so we will make controlled matrices and check for a known
//   // multiplication result
//
//   matrix2D mat2d_1(
//      1, 2, 3, 4,
//      5, 6, 7, 8,
//      9, 10, 11, 12,
//      13, 14, 15, 16);
//   matrix2D mat2d_2(
//      16, 15, 14, 13,
//      12, 11, 10, 9,
//      8, 7, 6, 5,
//      4, 3, 2, 1);
//
//   matrix2D result;
//
//   // got my result from an online matrix calculator:
//   // http://www.bluebit.gr/matrix-calculator/matrix_multiplication.aspx
//   result = mat2d_1 * mat2d_2;
//   
//   // row 0
//   EXPECT_FLOAT_EQ(80, result.a00);
//   EXPECT_FLOAT_EQ(70, result.a01);
//   EXPECT_FLOAT_EQ(60, result.a02);
//   EXPECT_FLOAT_EQ(50, result.a03);
//
//   // row 1
//   EXPECT_FLOAT_EQ(240, result.a10);
//   EXPECT_FLOAT_EQ(214, result.a11);
//   EXPECT_FLOAT_EQ(188, result.a12);
//   EXPECT_FLOAT_EQ(162, result.a13);
//
//   // row 2
//   EXPECT_FLOAT_EQ(400, result.a20);
//   EXPECT_FLOAT_EQ(358, result.a21);
//   EXPECT_FLOAT_EQ(316, result.a22);
//   EXPECT_FLOAT_EQ(274, result.a23);
//
//   // row 3
//   EXPECT_FLOAT_EQ(560, result.a30);
//   EXPECT_FLOAT_EQ(502, result.a31);
//   EXPECT_FLOAT_EQ(444, result.a32);
//   EXPECT_FLOAT_EQ(386, result.a33);
//
//
//   // now multiply in the reverse order
//   result = mat2d_2 * mat2d_1;
//
//   EXPECT_FLOAT_EQ(386, result.a00);
//   EXPECT_FLOAT_EQ(444, result.a01);
//   EXPECT_FLOAT_EQ(502, result.a02);
//   EXPECT_FLOAT_EQ(560, result.a03);
//
//   // row 1
//   EXPECT_FLOAT_EQ(274, result.a10);
//   EXPECT_FLOAT_EQ(316, result.a11);
//   EXPECT_FLOAT_EQ(358, result.a12);
//   EXPECT_FLOAT_EQ(400, result.a13);
//
//   // row 2
//   EXPECT_FLOAT_EQ(162, result.a20);
//   EXPECT_FLOAT_EQ(188, result.a21);
//   EXPECT_FLOAT_EQ(214, result.a22);
//   EXPECT_FLOAT_EQ(240, result.a23);
//
//   // row 3
//   EXPECT_FLOAT_EQ(50, result.a30);
//   EXPECT_FLOAT_EQ(60, result.a31);
//   EXPECT_FLOAT_EQ(70, result.a32);
//   EXPECT_FLOAT_EQ(80, result.a33);
//}
//
//
//TEST(Matrix2D, Matrix_Vector_Multiply)
//{
//   matrix2D linear_transform(
//      1, 2, 3, 4,
//      5, 6, 7, 8,
//      9, 10, 11, 12,
//      13, 14, 15, 16);
//
//   vector2D v1(1, 1, false, false);
//   vector2D v2(1, 1, false, true);
//   vector2D v3(1, 1, true, true);
//   vector2D v4(1, 1, true, false);
//
//   //vector2D result = v1 * linear_transform;  // won't compile, which is good
//   vector2D result;
//
//   // multiply the linear transform by vectors that selectively disable and
//   // enable translation and non-orgin rotation
//
//   // got my result from an online matrix calculator:
//   // http://www.bluebit.gr/matrix-calculator/matrix_multiplication.aspx
//
//   result = linear_transform * v1;
//   EXPECT_FLOAT_EQ(3, result.x);
//   EXPECT_FLOAT_EQ(11, result.y);
//   EXPECT_FLOAT_EQ(0, result.enable_translate);
//   EXPECT_FLOAT_EQ(0, result.enable_non_origin_rotation);
//
//   result = linear_transform * v2;
//   EXPECT_FLOAT_EQ(7, result.x);
//   EXPECT_FLOAT_EQ(19, result.y);
//   EXPECT_FLOAT_EQ(0, result.enable_translate);
//   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);
//
//   result = linear_transform * v3;
//   EXPECT_FLOAT_EQ(10, result.x);
//   EXPECT_FLOAT_EQ(26, result.y);
//   EXPECT_FLOAT_EQ(1, result.enable_translate);
//   EXPECT_FLOAT_EQ(1, result.enable_non_origin_rotation);
//
//   result = linear_transform * v4;
//   EXPECT_FLOAT_EQ(6, result.x);
//   EXPECT_FLOAT_EQ(18, result.y);
//   EXPECT_FLOAT_EQ(1, result.enable_translate);
//   EXPECT_FLOAT_EQ(0, result.enable_non_origin_rotation);
//}
//
//
//TEST(Matrix2D, Matrix_Rotation_Around_Origin)
//{
//   matrix2D rotation_matrix;
//
//   const float my_sqrt2_over_2 = SQRT_2 / 2.0f;
//   const float my_sqrt3_over_2 = SQRT_3 / 2.0f;
//   const float my_1_over_2 = 0.5f;
//
//
//   // +pi/4 (45 degrees)
//   rotation_matrix = matrix2D::rotate(PI / 4);
//   
//   // row 0
//   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a00);
//   EXPECT_FLOAT_EQ((-1) * my_sqrt2_over_2, rotation_matrix.a01);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a02);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a03);
//
//   // row 1
//   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a10);
//   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a11);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a12);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a13);
//
//   // row 2
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a20);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a21);
//   EXPECT_FLOAT_EQ(1, rotation_matrix.a22);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a23);
//
//   // row 3
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a30);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a31);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a32);
//   EXPECT_FLOAT_EQ(1, rotation_matrix.a33);
//
//
//   //// -pi/3 (45 degrees)
//   //rotation_matrix = matrix2D::rotate((-1) * PI / 3);
//   //
//   //// check x
//   //EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.a00);
//   //EXPECT_FLOAT_EQ((-1) * (-1) * my_sqrt3_over_2, rotation_matrix.a01);
//   //EXPECT_FLOAT_EQ(0, rotation_matrix.a02);
//
//   //// check y
//   //EXPECT_FLOAT_EQ((-1) * my_sqrt3_over_2, rotation_matrix.a10);
//   //EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.a11);
//   //EXPECT_FLOAT_EQ(0, rotation_matrix.a12);
//
//   //// check last row
//   //EXPECT_FLOAT_EQ(0, rotation_matrix.a20);
//   //EXPECT_FLOAT_EQ(0, rotation_matrix.a21);
//   //EXPECT_FLOAT_EQ(1, rotation_matrix.a22);
//
//   //
//   //// now try rotating some vectors
//   //// Note: We already checked multiplying matrix by vector, so don't 
//   //// bother checking the "enable" flags.
//   //vector2D unit_along_x(1, 0);
//   //vector2D unit_along_y(0, 1);
//   //vector2D rotated_vector;
//
//   //// rotate unit vector along x by +pi/4
//   //// Expected x: root(2) / 2
//   //// Expected y: 1 / 2
//   //rotation_matrix = matrix2D::rotate(PI / 4);
//   //rotated_vector = rotation_matrix * unit_along_x;
//   //EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotated_vector.x);
//   //EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotated_vector.y);
//
//   //// rotate unit vector along y by -60 degrees (- pi/3)
//   //// Expected x: root(3) / 2
//   //// Expected y: 1 / 2
//   //rotation_matrix = matrix2D::rotate((-1) * PI / 3);
//   //rotated_vector = rotation_matrix * unit_along_y;
//   //EXPECT_FLOAT_EQ(my_sqrt3_over_2, rotated_vector.x);
//   //EXPECT_FLOAT_EQ(my_1_over_2, rotated_vector.y);
//}
//
//
//TEST(Matrix2D, Matrix_Rotation_Around_Non_Origin)
//{
//   matrix2D rotation_matrix;
//   vector2D non_origin_rotation(0, -2);
//
//   const float my_sqrt2_over_2 = SQRT_2 / 2.0f;
//   const float my_sqrt3_over_2 = SQRT_3 / 2.0f;
//   const float my_1_over_2 = 0.5f;
//
//
//   // +pi/4 (45 degrees)
//   rotation_matrix = matrix2D::rotate(PI / 4, non_origin_rotation.x, non_origin_rotation.y);
//
//   // I did the calculation by hand
//
//   // row 0
//   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a00);
//   EXPECT_FLOAT_EQ((-1) * my_sqrt2_over_2, rotation_matrix.a01);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a02);
//   EXPECT_FLOAT_EQ((-1) * SQRT_2, rotation_matrix.a03);
//
//   // row 1
//   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a10);
//   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a11);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a12);
//   EXPECT_FLOAT_EQ(SQRT_2 - 2, rotation_matrix.a13);
//
//   // row 2
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a20);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a21);
//   EXPECT_FLOAT_EQ(1, rotation_matrix.a22);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a23);
//
//   // row 3
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a30);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a31);
//   EXPECT_FLOAT_EQ(0, rotation_matrix.a32);
//   EXPECT_FLOAT_EQ(1, rotation_matrix.a33);
//}
//



//
//TEST(Matrix2D, Matria02)
//{
//   matrix2D translation_matrix;
//   float delta_x;
//   float delta_y;
//
//   // translation check 1 (x_delta = -3, y_delta = +3)
//   delta_x = -3;
//   delta_y = +3;
//   translation_matrix = matrix2D::translate(delta_x, delta_y);
//
//   // check x
//   EXPECT_FLOAT_EQ(1, translation_matrix.a00);
//   EXPECT_FLOAT_EQ(0, translation_matrix.a01);
//   EXPECT_FLOAT_EQ(delta_x, translation_matrix.a02);
//
//   // check y
//   EXPECT_FLOAT_EQ(0, translation_matrix.a10);
//   EXPECT_FLOAT_EQ(1, translation_matrix.a11);
//   EXPECT_FLOAT_EQ(delta_y, translation_matrix.a12);
//
//   // check last row
//   EXPECT_FLOAT_EQ(0, translation_matrix.a20);
//   EXPECT_FLOAT_EQ(0, translation_matrix.a21);
//   EXPECT_FLOAT_EQ(1, translation_matrix.a22);
//
//
//   // translation check 1 (x_delta = -3, y_delta = +3)
//   delta_x = +2;
//   delta_y = -19;
//   translation_matrix = matrix2D::translate(delta_x, delta_y);
//
//   // check x
//   EXPECT_FLOAT_EQ(1, translation_matrix.a00);
//   EXPECT_FLOAT_EQ(0, translation_matrix.a01);
//   EXPECT_FLOAT_EQ(delta_x, translation_matrix.a02);
//
//   // check y
//   EXPECT_FLOAT_EQ(0, translation_matrix.a10);
//   EXPECT_FLOAT_EQ(1, translation_matrix.a11);
//   EXPECT_FLOAT_EQ(delta_y, translation_matrix.a12);
//
//   // check last row
//   EXPECT_FLOAT_EQ(0, translation_matrix.a20);
//   EXPECT_FLOAT_EQ(0, translation_matrix.a21);
//   EXPECT_FLOAT_EQ(1, translation_matrix.a22);
//
//
//   // now try translating some vectors
//   vector2D v1_t_disable(2, 2, 0);     // translation disabled
//   vector2D v1_t_enable(2, 2, 1);      // translation enabled
//   vector2D v2_t_disable(-3, -3, 0);   // translation disabled
//   vector2D v2_t_enable(-3, -3, 1);    // translation disabled
//   vector2D translated_vector;
//
//   delta_x = +4;
//   delta_y = -5;
//   translation_matrix = matrix2D::translate(delta_x, delta_y);
//
//   // shouldn't change
//   translated_vector = translation_matrix * v1_t_disable;
//   EXPECT_FLOAT_EQ(v1_t_disable.x, translated_vector.x);
//   EXPECT_FLOAT_EQ(v1_t_disable.y, translated_vector.y);
//
//   // now it should translate 
//   translated_vector = translation_matrix * v1_t_enable;
//   EXPECT_FLOAT_EQ(v1_t_enable.x + delta_x, translated_vector.x);
//   EXPECT_FLOAT_EQ(v1_t_enable.y + delta_y, translated_vector.y);
//
//
//
//   delta_x = -12;
//   delta_y = +67;
//   translation_matrix = matrix2D::translate(delta_x, delta_y);
//
//   // shouldn't change
//   translated_vector = translation_matrix * v2_t_disable;
//   EXPECT_FLOAT_EQ(v2_t_disable.x, translated_vector.x);
//   EXPECT_FLOAT_EQ(v2_t_disable.y, translated_vector.y);
//
//   // now it should translate 
//   translated_vector = translation_matrix * v2_t_enable;
//   EXPECT_FLOAT_EQ(v2_t_enable.x + delta_x, translated_vector.x);
//   EXPECT_FLOAT_EQ(v2_t_enable.y + delta_y, translated_vector.y);
//
//}

#endif
