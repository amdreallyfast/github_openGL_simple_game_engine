#ifndef PHYSICS_COMPONENTS_H
#define PHYSICS_COMPONENTS_H

#include <Entities\Game_Component.h>
#include <Math\Vector2D.h>

namespace Entities
{
   class __declspec(dllexport) Physics_Components : public Game_Component
   {
   public:
      Math::Vector2D velocity;

      // override the base class' update()
      void update();
   };
}


#endif
