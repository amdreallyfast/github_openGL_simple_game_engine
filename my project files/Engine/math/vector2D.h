#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

namespace Math
{
   struct vector2D
   {
      float x;
      float y;

      // let the default copy constructors be made by the compiler
      // Note: This is a simple structure, and the operators call the copy 
      // constructor when returning a new object, so the default copy
      // constructor is enough.

      // make constructor explicit so that the compiler won't try to implicitly
      // take two ajacent floats in a "verts" array and make a vector out of 
      // them
      // Note: This is normal C++ behavior and can be useful, but make the 
      // constructor explicit for the sake of forcing readable code.
      explicit vector2D(float new_x = 0.0f, float new_y = 0.0f) : 
         x(new_x),
         y(new_y)
      { }

      vector2D(const vector2D& source) :
         x(source.x),
         y(source.y)
      { }

      // define assignment operators inside the class because argument order
      // does matter
      // Note: In these operators, one argument gets modified, and the other 
      // does not, so argument order matters, and I do not want to allow 
      // implicit conversion of the left-hand side argument.  
      // Also Note: I also don't want to allow implicit conversion of the left-
      // hand side because the left-hand side is supposed to be "this".  And 
      // for that reason, the return value is a reference rather than a copy.
      inline vector2D& operator=(const vector2D& rhs);
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

   // now include the inline definitions
#include "vector2D.inl"
}

#endif // ENGINE_VECTOR_2D_H