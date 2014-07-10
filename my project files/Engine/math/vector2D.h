#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

#include <cmath>

namespace Math
{
   struct Vector2D
   {
      // the X value
      float x;

      // the Y value
      float y;

      // the value that, if non-zero, enables translation 
      // Note: Called "w" out of tradition.  I would call it "t" because it 
      // is associated with translation, but graphic programming tradition 
      // says that it is "w", so I'll go with the flow.
      // Also Note: It is not required to be exactly 1 or exactly 0, because 
      // it has some use with other values, particularly in 3D graphics with
      // the "perspective matrix".  Ordinarily, point vectors are translatable
      // and have a "w" value of 1, while direction vectors are not translatable
      // and have a "w" value of 0.  A point will not be added to a point, but
      // a direction vector may be added to a point, or a direction vector to
      // another direction vector, so the "w" value should always be exactly 
      // 1 or exactly 0 except for special circumstances.
      float w;

      // the first and second values can be any floats, but the last, the 
      // "enable translate" value, should only be 0 or 1
      // Note: If it is not between 0.99 and 1.01, then it will set to 0.
      // But if it is not specified, then it will default to 1 (translation
      // is enabled) because I decided that my default desire for vertices 
      // was that they be allowed to translate.
      explicit Vector2D(
         float start_x = 0.0f,
         float start_y = 0.0f,
         float start_w = 0.0f) :
         x(start_x),
         y(start_y),
         w(start_w)
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
      inline Vector2D& operator+=(const Vector2D& rhs);
      inline Vector2D& operator-=(const Vector2D& rhs);

   private:
   };

   // define these outside the class because argument order does not matter
   // Note: In these operators, the resulting value is temporary and is 
   // subsequently assigned to something else.  The arguments are unaltered, so
   // order does not matter, and I will allow implicit conversion of both 
   // arguments.
   // Also Note: Because the return value is a new and temporary object, return
   // it as a copy, not a reference.
   inline Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
   inline Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
   inline Vector2D operator*(float scalar, const Vector2D& vector);
   inline Vector2D operator*(const Vector2D& vector, float scalar);

   // now include the definitions
#include "Vector2D.inl"
}

#endif // ENGINE_VECTOR_2D_H