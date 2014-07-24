#include "Border_Handler_Component.h"

// for getting at the Physics_Component sibling component
#include <Entities\Components\Physics_Component.h>
#include <Entities\Entity.h>

// for making vectors out of the border points
#include <Math\vector2D.h>
using Math::Vector2D;

// for uint
#include <Misc\Typedefs.h>



namespace Entities
{
   Border_Handler_Component::Border_Handler_Component() :
      m_boundary_verts_ptr(0),
      m_physics_sibling_ptr(0)
   {
   }


   bool Border_Handler_Component::initialize()
   {
      m_physics_sibling_ptr = m_containing_entity_ptr->get_component<Physics_Component>();
      return ((m_physics_sibling_ptr != 0) && (m_boundary_verts_ptr != 0));
   }


   void Border_Handler_Component::update()
   {
      for (uint index = 0; index < m_NUM_BOUNDARY_VERTS; index++)
      {
         const Vector2D& first = m_boundary_verts_ptr[index];
         const Vector2D& second = m_boundary_verts_ptr[(index + 1) % m_NUM_BOUNDARY_VERTS];
         Vector2D border = second - first;
         Vector2D respective_position = (m_containing_entity_ptr->position) - first;

         Vector2D border_normal = border.get_ccw_perpendicular_vector();
         float dot_result = border_normal.dot(respective_position);
         if (dot_result < 0)
         {
            m_physics_sibling_ptr->linear_velocity += (-2) * m_physics_sibling_ptr->linear_velocity.project_onto(border_normal);

            // move it back within the borders do avoid rare cases of
            // border lock
            m_containing_entity_ptr->position = m_prev_entity_position;
         }
      }

      m_prev_entity_position = m_containing_entity_ptr->position;
   }


   void Border_Handler_Component::set_data(Math::Vector2D *boundary_verts_ptr, uint num_boundary_verts)
   {
      m_boundary_verts_ptr = boundary_verts_ptr;
      m_NUM_BOUNDARY_VERTS = num_boundary_verts;
   }
}