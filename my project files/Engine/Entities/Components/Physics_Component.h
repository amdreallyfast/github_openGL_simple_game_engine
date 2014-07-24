#ifndef PHYSICS_COMPONENTS_H
#define PHYSICS_COMPONENTS_H

#include <Entities\Game_Component.h>
#include <Math\Vector2D.h>

namespace Entities
{
   class __declspec(dllexport) Physics_Component: public Game_Component
   {
   public:
      bool initialize();

      float linear_acceleration;
      float angular_acceleration;

      // need to track velocity because acceleration is additive to velocity
      // Note: Need to make these public because the boundary handler 
      // component may need to alter them.
      Math::Vector2D linear_velocity;
      float angular_velocity;

      // override the base class' update()
      void update();

   private:
   };
}


#endif
