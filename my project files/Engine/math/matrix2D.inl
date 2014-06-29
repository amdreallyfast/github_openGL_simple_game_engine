
matrix2D matrix2D::rotate(float angle_in_radians, float pivot_x, float pivot_y)
{
   float cos_result = cosf(angle_in_radians);
   float sin_result = sinf(angle_in_radians);
   vector2D pivot(pivot_x, pivot_y);

   // first construct a matrix to rotate the pivot vector P'
   // Note: There is 0 displacement for this vector.
   matrix2D pivot_rotator(
      cos_result, (-1) * sin_result, 0,
      sin_result, cos_result, 0);

   // rotate the pivot vector
   vector2D pivot_rotated = pivot_rotator * pivot;

   // now mirror 

   // resulting matrix will look like this:
   //    | cos(angle)  -sin(angle)  0  displacement.x |
   //    | sin(angle)   cos(angle)  0  displacement.y |
   //    |     0            0       1        0        |
   //    |     0            0       0        1        |



   //return matrix2D(
   //   cos_result, (-1) * sin_result,
   //   sin_result, cos_result);
   return matrix2D();
}

matrix2D matrix2D::translate(float x_delta, float y_delta)
{
   // resulting matrix will look like this:
   //    | 1  0  x_delta |
   //    | 0  1  y_delta |
   //    | 0  0     1    |
   //return matrix2D(x_delta, y_delta);
   return matrix2D();
}

matrix2D operator*(const matrix2D& left, const matrix2D& right)
{
   float new_a00 = left.a00 * right.a00 + left.a01*right.a10 + left.a02*right.a20 + left.a03*right.a30;
   float new_a01 = left.a00 * right.a01 + left.a01*right.a11 + left.a02*right.a21 + left.a03*right.a31;
   float new_a02 = left.a00 * right.a02 + left.a01*right.a12 + left.a02*right.a22 + left.a03*right.a32;
   float new_a03 = left.a00 * right.a03 + left.a01*right.a13 + left.a02*right.a23 + left.a03*right.a33;

   float new_a10 = left.a10 * right.a00 + left.a11*right.a10 + left.a12*right.a20 + left.a13*right.a30;
   float new_a11 = left.a10 * right.a01 + left.a11*right.a11 + left.a12*right.a21 + left.a13*right.a31;
   float new_a12 = left.a10 * right.a02 + left.a11*right.a12 + left.a12*right.a22 + left.a13*right.a32;
   float new_a13 = left.a10 * right.a03 + left.a11*right.a13 + left.a12*right.a23 + left.a13*right.a33;

   float new_a20 = left.a20 * right.a00 + left.a21*right.a10 + left.a22*right.a20 + left.a23*right.a30;
   float new_a21 = left.a20 * right.a01 + left.a21*right.a11 + left.a22*right.a21 + left.a23*right.a31;
   float new_a22 = left.a20 * right.a02 + left.a21*right.a12 + left.a22*right.a22 + left.a23*right.a32;
   float new_a23 = left.a20 * right.a03 + left.a21*right.a13 + left.a22*right.a23 + left.a23*right.a33;

   float new_a30 = left.a30 * right.a00 + left.a31*right.a10 + left.a32*right.a20 + left.a33*right.a30;
   float new_a31 = left.a30 * right.a01 + left.a31*right.a11 + left.a32*right.a21 + left.a33*right.a31;
   float new_a32 = left.a30 * right.a02 + left.a31*right.a12 + left.a32*right.a22 + left.a33*right.a32;
   float new_a33 = left.a30 * right.a03 + left.a31*right.a13 + left.a32*right.a23 + left.a33*right.a33;

   return matrix2D(
      new_a00, new_a01, new_a02, new_a03,
      new_a10, new_a11, new_a12, new_a13,
      new_a20, new_a21, new_a22, new_a23,
      new_a30, new_a31, new_a32, new_a33);
}

vector2D operator*(const matrix2D& mat2d, const vector2D& vec2d)
{
   // Expected result:
   // new vector.x =                            
   //    matrix.a00 * vector.x + matrix.a01 * vector.y + matrix.a02 * vector.enable_translate + matrix.a03 * vector.enable_non_origin_rotation
   // new vector.y =
   //    matrix.a10 * vector.x + matrix.a11 * vector.y + matrix.a12 * vector.enable_translate + matrix.a13 * vector.enable_non_origin_rotation
   // new vector.enable_translate =
   //    if vector.enable_translate is 0, then new vector.enable_translate is also 0; ditto with 1
   // new vector.enable_non_origin_rotation =
   //    if vector.enable_non_origin_rotation is 0, then new vector.enable_non_origin_rotation is also 0; ditto with 1

   return vector2D(
      mat2d.a00 * vec2d.x + mat2d.a01 * vec2d.y + mat2d.a02 * vec2d.enable_translate + mat2d.a03 * vec2d.enable_non_origin_rotation,
      mat2d.a10 * vec2d.x + mat2d.a11 * vec2d.y + mat2d.a12 * vec2d.enable_translate + mat2d.a13 * vec2d.enable_non_origin_rotation,
      (1 == vec2d.enable_translate) ? true : false,
      (1 == vec2d.enable_non_origin_rotation) ? true : false);

   return vector2D();
}

