#ifndef ENGINE_BORDER_HANDLER_COMPONENT_H
#define ENGINE_BORDER_HANDLER_COMPONENT_H

#include <Entities\Game_Component.h>
#include <Math\vector2D.h>
#include <Misc\Typedefs.h>

namespace Entities
{
   class Physics_Component;

   class __declspec(dllexport) Border_Handler_Component : public Game_Component
   {
   public:
      // for making sure that pointers construct to 0
      Border_Handler_Component();

      // override base class functionality
      bool initialize();
      void update();

      // make a "set data" function because we want to be able to
      // abort with error if setting the boundary data point goes wrong,
      // and we won't use exceptions, so we can't use a constructor, and
      // we can't use initialize() because we want to keep its parameter
      // list void so that Entity can blindly initialize all it's 
      // components, but we still need a pointer to boundary data
      void set_data(Math::Vector2D *boundary_verts_ptr, uint num_boundary_verts);

   private:
      // this cannot be constant because it is set by set_data(),
      // but make it all caps to strongly suggest that it should not
      // be changed
      uint m_NUM_BOUNDARY_VERTS;

      const Math::Vector2D *m_boundary_verts_ptr;


      Physics_Component *m_physics_sibling_ptr;
      Math::Vector2D m_prev_entity_position;
   };
}

#endif