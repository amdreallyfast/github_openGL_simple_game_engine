
// the function definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration

float Vector2D::length()
{
   // "math.h" is included in the header file

   // the "enable translate" is meant for translation only and is not a 
   // part of the (x, y) dimension, so don't take it into account
   return sqrtf(powf(x, 2.0f) + powf(y, 2.0f));
}

Vector2D Vector2D::get_cw_perpendicular_vector()
{
   return Vector2D(y, -x);
}

Vector2D Vector2D::get_ccw_perpendicular_vector()
{
   return Vector2D(-y, x);
}

float Vector2D::dot(const Vector2D v)
{
   return ((x * v.x) + (y * v.y) + (w * v.w));
}


// Concerning Operators:
// If either of the source vectors have a flag enabled, enable it for the 
// result vector, and only disable the result vector's flags if both 
// source vectors' flags are 0.

// In-class operators
Vector2D& Vector2D::operator += (const Vector2D& right)
{
   x += right.x;
   y += right.y;
   w += right.w;

   return *this;
}

Vector2D& Vector2D::operator -= (const Vector2D& right)
{
   x -= right.x;
   y -= right.y;
   w -= right.w;

   return *this;
}


// Out-of-class operators
Vector2D operator+(const Vector2D& left, const Vector2D& right)
{
   return Vector2D(
      left.x + right.x,
      left.y + right.y,
      left.w + right.w);
}

Vector2D operator-(const Vector2D& left, const Vector2D& right)
{
   return Vector2D(
      left.x - right.x,
      left.y - right.y,
      left.w - right.w);
}

Vector2D operator*(float scalar, const Vector2D& vector)
{
   return Vector2D(
      scalar * vector.x,
      scalar * vector.y,
      scalar * vector.w);
}

Vector2D operator*(const Vector2D& vector, float scalar)
{
   // preserve "enable translate" value
   return Vector2D(
      vector.x * scalar,
      vector.y * scalar,
      vector.w * scalar);
}

