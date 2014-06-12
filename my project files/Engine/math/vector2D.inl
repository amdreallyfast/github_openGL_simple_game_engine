

// the operator definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration


// In-class operators
vector2D& vector2D::operator = (const vector2D& rhs)
{
   x = rhs.x;
   y = rhs.y;

   return *this;
}

vector2D& vector2D::operator += (const vector2D& rhs)
{
   x += rhs.x;
   y += rhs.y;

   return *this;
}

vector2D& vector2D::operator -= (const vector2D& rhs)
{
   x -= rhs.x;
   y -= rhs.y;

   return *this;
}


// Out-of-class operators
vector2D operator+(const vector2D& lhs, const vector2D& rhs)
{
   // should break the test
   //return vector2D();

   // should make the test pass
   return vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

vector2D operator-(const vector2D& lhs, const vector2D& rhs)
{
   return vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

vector2D operator*(float scalar, const vector2D& vector)
{
   return vector2D(scalar * vector.x, scalar * vector.y);
}

vector2D operator*(const vector2D& vector, float scalar)
{
   return vector2D(vector.x * scalar, vector.y * scalar);
}

