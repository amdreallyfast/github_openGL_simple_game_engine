
matrix2D::matrix2D(
   float start_x0, float start_x1,
   float start_y0, float start_y1)
   :
   x0(start_x0), x1(start_x1),
   y0(start_y0), y1(start_y1)
{
}

// make it a member function to enforce the right-hand-sideness of a vector
// when you multiply a matrix by a vector
vector2D matrix2D::operator*(const vector2D& vec)
{
   // Expected result:
   // matrix.x0 * vector.x + matrix.x1 * vector.y = new vector.x
   // matrix.y0 * vector.x + matrix.y1 * vector.y = new vector.y

   return vector2D(
      this->x0 * vec.x + this->x1 * vec.y,
      this->y0 * vec.x + this->y1 * vec.y);
}
