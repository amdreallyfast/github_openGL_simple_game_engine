#ifndef ENGINE_RENDERER_COMPONENT_H
#define ENGINE_RENDERER_COMPONENT_H

#include "Entities\Game_Component.h"
namespace Rendering { class Renderable; }

namespace Entities
{
   class __declspec(dllexport) Renderer_Component : public Game_Component
   {
   public:
      // ??what are we doing??
      void set_data(Rendering::Renderable *renderable_ptr);

      // override the base class' update function
      void update();

   private:
      // ??why store a pointer to renderable data and not the data itself??
      Rendering::Renderable *m_renderable_ptr;
   };
}

#endif
