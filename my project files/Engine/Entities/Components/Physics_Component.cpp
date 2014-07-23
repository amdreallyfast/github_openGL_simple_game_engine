#include "Physics_Component.h"

#include <Entities\Entity.h>

// for rotating and moving the ship
#include <Math\matrix2D.h>
using Math::Matrix2D;
#include <Math\Vector2D.h>
using Math::Vector2D;


namespace Entities
{
   bool Physics_Component::initialize()
   {
      linear_acceleration = 0;
      angular_acceleration = 0;

      m_linear_velocity = 0;
      m_angular_velocity = 0;

      return true;
   }

   void Physics_Component::update()
   {
      // grab delta time from the clock to modify velocities
      
      const float SHADY_MAGIC_DELTA_T = 0.03f;

      // rotate the entity first
      m_angular_velocity += angular_acceleration * SHADY_MAGIC_DELTA_T;
      m_containing_entity->orientation_radians += m_angular_velocity * SHADY_MAGIC_DELTA_T;

      // now move it in the new direction
      Vector2D forward_for_my_ship(0, 1);
      Matrix2D rotation_mat = Matrix2D::rotate(m_containing_entity->orientation_radians);
      Vector2D direction_to_accel = rotation_mat * forward_for_my_ship;

      m_linear_velocity = linear_acceleration * SHADY_MAGIC_DELTA_T;
      m_containing_entity->position += direction_to_accel * (m_linear_velocity * SHADY_MAGIC_DELTA_T);
   }
}
