#ifndef ENGINE_MATRIX_2D
#define ENGINE_MATRIX_2D

namespace Math
{
   struct matrix2D
   {
      float x0, x1;  // row 0, column 0 and 1
      float y0, y1;  // row 1, column 0 and 1

      // declare constructor explicit so that we do not have any implicit conversions
      // from "float" to "matrix2D"
      explicit matrix2D(
         float start_x0 = 0, float start_x1 = 0,
         float start_y0 = 0, float start_y1 = 0) 
         :
         x0(start_x0), x1(start_x1),
         y0(start_y0), y1(start_y1)
      {

      }
   };
}

#endif