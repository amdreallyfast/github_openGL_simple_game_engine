#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

namespace MATH
{
   struct vector2D
   {
      float x;
      float y;

      // let the default copy constructors be made by the compiler
      // Note: This is a simple structure, and the operators call the copy 
      // constructor when returning a new object, so the default copy
      // constructor is enough.

      vector2D(float new_x = 0.0f, float new_y = 0.0f) : 
         x(new_x),
         y(new_y)
      { }

   private:
   };

   inline vector2D operator+(const vector2D& lhs, const vector2D& rhs);
   inline vector2D operator*(float scalar, const vector2D& vector);
   inline vector2D operator*(const vector2D& vector, float scalar);

   // now include the inline definitions
#include "vector2D.inl"
}

#endif // ENGINE_VECTOR_2D_H