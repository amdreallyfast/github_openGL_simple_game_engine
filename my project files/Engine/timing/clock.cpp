#include "clock.h"

namespace Timing
{
   bool Clock::initialize()
   {
      // the "performance frequency only changes on system reset, so it's ok
      // to do it only during initialization
      bool b = QueryPerformanceFrequency(&m_cpu_timer_frequency);
      if (!b)
      {
         return false;
      }

      // assign the counter it's first value
      return QueryPerformanceCounter(&m_last_frame_time_counter);
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
      LARGE_INTEGER this_time_counter;
      QueryPerformanceCounter(&this_time_counter);
      LARGE_INTEGER delta;
      delta.QuadPart = this_time_counter.QuadPart - m_last_frame_time_counter.QuadPart;
      m_delta_time = ((float)delta.QuadPart) / m_cpu_timer_frequency.QuadPart;

      m_last_frame_time_counter.QuadPart = this_time_counter.QuadPart;
   }

   float Clock::time_elapsed_last_frame() const
   {
      return m_delta_time;
   }
}