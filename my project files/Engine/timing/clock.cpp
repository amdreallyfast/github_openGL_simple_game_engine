#include "clock.h"

namespace Timing
{
   bool Clock::initialize()
   {
      return false;
   }

   bool Clock::shutdown()
   {
      return false;
   }

   void Clock::new_frame()
   {

   }

   float Clock::time_elapsed_last_frame() const
   {
      return -1;
   }
}