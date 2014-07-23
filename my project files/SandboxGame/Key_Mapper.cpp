#include "Key_Mapper.h"

// for VK_some_key
#include <Windows.h>

#include <cassert>

// for key assignment enums
#include "Key_Action_Enums.h"

namespace Input
{
   int Key_Mapper::get_key_for(int action) const
   {
      switch (action)
      {
      case ACCELERATE:
         return VK_UP;
      case ROTATE_LEFT:
         return VK_LEFT;
      case ROTATE_RIGHT:
         return VK_RIGHT;
      }

      // if no known action was performed, assert false 
      assert(false);
      return -1;
   }
}
