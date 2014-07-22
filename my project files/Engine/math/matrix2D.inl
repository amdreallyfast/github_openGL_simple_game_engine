
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


Matrix2D Matrix2D::translate(float new_x, float new_y)
{
   // resulting matrix will look like this:
   //    | 1  0  x_delta |
   //    | 0  1  y_delta |
   //    | 0  0     1    |

   // only fill in as much of the constructor as you need, then leave the 
   // rest default
   return Matrix2D(
      1.0f, 0.0f, new_x,
      0.0f, 1.0f, new_y);
}

Matrix2D Matrix2D::translate(const Vector2D& new_position)
{
   // chain into another inline
   return translate(new_position.x, new_position.y);
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
   float new_x0 = left.x0 * right.x0 + left.x1*right.y0 + left.x2*right.w0;
   float new_x1 = left.x0 * right.x1 + left.x1*right.y1 + left.x2*right.w1;
   float new_x2 = left.x0 * right.x2 + left.x1*right.y2 + left.x2*right.w2;

   float new_y0 = left.y0 * right.x0 + left.y1*right.y0 + left.y2*right.w0;
   float new_y1 = left.y0 * right.x1 + left.y1*right.y1 + left.y2*right.w1;
   float new_y2 = left.y0 * right.x2 + left.y1*right.y2 + left.y2*right.w2;

   float new_w0 = left.w0 * right.x0 + left.w1*right.y0 + left.w2*right.w0;
   float new_w1 = left.w0 * right.x1 + left.w1*right.y1 + left.w2*right.w1;
   float new_w2 = left.w0 * right.x2 + left.w1*right.y2 + left.w2*right.w2;

   return Matrix2D(
      new_x0, new_x1, new_x2,
      new_y0, new_y1, new_y2,
      new_w0, new_w1, new_w2);
}

Vector2D operator*(const Matrix2D& m, const Vector2D& v)
{
   // it is not necessary to multiply the vector's "enable translate" value "t"
   // because the third row of the matrix as (0, 0, 1), which will only result
   // in the original "t" value anyway, so just carry it over and be done with
   // it
   return Vector2D(
      m.x0 * v.x + m.x1 * v.y + m.x2 * v.w,
      m.y0 * v.x + m.y1 * v.y + m.y2 * v.w,
      m.w0 * v.x + m.w1 * v.y + m.w2 * v.w);
}

