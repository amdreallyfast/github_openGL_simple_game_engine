#include "Game_Clock.h"


namespace Timing
{
   Game_Clock::Game_Clock()
   {
      // blank constructor; call the initializer function instead
   }


   Game_Clock& Game_Clock::get_instance()
   {
      static Game_Clock instance;

      return instance;
   }

   bool Game_Clock::initialize()
   {
      return m_clock.initialize();
   }


   bool Game_Clock::shutdown()
   {
      return m_clock.shutdown();
   }


   void Game_Clock::new_frame()
   {
      m_clock.new_frame();
   }


   float Game_Clock::delta_time_last_frame() const
   {
      return m_clock.delta_time_last_frame();
   }
}
