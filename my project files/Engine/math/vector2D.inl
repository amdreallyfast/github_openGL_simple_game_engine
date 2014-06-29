
// the function definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration

float vector2D::length()
{
   // "math.h" is included in the header file

   // the "enable translate" is meant for translation only and is not a 
   // part of the (x, y) dimension stuff, so don't take it into account
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

   if (1 == rhs.enable_translate || 1 == this->enable_translate)
   {
      enable_translate = 1;
   }

   if (1 == rhs.enable_non_origin_rotation || 1 == this->enable_non_origin_rotation)
   {
      enable_non_origin_rotation = 1;
   }

   return *this;
}

vector2D& vector2D::operator -= (const vector2D& rhs)
{
   x -= rhs.x;
   y -= rhs.y;

   if (1 == rhs.enable_translate || 1 == this->enable_translate)
   {
      enable_translate = 1;
   }

   if (1 == rhs.enable_non_origin_rotation || 1 == this->enable_non_origin_rotation)
   {
      enable_non_origin_rotation = 1;
   }

   return *this;
}


// Out-of-class operators
vector2D operator+(const vector2D& lhs, const vector2D& rhs)
{
   return vector2D(
      lhs.x + rhs.x, 
      lhs.y + rhs.y,
      (1 == lhs.enable_translate || 1 == rhs.enable_translate) ? true : false,
      (1 == lhs.enable_non_origin_rotation || 1 == rhs.enable_non_origin_rotation) ? true : false);
}

vector2D operator-(const vector2D& lhs, const vector2D& rhs)
{
   return vector2D(
      lhs.x - rhs.x,
      lhs.y - rhs.y,
      (1 == lhs.enable_translate || 1 == rhs.enable_translate) ? true : false,
      (1 == lhs.enable_non_origin_rotation || 1 == rhs.enable_non_origin_rotation) ? true : false);
}

vector2D operator*(float scalar, const vector2D& vector)
{
   return vector2D(
      scalar * vector.x, 
      scalar * vector.y,
      (1 == vector.enable_translate) ? true : false,
      (1 == vector.enable_non_origin_rotation) ? true : false);
}

vector2D operator*(const vector2D& vector, float scalar)
{
   return vector2D(
      vector.x * scalar,
      vector.y * scalar,
      (1 == vector.enable_translate) ? true : false,
      (1 == vector.enable_non_origin_rotation) ? true : false);
}

