#pragma once
#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include <Entities\Game_Component.h>

namespace Entities
{

   // this is not a reusable component, so it goes into the game 
   // and not the engine
   class Controller_Component : public Game_Component
   {
   public:
      void update();
   };
}

#endif

