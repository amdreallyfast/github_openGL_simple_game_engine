#pragma once
#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include <Entities\Game_Component.h>

namespace Entities
{
   class Physics_Component;

   // this is not a reusable component, so it goes into the game 
   // and not the engine
   class Controller_Component : public Game_Component
   {
   public:
      bool initialize();
      void update();

   private:
      Physics_Component* m_easy_physics_ptr;
   };
}

#endif

