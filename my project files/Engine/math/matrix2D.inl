
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
   float new_row0_col0 = left.row0_col0 * right.row0_col0 + left.row0_col1*right.row1_col0 + left.row0_col2*right.row2_col0;
   float new_row0_col1 = left.row0_col0 * right.row0_col1 + left.row0_col1*right.row1_col1 + left.row0_col2*right.row2_col1;
   float new_row0_col2 = left.row0_col0 * right.row0_col2 + left.row0_col1*right.row1_col2 + left.row0_col2*right.row2_col2;

   float new_row1_col0 = left.row1_col0 * right.row0_col0 + left.row1_col1*right.row1_col0 + left.row1_col2*right.row2_col0;
   float new_row1_col1 = left.row1_col0 * right.row0_col1 + left.row1_col1*right.row1_col1 + left.row1_col2*right.row2_col1;
   float new_row1_col2 = left.row1_col0 * right.row0_col2 + left.row1_col1*right.row1_col2 + left.row1_col2*right.row2_col2;

   float new_row2_col0 = left.row2_col0 * right.row0_col0 + left.row2_col1*right.row1_col0 + left.row2_col2*right.row2_col0;
   float new_row2_col1 = left.row2_col0 * right.row0_col1 + left.row2_col1*right.row1_col1 + left.row2_col2*right.row2_col1;
   float new_row2_col2 = left.row2_col0 * right.row0_col2 + left.row2_col1*right.row1_col2 + left.row2_col2*right.row2_col2;

   return matrix2D(
      new_row0_col0, new_row0_col1, new_row0_col2,
      new_row1_col0, new_row1_col1, new_row1_col2,
      new_row2_col0, new_row2_col1, new_row2_col2);
}

vector2D operator*(const matrix2D& mat2d, const vector2D& vec2d)
{
   // Expected result:
   // new vector.x =                matrix.row0_col0 * vector.x + matrix.row0_col1 * vector.y + matrix.row0_col2 * vector.enable_translate
   // new vector.y =                matrix.row1_col0 * vector.x + matrix.row1_col1 * vector.y + matrix.row1_col2 * vector.enable_translate
   // new vector.enable_translate = matrix.row2_col0 * vector.x + matrix.row2_col1 * vector.y + matrix.row2_col2 * vector.enable_translate

   return vector2D(
      mat2d.row0_col0 * vec2d.x + mat2d.row0_col1 * vec2d.y + mat2d.row0_col2 * vec2d.enable_translate,
      mat2d.row1_col0 * vec2d.x + mat2d.row1_col1 * vec2d.y + mat2d.row1_col2 * vec2d.enable_translate,
      mat2d.row2_col0 * vec2d.x + mat2d.row2_col1 * vec2d.y + mat2d.row2_col2 * vec2d.enable_translate);
}

