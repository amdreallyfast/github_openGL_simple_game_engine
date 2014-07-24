#ifndef ENGINE_GAME_CLOCK_H
#define ENGINE_GAME_CLOCK_H

#include <Timing\clock.h>

namespace Timing
{
   // this is a wrapper for the generic engine clock, and it is the 
   // official clock of the game (as opposed to the profiler)
   class __declspec(dllexport) Game_Clock
   {
   public:
      static Game_Clock& get_instance();

      bool initialize();
      bool shutdown();

      void new_frame();
      float delta_time_last_frame() const;

   private:
      // make the default constructor empty and implicitly inline, and 
      // don't define the other constructors
      Game_Clock() {}
      Game_Clock(const Game_Clock&);
      Game_Clock& operator=(const Game_Clock&);

      Clock m_clock;
   };
}


#endif
