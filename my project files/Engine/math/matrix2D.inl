
Matrix2D Matrix2D::rotate(float angle_in_radians)
{
   float cos_result = cosf(angle_in_radians);
   float sin_result = sinf(angle_in_radians);

   // resulting matrix will look like this:
   //
   //                               |
   //                               v
   //    | cos(angle)  -sin(angle)  0  |  <-- need to fill this in manually
   //    | sin(angle)   cos(angle)  0  |
   //    |     0            0       1  |

   // need to fill in the first row, third value manually in order to get to 
   // the second row values in the constructor, but leave everything else as
   // default
   return Matrix2D(
      cos_result, (-1) * sin_result, 0.0f,
      sin_result, cos_result);
}


Matrix2D Matrix2D::translate(float x_delta, float y_delta)
{
   // resulting matrix will look like this:
   //    | 1  0  x_delta |
   //    | 0  1  y_delta |
   //    | 0  0     1    |

   // only fill in as much of the constructor as you need, then leave the 
   // rest default
   return Matrix2D(
      1.0f, 0.0f, x_delta,
      0.0f, 1.0f, y_delta);
}


Matrix2D Matrix2D::scale(float scale_x, float scale_y)
{
   // resulting matrix will look like this
   //    | scale_x    0      0 |
   //    |   0      scale_y  0 |
   //    |   0        0      1 |

   // fill in what you need, then leave the rest default
   return Matrix2D(
      scale_x, 0.0f, 0.0f,
      0.0f, scale_y);
}


Vector2D Matrix2D::get_displacement_vector_for_non_origin_rotation(float angle_in_radians, const Vector2D& pivot)
{
   // herese a brief explanation of how this will go down
   // We want to rotate this pivot point around itself by "angle in radians"
   // radians.  We will do that by rotating it by that angle, mirroring it
   // around both axes, and adding it to its original self.  Try drawing it 
   // on paper.
   // Add this resulting displacement vector to any rotated-around-origin 
   // vector to get vector that would result if that point had rotated 
   // around the pivot specified in this function's arguments.

   Matrix2D rotator = rotate(angle_in_radians);
   Vector2D result = (-1) * (rotator * pivot) + pivot;

   // return via copy constructor because there is no way that the result's
   // individual arguments could have been constructed
   return result;
}


Matrix2D operator*(const Matrix2D& left, const Matrix2D& right)
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

   return Matrix2D(
      new_a00, new_a01, new_a02,
      new_a10, new_a11, new_a12,
      new_a20, new_a21, new_a22);
}

Vector2D operator*(const Matrix2D& m, const Vector2D& v)
{
   // it is not necessary to multiply the vector's "enable translate" value "t"
   // because the third row of the matrix as (0, 0, 1), which will only result
   // in the original "t" value anyway, so just carry it over and be done with
   // it
   return Vector2D(
      m.a00 * v.x + m.a01 * v.y + m.a02 * v.w,
      m.a10 * v.x + m.a11 * v.y + m.a12 * v.w,
      m.a20 * v.x + m.a21 * v.y + m.a22 * v.w);
}

