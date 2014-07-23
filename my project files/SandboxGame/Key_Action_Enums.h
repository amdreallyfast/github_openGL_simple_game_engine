#ifndef SANDBOX_GAME_MY_KEY_CHOICE_ENUM_H
#define SANDBOX_GAME_MY_KEY_CHOICE_ENUM_H

namespace Input
{
   enum Key_Action_Enums
   {
      ACCELERATE   = 0x00000001,
      ROTATE_LEFT  = 0x00000002,
      ROTATE_RIGHT = 0x00000004,
      MAX =          0x00000008,
   };
}

#endif