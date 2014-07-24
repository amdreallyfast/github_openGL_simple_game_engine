#include "Boundary_Handler_Component.h"

#include <Math\vector2D.h>
using Math::Vector2D;

#include <Misc\Typedefs.h>

namespace Entities
{
   void Boundary_Handler_Component::update()
   {
      for (uint index = 0; index < g_NUM_BORDER_VERTS; index++)
      {
         const Vector2D& first = g_border_verts[index];
         const Vector2D& second = g_border_verts[(index + 1) % g_NUM_BORDER_VERTS];
         Vector2D border = second - first;
         Vector2D respective_ship_position = g_ship_position - first;

         Vector2D border_normal = border.get_ccw_perpendicular_vector();
         float dot_result = border_normal.dot(respective_ship_position);
         if (dot_result < 0)
         {
            g_ship_velocity += (-2) * g_ship_velocity.project_onto(border_normal);
         }
      }

   }
}