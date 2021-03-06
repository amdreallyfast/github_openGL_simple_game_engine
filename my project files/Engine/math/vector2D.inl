
// the function definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration

float Vector2D::magnitude() const
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

float Vector2D::magnitude_squared() const
{
   // this function is useful as a computationally cheap way of comparing the
   // magnitudes of two vectors to see which is greater
   float f = this->dot(*this);
   return f;
}

float Vector2D::dot(const Vector2D v) const
{
   return ((x * v.x) + (y * v.y) + (w * v.w));
}

Vector2D Vector2D::normalize() const
{
   float scalar = 1 / magnitude();

   // make a copy of this vector and scale it by the inverse of the magnitude
   return scalar * (*this);
}

Vector2D Vector2D::project_onto(const Vector2D& target) const
{
   return (this->dot(target) / target.magnitude_squared()) * target;
}

Vector2D Vector2D::get_cw_perpendicular_vector() const
{
   return Vector2D(y, -x);
}

Vector2D Vector2D::get_ccw_perpendicular_vector() const
{
   return Vector2D(-y, x);
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

Vector2D lerp(const Vector2D& source, const Vector2D& dest, float alpha)
{
   return (1.0f - alpha) * source + (alpha * dest);
}


