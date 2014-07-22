#include "Physics_Components.h"

#include <Entities\Entity.h>

namespace Entities
{
   void Physics_Components::update()
   {
      m_containing_entity->position += velocity;
   }
}
