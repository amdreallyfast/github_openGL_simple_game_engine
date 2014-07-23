#ifndef SANDBOX_GAME_MY_KEY_MAPPER_H
#define SANDBOX_GAME_MY_KEY_MAPPER_H

#include <Input\I_Key_Mapper.h>

// put it in the same namespace as the engine's input system (??why??)
namespace Input
{
   class Key_Mapper : public I_Key_Mapper
   {
   public:
      // override the base class functionality
      int get_key_for(int action) const;
   };
}

#endif

