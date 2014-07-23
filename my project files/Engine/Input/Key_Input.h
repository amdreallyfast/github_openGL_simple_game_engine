#ifndef ENGINE_KEY_INPUT_H
#define ENGINE_KEY_INPUT_H

namespace Input
{
   class I_Key_Mapper;

   class __declspec(dllexport) Key_Input
   {
   public:
      static Key_Input& get_instance();

      bool initialize(I_Key_Mapper *key_mapper, int max_action_value);
      bool shutdown();
      void update();
      
      inline int get_actions_this_frame() const;
      bool actions_hot_this_frame(int actions) const;

   private:
      Key_Input();
      Key_Input(const Key_Input&);
      Key_Input& operator=(const Key_Input&);

      I_Key_Mapper *m_key_mapper;
      int m_max_action_value;
      int m_actions_this_frame;
   };
}

#endif