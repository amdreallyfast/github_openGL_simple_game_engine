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
      float a00, a01, a02, a03;
      float a10, a11, a12, a13;
      float a20, a21, a22, a23;
      float a30, a31, a32, a33;

      // declare constructors explicit so that we do not have any implicit conversions
      // from and argument type like "float" to "matrix2D"

      // this constructor makes an identity matrix, which is intended for testing
      // only (it is used to create a "dud" matrix" to stub out various functions),
      // but someone could still use it if they wanted an identity matrix
      explicit matrix2D() :
         a00(1), a01(0), a02(0), a03(0),
         a10(0), a11(1), a12(0), a13(0),
         a20(0), a21(0), a22(1), a23(0),
         a30(0), a31(0), a32(0), a33(1)
      {
      }

      // this matrix is intended for testing matrix-matrix and matrix-vector 
      // operations, but it has no other use
      explicit matrix2D(
         float start_a00, float start_a01, float start_a02, float start_a03,
         float start_a10, float start_a11, float start_a12, float start_a13,
         float start_a20, float start_a21, float start_a22, float start_a23,
         float start_a30, float start_a31, float start_a32, float start_a33) :
         a00(start_a00), a01(start_a01), a02(start_a02), a03(start_a03),
         a10(start_a10), a11(start_a11), a12(start_a12), a13(start_a13),
         a20(start_a20), a21(start_a21), a22(start_a22), a23(start_a23),
         a30(start_a30), a31(start_a31), a32(start_a32), a33(start_a33)
      {
      }

      // the rotation is very specific to the matrix itself, so make it a member,
      // and make it a static factory that will create a matrix that can be
      // applied to a vector to rotate it
      inline static matrix2D rotate(
         float angle_in_radians, 
         float pivot_x = 0, 
         float pivot_y = 0);

      // similarly, translation is very specific to the matrix itself, so make it
      // a static member
      inline static matrix2D translate(float x_delta, float y_delta);

   private:
      // make constructors explicitly for rotation and translation
      // Note: Make them private because they are to be used exclusively internally.
      
      // rotation constructor
      // Note: No default arguments.  Everything must be provided.
      explicit matrix2D(
         float rotate_x0, float rotate_x1, float displacement_x,
         float rotate_y0, float rotate_y1, float displacement_y) //:
         //a00(rotate_x0), a01(rotate_x1), a02(0), a03(displacement_x),
         //a10(rotate_y0), a11(rotate_y1), a12(0), a13(displacement_y),
         //a20(0), a21(0), a22(1), a23(0),
         //a30(0), a31(0), a32(0), a33(1)
      {
      }

      // translate constructor
      // Note: No default arguments.  Everything must be provided.
      explicit matrix2D(float x_delta, float y_delta) //:
         //a00(1), a01(0), a02(x_delta), a03(0),
         //a10(0), a11(1), a12(y_delta), a13(0),
         //a20(0), a21(0), a22(1), a23(0),
         //a30(0), a31(0), a32(0), a33(1)
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