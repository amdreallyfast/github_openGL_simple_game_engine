#ifndef ENGINE_KEY_INPUT_H
#define ENGINE_KEY_INPUT_H

namespace Input
{
   class I_Key_Mapper;

   class Key_Input
   {
   public:
      bool initialize(I_Key_Mapper *key_mapper, int max_action_value);
      bool shutdown();
      void update();
      
      inline int get_actions_this_frame() const;
      bool actions_hot_this_frame(int actions) const;

   private:
      I_Key_Mapper *m_key_mapper;
      int m_max_action_value;
      int m_actions_this_frame;
   };
}

#endif