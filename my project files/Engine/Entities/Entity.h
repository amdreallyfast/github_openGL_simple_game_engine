#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include "Misc\Typedefs.h"
#include "Math\Vector2D.h"

namespace Entities
{
   class Game_Component;

   class __declspec(dllexport) Entity
   {
   public:
      // for initializing non-static-const members values
      Entity();

      // initalizes all components, or resets them if it is called sometime 
      // after it has already been called
      bool initialize();

      // for consistency, we also require a shutdown
      bool shutdown();

      // add a component pointer to the entity, but the component is stored
      // elsewhere
      void add_component(Game_Component* component);

      // goes through all its components and causes them to update
      void update();

      // this is so that a component can get at one of its sibling components
      template<class T>
      T* get_component() const;


      // these components/values are shared by all entities, and they will
      // likely be updated by some other component, so just make them public
      Math::Vector2D position;
      float orientation_radians;

   private:
      static const uint m_MAX_COMPONENTS = 10;
      uint m_num_current_components;
      Game_Component* m_components[m_MAX_COMPONENTS];
   };

   // define it in this file so that it is implicitly inline
   template<class T>
   T* Entity::get_component() const
   {
      for (uint index = 0; index < m_num_current_components; index++)
      {
         // downcast the component to the requested class
         T* ret = dynamic_cast<T*>(m_components[index]);
         
         if (ret != 0)
         {
            return ret;
         }
      }

      // didn't find the requested type, so return a null pointer
      return 0;
   }
}

#endif

