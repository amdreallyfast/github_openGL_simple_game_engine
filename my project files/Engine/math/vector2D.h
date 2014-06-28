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

      // let the default copy constructors be made by the compiler
      // Note: This is a simple structure, and the operators call the copy 
      // constructor when returning a new object, so the default copy
      // constructor is enough.

      // make constructor explicit so that the compiler won't try to implicitly
      // take two adjacent floats in a "verts" array and make a vector out of 
      // them
      // Note: This implicitness is normal C++ behavior and can be useful, but 
      // make the constructor explicit for the sake of forcing readable code.
      // Also Note: The constructor must be defined here because it is neither 
      // inline nor defined in a separate compilation unit.
      explicit vector2D(
         float start_x = 0, 
         float start_y = 0,
         float start_enable_translate = 0) :
         x(start_x),
         y(start_y),
         enable_translate(start_enable_translate)
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