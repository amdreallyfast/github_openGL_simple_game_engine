#ifndef ENGINE_MATRIX_2D
#define ENGINE_MATRIX_2D

// ??why don't I need to state, "using Math::Vector2D"? is it because I am already working in the same namespace??
#include "Vector2D.h"

// for trig functons
#include <cmath>

namespace Math
{
   // make it a struct for the convenience of everything being default public

   struct Matrix2D
   {
      float a00, a01, a02;
      float a10, a11, a12;
      float a20, a21, a22;

      // declare constructors explicit so that we do not have any implicit conversions
      // from and argument type like "float" to "Matrix2D"

      explicit Matrix2D(
         float start_a00 = 1.0f, float start_a01 = 0.0f, float start_a02 = 0.0f,
         float start_a10 = 0.0f, float start_a11 = 1.0f, float start_a12 = 0.0f,
         float start_a20 = 0.0f, float start_a21 = 0.0f, float start_a22 = 1.0f) :
         a00(start_a00), a01(start_a01), a02(start_a02),
         a10(start_a10), a11(start_a11), a12(start_a12),
         a20(start_a20), a21(start_a21), a22(start_a22)
      {
      }

      // the rotation is very specific to the matrix itself, so make it a member,
      // and make it a static factory that will create a matrix that can be
      // applied to a vector to rotate it
      inline static Matrix2D rotate(float angle_in_radians);

      inline static Vector2D get_displacement_vector_for_non_origin_rotation(float angle_in_radians, const Vector2D& pivot);

      // similarly, translation is very specific to the matrix itself, so make it
      // a static member
      inline static Matrix2D translate(float x_delta, float y_delta);
   };

   // when performthing this multiplication, leave the source matrix and vector 
   // unchanged and return a new vector
   inline Vector2D operator*(const Matrix2D& mat2d, const Vector2D& vec2d);

   // do not alter the source matrices, and instead return a new one
   inline Matrix2D operator*(const Matrix2D& left, const Matrix2D& right);

#include "Matrix2D.inl"
}

#endif