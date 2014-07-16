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
      float x0, x1, x2;
      float y0, y1, y2;
      float w0, w1, w2;

      // declare constructors explicit so that we do not have any implicit conversions
      // from and argument type like "float" to "Matrix2D"

      explicit Matrix2D(
         float start_x0 = 1.0f, float start_x1 = 0.0f, float start_x2 = 0.0f,
         float start_y0 = 0.0f, float start_y1 = 1.0f, float start_y2 = 0.0f,
         float start_w0 = 0.0f, float start_w1 = 0.0f, float start_w2 = 1.0f) :
         x0(start_x0), x1(start_x1), x2(start_x2),
         y0(start_y0), y1(start_y1), y2(start_y2),
         w0(start_w0), w1(start_w1), w2(start_w2)
      {
      }

      // make the matrix factories member functions
      inline static Matrix2D rotate(float angle_in_radians);
      inline static Matrix2D translate(float x_delta, float y_delta);
      inline static Matrix2D scale(float scale_x, float scale_y);

      inline static Vector2D get_displacement_vector_for_non_origin_rotation(float angle_in_radians, const Vector2D& pivot);



   };

   // when performthing this multiplication, leave the source matrix and vector 
   // unchanged and return a new vector
   inline Vector2D operator*(const Matrix2D& mat2d, const Vector2D& vec2d);

   // do not alter the source matrices, and instead return a new one
   inline Matrix2D operator*(const Matrix2D& left, const Matrix2D& right);

#include "Matrix2D.inl"
}

#endif