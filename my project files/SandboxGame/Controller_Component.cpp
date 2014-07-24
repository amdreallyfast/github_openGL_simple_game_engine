#include "Controller_Component.h"

// for getting at the physics component
#include <Entities\Entity.h>
#include <Entities\Components\Physics_Component.h>

// from the engine
#include <Input\Key_Input.h>
using Input::Key_Input;

// for actions specific to this game
#include <Key_Action_Enums.h>
using Input::Key_Action_Enums;

namespace Entities
{
   bool Controller_Component::initialize()
   {
      m_easy_physics_ptr = m_containing_entity_ptr->get_component<Physics_Component>();
      return (m_easy_physics_ptr != 0);
   }

   void Controller_Component::update()
   {
      const float ANGULAR_ACCELERATION = 0.5f;
      const float LINEAR_ACCELERATION = 0.2f;

      if (Key_Input::get_instance().actions_are_hot(Key_Action_Enums::ROTATE_RIGHT))
      {
         m_easy_physics_ptr->angular_acceleration = -ANGULAR_ACCELERATION;
      }
      else if (Key_Input::get_instance().actions_are_hot(Key_Action_Enums::ROTATE_LEFT))
      {
         m_easy_physics_ptr->angular_acceleration = +ANGULAR_ACCELERATION;
      }
      else
      {
         m_easy_physics_ptr->angular_acceleration = 0;
      }

      if (Key_Input::get_instance().actions_are_hot(Key_Action_Enums::ACCELERATE))
      {
         m_easy_physics_ptr->linear_acceleration = LINEAR_ACCELERATION;
      }
      else
      {
         m_easy_physics_ptr->linear_acceleration = 0;
      }
   }
}
