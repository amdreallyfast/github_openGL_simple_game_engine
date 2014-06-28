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
      float row0_col0, row0_col1, row0_col2;
      float row1_col0, row1_col1, row1_col2;
      float row2_col0, row2_col1, row2_col2;

      // declare constructors explicit so that we do not have any implicit conversions
      // from and argument type like "float" to "matrix2D"

      // this constructor makes an identity matrix
      explicit matrix2D() :
         row0_col0(1), row0_col1(0), row0_col2(0),
         row1_col0(0), row1_col1(1), row1_col2(0),
         row2_col0(0), row2_col1(0), row2_col2(1)
      {
      }

      // this matrix is intended for testing so that any desired matrix can be
      // constructed, but it could be used by the adventerous type who wants to
      // build the matrix themselves
      // Note: There are no default values so that it does not conflict with the
      // no-argument constructor.
      explicit matrix2D(
         float start_row0_col0, float start_row0_col1, float start_row0_col2,
         float start_row1_col0, float start_row1_col1, float start_row1_col2,
         float start_row2_col0, float start_row2_col1, float start_row2_col2) :
         row0_col0(start_row0_col0), row0_col1(start_row0_col1), row0_col2(start_row0_col2),
         row1_col0(start_row1_col0), row1_col1(start_row1_col1), row1_col2(start_row1_col2),
         row2_col0(start_row2_col0), row2_col1(start_row2_col1), row2_col2(start_row2_col2)
      {
      }

      // the rotation is very specific to the matrix itself, so make it a member,
      // and make it a static factory that will create a matrix that can be
      // applied to a vector to rotate it
      inline static matrix2D rotate(float angle_in_radians);

      // similarly, translation is very specific to the matrix itself, so make it
      // a static member
      inline static matrix2D translate(float x_delta, float y_delta);

   private:
      // make constructors explicitly for rotation and translation
      // Note: Make them private because they are to be used exclusively internally.
      
      // rotation constructor
      // Note: No default arguments.  Everything must be provided.
      explicit matrix2D(
         float rotate_x0, float rotate_x1,
         float rotate_y0, float rotate_y1) :
         row0_col0(rotate_x0), row0_col1(rotate_x1), row0_col2(0),
         row1_col0(rotate_y0), row1_col1(rotate_y1), row1_col2(0),
         row2_col0(0), row2_col1(0), row2_col2(1)
      {
      }

      // translate constructor
      // Note: No default arguments.  Everything must be provided.
      explicit matrix2D(float row0_col2, float row1_col2) :
         row0_col0(1), row0_col1(0), row0_col2(row0_col2),
         row1_col0(0), row1_col1(1), row1_col2(row1_col2),
         row2_col0(0), row2_col1(0), row2_col2(1)
      {
      }
   };

   // when performthing this multiplication, leave the source matrix and vector 
   // unchanged and return a new vector
   inline vector2D operator*(const matrix2D& mat2d, const vector2D& vec2d);

   // do not alter the source matrices, and instead return a new one
   inline matrix2D operator*(const matrix2D& left, const matrix2D& right);

#include "matrix2D.inl"
}

#endif