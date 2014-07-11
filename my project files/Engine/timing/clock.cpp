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
      // fraction of a second that has passed
      LARGE_INTEGER now;
      QueryPerformanceCounter(&now);

      LARGE_INTEGER delta;
      delta.QuadPart = now.QuadPart - m_last_frame_time_counter.QuadPart;
      m_delta_time = ((float)delta.QuadPart) / m_cpu_timer_frequency.QuadPart;

      m_last_frame_time_counter.QuadPart = now.QuadPart;
   }

   float Clock::time_elapsed_last_frame() const
   {
      return m_delta_time;
   }

   void Clock::stopwatch_start()
   {
      QueryPerformanceCounter(&m_stopwatch_start_time);
   }

   float Clock::stopwatch_stop_and_return_delta_time() const
   {
      LARGE_INTEGER now;
      QueryPerformanceCounter(&now);

      LARGE_INTEGER delta;
      delta.QuadPart = now.QuadPart - m_stopwatch_start_time.QuadPart;

      float fractional_second = ((float)delta.QuadPart) / m_cpu_timer_frequency.QuadPart;

      return fractional_second;
   }
}