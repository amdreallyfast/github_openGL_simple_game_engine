#include <gtest\gtest.h>

#include "math\matrix2D.h"
#include "math\vector2D.h"
#include "math\constants.h"
using namespace Math;

#ifdef RUN_MATRIX2D_TESTS

TEST(Matrix2D, Constructor)
{
   // default constructor
   matrix2D identity;

   // row 0
   EXPECT_FLOAT_EQ(1, identity.a00);
   EXPECT_FLOAT_EQ(0, identity.a01);
   EXPECT_FLOAT_EQ(0, identity.a02);

   // row 1
   EXPECT_FLOAT_EQ(0, identity.a10);
   EXPECT_FLOAT_EQ(1, identity.a11);
   EXPECT_FLOAT_EQ(0, identity.a12);

   // row 2
   EXPECT_FLOAT_EQ(0, identity.a20);
   EXPECT_FLOAT_EQ(0, identity.a21);
   EXPECT_FLOAT_EQ(1, identity.a22);



   // now non-default constructor
   // Note: Ordinarily we would not create a matrix this way but would instead
   // summon one through a function like rotate(...) or translate(...), which
   // use private constructors to make a very specific matrix with the 
   // remaining diagonals being 1 and everything else 0, but this is a test 
   // for the constructor so that future tests, such as matrix multiply, can
   // build whatever they want, so we will test all the arguments. 
   matrix2D some_matrix(
      1, 2, 3,
      4, 5, 6,
      7, 8, 9);

   // row 0
   EXPECT_FLOAT_EQ(1, some_matrix.a00);
   EXPECT_FLOAT_EQ(2, some_matrix.a01);
   EXPECT_FLOAT_EQ(3, some_matrix.a02);

   // row 1
   EXPECT_FLOAT_EQ(4, some_matrix.a10);
   EXPECT_FLOAT_EQ(5, some_matrix.a11);
   EXPECT_FLOAT_EQ(6, some_matrix.a12);

   // row 2
   EXPECT_FLOAT_EQ(7, some_matrix.a20);
   EXPECT_FLOAT_EQ(8, some_matrix.a21);
   EXPECT_FLOAT_EQ(9, some_matrix.a22);
}


TEST(Matrix2D, Matrix_Vector_Multiply)
{
   matrix2D linear_transform(
      1, 2, 3,
      4, 5, 6,
      7, 8, 9);

   // implicitly enable translation
   vector2D v1(1, 1);

   // explicitly disable translation
   // Note: In effect, this means the first two rows of the third column are 
   // multiplied by 0 in the addition portion of the multiplication operator.
   vector2D v2(2, 2, 0);

   //vector2D result = v1 * linear_transform;  // won't compile, which is good
   vector2D result;

   // multiply the linear transform by vectors that selectively disable and
   // enable translation and non-orgin rotation

   // got my result from an online matrix calculator:
   // http://www.bluebit.gr/matrix-calculator/matrix_multiplication.aspx

   result = linear_transform * v1;
   EXPECT_FLOAT_EQ(6, result.x);
   EXPECT_FLOAT_EQ(15, result.y);
   EXPECT_FLOAT_EQ(1, result.t);

   result = linear_transform * v2;
   EXPECT_FLOAT_EQ(6, result.x);
   EXPECT_FLOAT_EQ(18, result.y);
   EXPECT_FLOAT_EQ(0, result.t);

}


TEST(Matrix2D, Matrix_Matrix_Multiply)
{
   // again, we would not normally instialize a matrix this way, but this is a
   // controlled test, so we will make controlled matrices and check for a known
   // multiplication result

   matrix2D mat1(
      1, 2, 3,
      4, 5, 6,
      7, 8, 9);
   matrix2D mat2(
      9, 8, 7,
      6, 5, 4,
      3, 2, 1);

   matrix2D result;

   // got my result from an online matrix calculator:
   // http://www.bluebit.gr/matrix-calculator/matrix_multiplication.aspx
   result = mat1 * mat2;
   
   // row 0
   EXPECT_FLOAT_EQ(30, result.a00);
   EXPECT_FLOAT_EQ(24, result.a01);
   EXPECT_FLOAT_EQ(18, result.a02);

   // row 1
   EXPECT_FLOAT_EQ(84, result.a10);
   EXPECT_FLOAT_EQ(69, result.a11);
   EXPECT_FLOAT_EQ(54, result.a12);

   // row 2
   EXPECT_FLOAT_EQ(138, result.a20);
   EXPECT_FLOAT_EQ(114, result.a21);
   EXPECT_FLOAT_EQ(90, result.a22);


   // now multiply in the reverse order
   result = mat2 * mat1;

   EXPECT_FLOAT_EQ(90, result.a00);
   EXPECT_FLOAT_EQ(114, result.a01);
   EXPECT_FLOAT_EQ(138, result.a02);

   // row 1
   EXPECT_FLOAT_EQ(54, result.a10);
   EXPECT_FLOAT_EQ(69, result.a11);
   EXPECT_FLOAT_EQ(84, result.a12);

   // row 2
   EXPECT_FLOAT_EQ(18, result.a20);
   EXPECT_FLOAT_EQ(24, result.a21);
   EXPECT_FLOAT_EQ(30, result.a22);
}


TEST(Matrix2D, Matrix_Rotation_Around_Origin)
{
   matrix2D rotation_matrix;

   const float my_sqrt2_over_2 = SQRT_2 / 2.0f;
   const float my_sqrt3_over_2 = SQRT_3 / 2.0f;
   const float my_1_over_2 = 0.5f;


   // +pi/4 (45 degrees)
   rotation_matrix = matrix2D::rotate(PI / 4);
   
   // row 0
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a00);
   EXPECT_FLOAT_EQ((-1) * my_sqrt2_over_2, rotation_matrix.a01);
   EXPECT_FLOAT_EQ(0, rotation_matrix.a02);

   // row 1
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a10);
   EXPECT_FLOAT_EQ(my_sqrt2_over_2, rotation_matrix.a11);
   EXPECT_FLOAT_EQ(0, rotation_matrix.a12);

   // row 2
   EXPECT_FLOAT_EQ(0, rotation_matrix.a20);
   EXPECT_FLOAT_EQ(0, rotation_matrix.a21);
   EXPECT_FLOAT_EQ(1, rotation_matrix.a22);


   // -pi/3 (45 degrees)
   rotation_matrix = matrix2D::rotate((-1) * PI / 3);
   
   // row 0
   EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.a00);
   EXPECT_FLOAT_EQ((-1) * (-1) * my_sqrt3_over_2, rotation_matrix.a01);
   EXPECT_FLOAT_EQ(0, rotation_matrix.a02);

   // row 1
   EXPECT_FLOAT_EQ((-1) * my_sqrt3_over_2, rotation_matrix.a10);
   EXPECT_FLOAT_EQ(my_1_over_2, rotation_matrix.a11);
   EXPECT_FLOAT_EQ(0, rotation_matrix.a12);

   // row 2
   EXPECT_FLOAT_EQ(0, rotation_matrix.a20);
   EXPECT_FLOAT_EQ(0, rotation_matrix.a21);
   EXPECT_FLOAT_EQ(1, rotation_matrix.a22);

   
   // now try rotating some vectors
   // Note: There is another test for multiplying matrix by vector, so don't 
   // bother checking "enable translate".
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

   // rotate unit vector along y by -60 degrees (- pi/3)
   // Expected x: root(3) / 2
   // Expected y: 1 / 2
   rotation_matrix = matrix2D::rotate((-1) * PI / 3);
   rotated_vector = rotation_matrix * unit_along_y;
   EXPECT_FLOAT_EQ(my_sqrt3_over_2, rotated_vector.x);
   EXPECT_FLOAT_EQ(my_1_over_2, rotated_vector.y);
}


TEST(Matrix2D, Matrix_Rotation_Around_Non_Origin)
{
   const float my_sqrt2_over_2 = SQRT_2 / 2.0f;

   // rotation will be PI / 4

   // make a rotation matrix and a vector, and rotate the vector
   // Note: Don't bother checking the rotation matrix's values because 
   // those were already covered in the "Matrix Rotation Around Origin" test.
   matrix2D rotation_matrix = matrix2D::rotate(PI / 4);
   vector2D some_vector(3, 3);

   // make the displacement vector that will result from a non-origin 
   // rotation point
   // Note: check for both the value and that the "enable translate" is 0,
   // which I would expect from a displacement vector, which is, by
   // nature, a relative vector and therefore should not be translated
   // Also Note: I did the calculation by hand.
   float non_origin_rotation_X = 0.0f;
   float non_origin_rotation_Y = -2.0f;
   vector2D displacement = matrix2D::get_displacement_vector_for_non_origin_rotation(PI / 4, non_origin_rotation_X, non_origin_rotation_Y);
   EXPECT_FLOAT_EQ((-1) * SQRT_2, displacement.x);
   EXPECT_FLOAT_EQ(SQRT_2 - 2, displacement.y);
   EXPECT_FLOAT_EQ(0, displacement.t);

   // rotate the vector, add the displacement, check the values, and check
   // that the "enable translate" value is preserved from "some vector"
   // Note: I did the calculation by hand.
   vector2D result = (rotation_matrix * some_vector) + displacement;
   EXPECT_FLOAT_EQ((-1) * SQRT_2, result.x);
   EXPECT_FLOAT_EQ(6 * my_sqrt2_over_2 + (SQRT_2 - 2), result.y);
   EXPECT_FLOAT_EQ(1, result.t);

}

TEST(Matrix2D, Matrix_Translation)
{
   matrix2D translation_matrix;
   float delta_x;
   float delta_y;


   delta_x = -3;
   delta_y = +3;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // row 0
   EXPECT_FLOAT_EQ(1, translation_matrix.a00);
   EXPECT_FLOAT_EQ(0, translation_matrix.a01);
   EXPECT_FLOAT_EQ(delta_x, translation_matrix.a02);

   // row 1
   EXPECT_FLOAT_EQ(0, translation_matrix.a10);
   EXPECT_FLOAT_EQ(1, translation_matrix.a11);
   EXPECT_FLOAT_EQ(delta_y, translation_matrix.a12);

   // row 2
   EXPECT_FLOAT_EQ(0, translation_matrix.a20);
   EXPECT_FLOAT_EQ(0, translation_matrix.a21);
   EXPECT_FLOAT_EQ(1, translation_matrix.a22);


   delta_x = +2;
   delta_y = -19;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // row 0
   EXPECT_FLOAT_EQ(1, translation_matrix.a00);
   EXPECT_FLOAT_EQ(0, translation_matrix.a01);
   EXPECT_FLOAT_EQ(delta_x, translation_matrix.a02);

   // row 1
   EXPECT_FLOAT_EQ(0, translation_matrix.a10);
   EXPECT_FLOAT_EQ(1, translation_matrix.a11);
   EXPECT_FLOAT_EQ(delta_y, translation_matrix.a12);

   // row 2
   EXPECT_FLOAT_EQ(0, translation_matrix.a20);
   EXPECT_FLOAT_EQ(0, translation_matrix.a21);
   EXPECT_FLOAT_EQ(1, translation_matrix.a22);


   // now try translating some vectors
   vector2D v_t_disable(2, 2, 0);     // translation disabled
   vector2D v_t_enable(2, 2);      // translation enabled
   vector2D translated_vector;

   delta_x = +4;
   delta_y = -5;
   translation_matrix = matrix2D::translate(delta_x, delta_y);

   // shouldn't change
   translated_vector = translation_matrix * v_t_disable;
   EXPECT_FLOAT_EQ(v_t_disable.x, translated_vector.x);
   EXPECT_FLOAT_EQ(v_t_disable.y, translated_vector.y);

   // now it should translate 
   translated_vector = translation_matrix * v_t_enable;
   EXPECT_FLOAT_EQ(v_t_enable.x + delta_x, translated_vector.x);
   EXPECT_FLOAT_EQ(v_t_enable.y + delta_y, translated_vector.y);
}

#endif
