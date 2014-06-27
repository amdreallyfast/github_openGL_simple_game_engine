
inline vector2D operator*(const matrix2D& mat2, const vector2D& vec2)
{
   // Expected result:
   // matrix.x0 * vector.x + matrix.x1 * vector.y = new vector.x
   // matrix.y0 * vector.x + matrix.y1 * vector.y = new vector.y

   return vector2D(
      mat2.x0 * vec2.x + mat2.x1 * vec2.y,
      mat2.y0 * vec2.x + mat2.y1 * vec2.y);
}

matrix2D matrix2D::rotate(float angle_in_radians)
{
   float cos_result = cosf(angle_in_radians);
   float sin_result = sinf(angle_in_radians);
   return matrix2D(
      cos_result, (-1) * sin_result,
      sin_result, cos_result);
}
