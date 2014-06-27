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
      float x0, x1;  // row 0, column 0 and 1
      float y0, y1;  // row 1, column 0 and 1

      // declare constructor explicit so that we do not have any implicit conversions
      // from "float" to "matrix2D"
      // Note: Default matrix is a 2x2 identity matrix.
      explicit matrix2D(
         float start_x0 = 1, float start_x1 = 0,
         float start_y0 = 0, float start_y1 = 1) :
         x0(start_x0), x1(start_x1),
         y0(start_y0), y1(start_y1)
      {
      }

      // the rotation is very specific to the matrix itself, so make it a member,
      // and make it a static factory that will create a matrix that can be
      // applied to a vector to rotate it
      inline static matrix2D rotate(float angle_in_radians);
   };

   // when performthing this multiplication, leave the source vector unchanged and 
   // return a new vector
   inline vector2D operator*(const matrix2D& mat2, const vector2D& vec2);

#include "matrix2D.inl"
}

#endif