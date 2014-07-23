#include "Key_Input.h"

#include <Windows.h>
#include <Input\I_Key_Mapper.h>

namespace Input
{
   bool Key_Input::initialize(I_Key_Mapper *key_mapper, int max_action_value)
   {
      if (0 == key_mapper)
      {
         return false;
      }

      this->m_key_mapper = key_mapper;
      this->m_max_action_value = max_action_value;

      return true;
   }

   bool Key_Input::shutdown()
   {
      return true;
   }

   void Key_Input::update()
   {
      // reset the possible actions
      m_actions_this_frame = 0;

      int possible_action = 1;
      while (possible_action != m_max_action_value)
      {
         int key = m_key_mapper->get_key_for(possible_action);
         
         // this function will be polled very quickly (30-60 times per second),
         // so don't worry about a key being pressed and released very very quickly 
         // between pollings
         if (GetAsyncKeyState(key))
         {
            m_actions_this_frame |= possible_action;
         }
         possible_action <<= 1;
      }
   }


   int Key_Input::get_actions_this_frame() const
   {
      return m_actions_this_frame;
   }


   bool Key_Input::actions_hot_this_frame(int actions) const
   {
      // if not all the actions are hot this frame, then we return false, but
      // if all the actions and more keys are pressed at the same time, then we
      // return true (the & operation masks out excess)
      return (actions == (m_actions_this_frame & actions));
   }

}