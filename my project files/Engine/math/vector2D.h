#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

#include <cmath>

namespace Math
{
   // export this to dll because it is a member of the Entity class
   struct __declspec(dllexport) Vector2D
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
      inline float magnitude() const;
      inline float magnitude_squared() const;

      // calculate the dot product of this with another vector
      inline float dot(const Vector2D v) const;

      // construct a unit vector out of this vector
      inline Vector2D normalize() const;

      // projet this vector onto another vector without normalizing it
      inline Vector2D project_onto(const Vector2D& target) const;

      // calculate a vector that is perpendicular to this one
      inline Vector2D get_cw_perpendicular_vector() const;
      inline Vector2D get_ccw_perpendicular_vector() const;

      // define assignment operators inside the class because argument order
      // does matter
      // Note: In these operators, one argument gets modified, and the other 
      // does not, so argument order matters.  
      // Also Note: The return value is a reference rather than a copy because
      // this is an assignment operator, so "this" gets modified.
      inline Vector2D& operator+=(const Vector2D& right);
      inline Vector2D& operator-=(const Vector2D& right);

   private:
   };

   // define these outside the class because argument order does not matter
   // Note: In these operators, the resulting value is temporary and is 
   // subsequently assigned to something else.  The arguments are unaltered, so
   // order does not matter, and I will allow implicit conversion of both 
   // arguments.
   // Also Note: Because the return value is a new and temporary object, return
   // it as a copy, not a reference.
   inline Vector2D operator+(const Vector2D& left, const Vector2D& right);
   inline Vector2D operator-(const Vector2D& left, const Vector2D& right);
   inline Vector2D operator*(float scalar, const Vector2D& vector);
   inline Vector2D operator*(const Vector2D& vector, float scalar);

   inline Vector2D lerp(const Vector2D& source, const Vector2D& dest, float alpha);

   // now include the definitions
#include "Vector2D.inl"
}

#endif // ENGINE_VECTOR_2D_H