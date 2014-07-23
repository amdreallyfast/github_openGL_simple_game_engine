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

      // override the base class' update()
      void update();

   private:
      // need to track velocity because acceleration is additive to velocity
      float m_linear_velocity;
      float m_angular_velocity;
   };
}


#endif
