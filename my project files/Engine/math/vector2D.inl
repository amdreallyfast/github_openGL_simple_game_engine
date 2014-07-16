
// the function definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration

float Vector2D::length() const
{
   // the standard library math header is included in the .h file

   // take the square root of the sum of all the squares, not just X and Y
   // Note: Do this because it looks like what you expect out of a Vector with
   // three components.  Also, the only time when w will be non-zero is when 
   // it is a point to be translated, and points are not directional vectors,
   // so it makes no sense to normalize them.  Directional vectors have a w
   // term of 0, w^2 will also be 0 in this case, and all is good.
   return sqrtf((x * x) + (y * y) + (w * w));
}

Vector2D Vector2D::normalize() const
{
   float L = length();
   return Vector2D((x / L), (y / L), (w / L));
}

Vector2D Vector2D::get_cw_perpendicular_vector() const
{
   return Vector2D(y, -x);
}

Vector2D Vector2D::get_ccw_perpendicular_vector() const
{
   return Vector2D(-y, x);
}

float Vector2D::dot(const Vector2D v) const
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

