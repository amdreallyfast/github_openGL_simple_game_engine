#pragma once

namespace Timing
{
   class Clock
   {
   public:
      bool initialize();
      bool shutdown();
      void new_frame();
      float time_elapsed_last_frame() const;
   };
}
