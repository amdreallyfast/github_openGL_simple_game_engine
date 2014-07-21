#include "Entity.h"

// for checking that memory pools don't overflow
#include <cassert>

namespace Entities
{
   bool Entity::initialize()
   {
      m_num_current_components = 0;

      return true;
   }

   bool Entity::shutdown()
   {
      return true;
   }

   void Entity::add_component(Game_Component* component)
   {
      assert(m_num_current_components != m_MAX_COMPONENTS);
      m_components[m_num_current_components++] = component;
   }
}