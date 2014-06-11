#pragma once

// this is a big header, but necessary to get access to LARGE_INTEGER
// Note: We can't just include winnt.h, in which LARGE_INTEGER is defined,
// because there are some macros that this header file needs that are defined
// further up in the header hierarchy.  So just include Windows.h and be done
// with it.
#include <Windows.h>

namespace Timing
{
   // the "__declspec(dllexport)" is Microsoft's way of modifying the class
   // declaration so that it will be exported into a library that is external to
   // this dll project
   class __declspec(dllexport) Clock
   {
   public:
      bool initialize();
      bool shutdown();
      void new_frame();
      float time_elapsed_last_frame() const;

   private:
      LARGE_INTEGER m_last_frame_time_counter;
      LARGE_INTEGER m_cpu_timer_frequency;
      //LARGE_INTEGER m_delta_last_frame;
      float m_delta_time;
   };
}
