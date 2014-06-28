
matrix2D matrix2D::rotate(float angle_in_radians)
{
   float cos_result = cosf(angle_in_radians);
   float sin_result = sinf(angle_in_radians);

   return matrix2D(
      cos_result, (-1) * sin_result,
      sin_result, cos_result);
}

matrix2D matrix2D::translate(float x_delta, float y_delta)
{
   //return matrix2D();
   return matrix2D(x_delta, y_delta);
}

matrix2D operator*(const matrix2D& left, const matrix2D& right)
{
   float new_x0 = left.x0 * right.x0 + left.x1*right.y0 + left.x_translate*right.row2_col0;
   float new_x1 = left.x0 * right.x1 + left.x1*right.y1 + left.x_translate*right.row2_col1;
   float new_x_translate = left.x0 * right.x_translate + left.x1*right.y_translate + left.x_translate*right.row2_col2;

   float new_y0 = left.y0 * right.x0 + left.y1*right.y0 + left.y_translate*right.row2_col0;
   float new_y1 = left.y0 * right.x1 + left.y1*right.y1 + left.y_translate*right.row2_col1;
   float new_y_translate = left.y0 * right.x_translate + left.y1*right.y_translate + left.y_translate*right.row2_col2;

   float new_row2_col0 = left.row2_col0 * right.x0 + left.row2_col1*right.y0 + left.row2_col2*right.row2_col0;
   float new_row2_col1 = left.row2_col0 * right.x1 + left.row2_col1*right.y1 + left.row2_col2*right.row2_col1;
   float new_row2_col2 = left.row2_col0 * right.x_translate + left.row2_col1*right.y_translate + left.row2_col2*right.row2_col2;

   return matrix2D(
      new_x0, new_x1, new_x_translate,
      new_y0, new_y1, new_y_translate,
      new_row2_col0, new_row2_col1, new_row2_col2);
}

vector2D operator*(const matrix2D& mat2d, const vector2D& vec2d)
{
   // Expected result:
   // matrix.x0 * vector.x + matrix.x1 * vector.y = new vector.x
   // matrix.y0 * vector.x + matrix.y1 * vector.y = new vector.y

   return vector2D(
      mat2d.x0 * vec2d.x + mat2d.x1 * vec2d.y + mat2d.x_translate * vec2d.enable_translate,
      mat2d.y0 * vec2d.x + mat2d.y1 * vec2d.y + mat2d.y_translate * vec2d.enable_translate,
      mat2d.row2_col0 * vec2d.x + mat2d.row2_col1 * vec2d.y + mat2d.row2_col2 * vec2d.enable_translate);
}

