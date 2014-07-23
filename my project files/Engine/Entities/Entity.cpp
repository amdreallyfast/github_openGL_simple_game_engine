#include "Entity.h"

// for checking that memory pools don't overflow
#include <cassert>

// so we can assign each component's "containing entity" pointer
#include "Entities\Game_Component.h"

// for uint
#include "Misc\Typedefs.h"

namespace Entities
{
   Entity::Entity() :
      m_num_current_components(0),
      orientation_radians(0)
   {
   }

   bool Entity::initialize()
   {
      for (uint index = 0; index < m_num_current_components; index++)
      {
         if (!m_components[index]->initialize())
         {
            return false;
         }
      }

      return true;
   }

   bool Entity::shutdown()
   {
      for (uint index = 0; index < m_num_current_components; index++)
      {
         if (!m_components[index]->shutdown())
         {
            return false;
         }
      }

      return true;
   }

   void Entity::add_component(Game_Component* component)
   {
      assert(m_num_current_components != m_MAX_COMPONENTS);
      m_components[m_num_current_components++] = component;
      component->m_containing_entity = this;
   }

   void Entity::update()
   {
      for (uint index = 0; index < m_num_current_components; index++)
      {
         m_components[index]->update();
      }
   }
}