
matrix2D::matrix2D(
   float start_x0, float start_x1,
   float start_y0, float start_y1)
   :
   x0(start_x0), x1(start_x1),
   y0(start_y0), y1(start_y1)
{
}

inline vector2D operator*(const matrix2D& mat2, const vector2D& vec2)
{
   // Expected result:
   // matrix.x0 * vector.x + matrix.x1 * vector.y = new vector.x
   // matrix.y0 * vector.x + matrix.y1 * vector.y = new vector.y

   return vector2D(
      mat2.x0 * vec2.x + mat2.x1 * vec2.y,
      mat2.y0 * vec2.x + mat2.y1 * vec2.y);
}
