
matrix2D matrix2D::rotate(float angle_in_radians)
{
   float cos_result = cosf(angle_in_radians);
   float sin_result = sinf(angle_in_radians);

   // resulting matrix will look like this:
   //    | cos(angle)  -sin(angle)  0 |
   //    | sin(angle)   cos(angle)  0 |
   //    |     0            0       1 |
   return matrix2D(
      cos_result, (-1) * sin_result,
      sin_result, cos_result);
}

matrix2D matrix2D::translate(float x_delta, float y_delta)
{
   // resulting matrix will look like this:
   //    | 1  0  x_delta |
   //    | 0  1  y_delta |
   //    | 0  0     1    |
   return matrix2D(x_delta, y_delta);
}

matrix2D operator*(const matrix2D& left, const matrix2D& right)
{
   float new_a00 = left.a00 * right.a00 + left.a01*right.a10 + left.a02*right.a20;
   float new_a01 = left.a00 * right.a01 + left.a01*right.a11 + left.a02*right.a21;
   float new_a02 = left.a00 * right.a02 + left.a01*right.a12 + left.a02*right.a22;

   float new_a10 = left.a10 * right.a00 + left.a11*right.a10 + left.a12*right.a20;
   float new_a11 = left.a10 * right.a01 + left.a11*right.a11 + left.a12*right.a21;
   float new_a12 = left.a10 * right.a02 + left.a11*right.a12 + left.a12*right.a22;

   float new_a20 = left.a20 * right.a00 + left.a21*right.a10 + left.a22*right.a20;
   float new_a21 = left.a20 * right.a01 + left.a21*right.a11 + left.a22*right.a21;
   float new_a22 = left.a20 * right.a02 + left.a21*right.a12 + left.a22*right.a22;

   return matrix2D(
      new_a00, new_a01, new_a02,
      new_a10, new_a11, new_a12,
      new_a20, new_a21, new_a22);
}

vector2D operator*(const matrix2D& mat2d, const vector2D& vec2d)
{
   // Expected result:
   // new vector.x =                matrix.a00 * vector.x + matrix.a01 * vector.y + matrix.a02 * vector.enable_translate
   // new vector.y =                matrix.a10 * vector.x + matrix.a11 * vector.y + matrix.a12 * vector.enable_translate
   // new vector.enable_translate = matrix.a20 * vector.x + matrix.a21 * vector.y + matrix.a22 * vector.enable_translate

   return vector2D(
      mat2d.a00 * vec2d.x + mat2d.a01 * vec2d.y + mat2d.a02 * vec2d.enable_translate,
      mat2d.a10 * vec2d.x + mat2d.a11 * vec2d.y + mat2d.a12 * vec2d.enable_translate,
      mat2d.a20 * vec2d.x + mat2d.a21 * vec2d.y + mat2d.a22 * vec2d.enable_translate);
}

