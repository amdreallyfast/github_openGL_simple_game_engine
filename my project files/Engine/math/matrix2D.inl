
matrix2D::matrix2D(
   float start_x0, float start_x1,
   float start_y0, float start_y1)
   //:
   //x0(start_x0), x1(start_x1),
   //y0(start_y0), y1(start_y1)
{
}

// make it a member function to enforce the right-hand-sideness of a vector
// when you multiply a matrix by a vector
vector2D matrix2D::operator*(const vector2D& rhs)
{
   return vector2D();
}
