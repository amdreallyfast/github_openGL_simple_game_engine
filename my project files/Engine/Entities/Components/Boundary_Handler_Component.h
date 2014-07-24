#ifndef ENGINE_BOUNDARY_HANDLER_COMPONENT_H
#define ENGINE_BOUNDARY_HANDLER_COMPONENT_H

#include <Entities\Game_Component.h>

namespace Entities
{
   class Boundary_Handler_Component : public Game_Component
   {
   public:
      // override base class functionality
      void update();
   };
}

#endif