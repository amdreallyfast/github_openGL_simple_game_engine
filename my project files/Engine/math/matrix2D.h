#ifndef ENGINE_MATRIX_2D
#define ENGINE_MATRIX_2D

#include "vector2D.h"
//using Math::vector2D;

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
         float start_y0 = 0, float start_y1 = 1);

      // make it a member function to enforce the right-hand-sideness of a vector
      // when you multiply a matrix by a vector
      // Note: You can multiply 2x2 matrix by a 1x2 vector, but not the other way
      // around because of restrictions in matrix mathematics.
      inline vector2D operator*(const vector2D& rhs);
   };

#include "matrix2D.inl"
}

#endif