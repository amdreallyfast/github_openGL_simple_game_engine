#ifndef SANDBOX_GAME_MY_MENU_CHOICE_H
#define SANDBOX_GAME_MY_MENU_CHOICE_H

namespace Input
{
   enum My_Menu_Choice
   {
      ACCELERATE   = 0x00000001,
      ROTATE_LEFT  = 0x00000002,
      ROTATE_RIGHT = 0x00000004,
      MAX =          0x00000008,
   };
}

#endif