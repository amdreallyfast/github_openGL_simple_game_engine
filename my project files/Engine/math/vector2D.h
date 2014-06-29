#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

#include <cmath>

namespace Math
{
   struct vector2D
   {
      // the X value
      float x;

      // the Y value
      float y;

      // the "enable translate" value, and should be 1 or 0 only
      float t;

      // the first and second values can be any floats, but the last, the 
      // "enable translate" value, should only be 0 or 1
      // Note: If it is not between 0.99 and 1.01, then it will set to 0.
      // But if it is not specified, then it will default to 1 (translation
      // is enabled) because I decided that my default desire for vertices 
      // was that they be allowed to translate.
      explicit vector2D(
         float start_x = 0.0f,
         float start_y = 0.0f,
         float start_t = 1.0f) :
         x(start_x),
         y(start_y),
         t((1.0f == start_t) ? 1.0f : 0.0f)
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