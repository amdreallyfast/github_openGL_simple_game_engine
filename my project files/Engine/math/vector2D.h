#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

#include <cmath>

namespace Math
{
   struct vector2D
   {
      float x;
      float y;

      // you don't always want to be able to translate a vector, such as if it
      // is a vector from the origin to a reference point, like a non-origin 
      // rotation point
      float enable_translate;

      // similarly, you may not want a vector to be allowed to rotate around a
      // non-origin axis
      float enable_non_origin_rotation;

      // make the default constructor yourself because the compiler seems unable
      // to make one
      // Note: Default values are all 0 (zero).
      explicit vector2D() :
         x(0),
         y(0),
         enable_translate(0),
         enable_non_origin_rotation(0)
      {
      }

      // make constructor explicit so that the compiler won't try to implicitly
      // take two adjacent floats in a "verts" array and make a vector out of 
      // them
      // Note: The constructor must be defined here because it is neither 
      // inline nor defined in a separate compilation unit.
      explicit vector2D(
         float start_x, 
         float start_y,
         bool start_enable_translate = false,
         bool start_enable_non_origin_rotation = false) :
         x(start_x),
         y(start_y),
         enable_translate(start_enable_translate ? 1.0f : 0.0f),
         enable_non_origin_rotation(start_enable_non_origin_rotation ? 1.0f : 0.0f)
      {
      }

      // calculate the magnitude of this vector
      float inline length();

      // define assignment operators inside the class because argument order
      // does matter
      // Note: In these operators, one argument gets modified, and the other 
      // does not, so argument order matters.  
      // Also Note: The return value is a reference rather than a copy because
      // this is an assignment operator, so "this" gets modified.
      inline vector2D& operator+=(const vector2D& rhs);
      inline vector2D& operator-=(const vector2D& rhs);

   private:
   };

   // define these outside the class because argument order does not matter
   // Note: In these operators, the resulting value is temporary and is 
   // subsequently assigned to something else.  The arguments are unaltered, so
   // order does not matter, and I will allow implicit conversion of both 
   // arguments.
   // Also Note: Because the return value is a new and temporary object, return
   // it as a copy, not a reference.
   inline vector2D operator+(const vector2D& lhs, const vector2D& rhs);
   inline vector2D operator-(const vector2D& lhs, const vector2D& rhs);
   inline vector2D operator*(float scalar, const vector2D& vector);
   inline vector2D operator*(const vector2D& vector, float scalar);

   // now include the definitions
#include "vector2D.inl"
}

#endif // ENGINE_VECTOR_2D_H