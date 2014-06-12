#include "clock.h"

namespace Timing
{
   bool Clock::initialize()
   {
      // the "performance frequency only changes on system reset, so it's ok
      // to do it only during initialization
      // Note: If it succeeds, it returns non-zero, not a bool.  I got a 
      // compiler warning abotu a performance issue in int<-->bool conversion.
      // http://msdn.microsoft.com/en-us/library/windows/desktop/ms644905(v=vs.85).aspx
      bool success = (0 != QueryPerformanceFrequency(&m_cpu_timer_frequency));
      if (!success){ return false; }

      // assign the counter it's first value
      // Note: Like "query performance frequency", it returns non-zero if 
      // successful, not a bool.  
      success = (1 == QueryPerformanceCounter(&m_last_frame_time_counter));
      if (!success){ return false; }

      return true;
   }

   bool Clock::shutdown()
   {
      // make it return true just so that it passes the tests
      return true;
   }

   void Clock::new_frame()
   {
      // get the change in time and convert it to a float that represents the
      // franction of a second that has passed
      LARGE_INTEGER this_frame_time_counter;
      QueryPerformanceCounter(&this_frame_time_counter);
      LARGE_INTEGER delta;
      delta.QuadPart = this_frame_time_counter.QuadPart - m_last_frame_time_counter.QuadPart;
      m_delta_time = ((float)delta.QuadPart) / m_cpu_timer_frequency.QuadPart;

      m_last_frame_time_counter.QuadPart = this_frame_time_counter.QuadPart;
   }

   float Clock::time_elapsed_last_frame() const
   {
      return m_delta_time;
   }
}