#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

namespace MATH
{
   struct vector2D
   {
      float x;
      float y;

      // ??force to explicit??
      vector2D(float new_x = 0.0f, float new_y = 0.0f) : 
         x(new_x),
         y(new_y)
      { }


   };

   // operator overloading
   // Note: Do NOT make the return values const.  The user must be able to modify
   // the vector after it has been computed.
   //??why doesn't making it const prevent the return value from being modified??

   vector2D operator+(const vector2D& lhs, const vector2D& rhs)
   {
      return vector2D();
   }

   // scalar multiplication (both orders)
   vector2D operator*(float scalar, const vector2D& rhs)
   {
      return vector2D();
   }

   vector2D operator*(const vector2D& rhs, float scalar)
   {
      return vector2D();
   }
}

#endif // ENGINE_VECTOR_2D_H