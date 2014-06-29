#ifndef ENGINE_MATRIX_2D
#define ENGINE_MATRIX_2D

// ??why don't I need to state, "using Math::vector2D"? is it because I am already working in the same namespace??
#include "vector2D.h"

// for trig functons
#include <cmath>

namespace Math
{
   // make it a struct for the convenience of everything being default public

   struct matrix2D
   {
      float a00, a01, a02;
      float a10, a11, a12;
      float a20, a21, a22;

      // declare constructors explicit so that we do not have any implicit conversions
      // from and argument type like "float" to "matrix2D"

      explicit matrix2D(
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
      inline static matrix2D rotate(float angle_in_radians);

      inline static vector2D get_displacement_vector_for_non_origin_rotation(float angle_in_radians, const vector2D& pivot);

      // similarly, translation is very specific to the matrix itself, so make it
      // a static member
      inline static matrix2D translate(float x_delta, float y_delta);
   };

   // when performthing this multiplication, leave the source matrix and vector 
   // unchanged and return a new vector
   inline vector2D operator*(const matrix2D& mat2d, const vector2D& vec2d);

   // do not alter the source matrices, and instead return a new one
   inline matrix2D operator*(const matrix2D& left, const matrix2D& right);

#include "matrix2D.inl"
}

#endif