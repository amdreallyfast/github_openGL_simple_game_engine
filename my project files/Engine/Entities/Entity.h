#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include "Misc\Typedefs.h"
#include "Math\Vector2D.h"

namespace Entities
{
   class Game_Component;

   class Entity
   {
   public:
      // creates Entity startup condition
      bool initialize();

      // for consistency, we also require a shutdown
      bool shutdown();

      // add a component pointer to the entity, but the component is stored
      // elsewhere
      void add_component(Game_Component* component);

      
      // this is the only component that is shared by all entities, so it is
      // put here by its actual type instead of as a Game_Component type
      Math::Vector2D position;

   private:

      static const uint m_MAX_COMPONENTS = 10;
      uint m_num_current_components;
      Game_Component* m_components[m_MAX_COMPONENTS];
   };
}

#endif

