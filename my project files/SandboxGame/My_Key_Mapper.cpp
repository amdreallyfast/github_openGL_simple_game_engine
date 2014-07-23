#include "My_Key_Mapper.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cassert>

// for key assignment enums
#include "My_Menu_Choice.h"

namespace Input
{
   int My_Key_Mapper::get_action_for(int key) const
   {
      switch (key)
      {
      case ACCELERATE:
         return VK_UP;
      case ROTATE_LEFT:
         return VK_LEFT;
      case ROTATE_RIGHT:
         return VK_RIGHT;
      }

      // if no key known key was pressed, assert false 
      assert(false);
      return -1;
   }

   int My_Key_Mapper::get_key_for(int action) const
   {
      switch (action)
      {
      case VK_UP:
         return ACCELERATE;
      case VK_LEFT:
         return ROTATE_LEFT;
      case VK_RIGHT:
         return ROTATE_RIGHT;
      }

      // if no known action was performed, assert false 
      assert(false);
      return -1;
   }
}
