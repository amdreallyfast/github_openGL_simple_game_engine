

// the operator definitions here do not require the "inline" keyword because
// they were already declared as "inline" in their declaration

vector2D operator+(const vector2D& lhs, const vector2D& rhs)
{
   // should break the test
   //return vector2D();

   // should make the test pass
   return vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

vector2D operator*(float scalar, const vector2D& vector)
{
   // should break the test
   //return vector2D();

   // should make the test pass
   return vector2D(scalar * vector.x, scalar * vector.y);
}

vector2D operator*(const vector2D& vector, float scalar)
{
   // should break the test
   //return vector2D();

   // should make the test pass
   return vector2D(vector.x * scalar, vector.y * scalar);
}
