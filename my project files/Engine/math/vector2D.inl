
// the function definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration

float vector2D::length()
{
   // "math.h" is included in the header file

   // the "enable translate" is meant for translation only and is not a 
   // part of the (x, y) dimension, so don't take it into account
   return sqrtf(powf(x, 2.0f) + powf(y, 2.0f));
}


// Concerning Operators:
// If either of the source vectors have a flag enabled, enable it for the 
// result vector, and only disable the result vector's flags if both 
// source vectors' flags are 0.

// In-class operators
vector2D& vector2D::operator += (const vector2D& rhs)
{
   x += rhs.x;
   y += rhs.y;
   w += rhs.w;

   return *this;
}

vector2D& vector2D::operator -= (const vector2D& rhs)
{
   x -= rhs.x;
   y -= rhs.y;
   w -= rhs.w;

   return *this;
}


// Out-of-class operators
vector2D operator+(const vector2D& lhs, const vector2D& rhs)
{
   return vector2D(
      lhs.x + rhs.x,
      lhs.y + rhs.y,
      lhs.w + rhs.w);
}

vector2D operator-(const vector2D& lhs, const vector2D& rhs)
{
   return vector2D(
      lhs.x - rhs.x,
      lhs.y - rhs.y,
      lhs.w - rhs.w);
}

vector2D operator*(float scalar, const vector2D& vector)
{
   return vector2D(
      scalar * vector.x,
      scalar * vector.y,
      scalar * vector.w);
}

vector2D operator*(const vector2D& vector, float scalar)
{
   // preserve "enable translate" value
   return vector2D(
      vector.x * scalar,
      vector.y * scalar,
      vector.w * scalar);
}

