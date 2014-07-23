#include "Physics_Component.h"

#include <Entities\Entity.h>

// for rotating and moving the ship
#include <Math\matrix2D.h>
using Math::Matrix2D;
#include <Math\Vector2D.h>
using Math::Vector2D;

// for the time part of acceleration and velocity calculations
#include <Timing\Game_Clock.h>
using Timing::Game_Clock;

namespace Entities
{
   bool Physics_Component::initialize()
   {
      linear_acceleration = 0;
      angular_acceleration = 0;
      m_angular_velocity = 0;

      return true;
   }

   void Physics_Component::update()
   {
      // grab delta time from the clock to modify velocities
      
      float delta_time = Game_Clock::get_instance().delta_time_last_frame();

      // rotate the entity first
      m_angular_velocity += angular_acceleration * delta_time;
      m_containing_entity->orientation_radians += m_angular_velocity * delta_time;

      // now move it in the new direction
      Vector2D forward_for_my_ship(0, 1);
      Matrix2D rotation_mat = Matrix2D::rotate(m_containing_entity->orientation_radians);
      Vector2D direction_to_accel = rotation_mat * forward_for_my_ship;

      if (linear_acceleration > 0)
      {
         m_linear_velocity += direction_to_accel * (linear_acceleration * delta_time);
      }
         
      m_containing_entity->position += m_linear_velocity * delta_time;
   }
}
