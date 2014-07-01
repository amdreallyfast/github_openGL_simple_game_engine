#include <gtest\gtest.h>

#include "DebugTools\Profiling\profiler.h"

TEST(Profiler, asdfasdf)
{
   profiler my_profiler;
   my_profiler.initialize();

   my_profiler.new_frame();

   const unsigned int NUM_ENTRIES = 15;
   for (int i = 0; i < NUM_ENTRIES; i += 3)
   {
      my_profiler.add_entry("Category1", i);
      my_profiler.add_entry("Category2", i + 1);
      my_profiler.add_entry("Category3", i + 2);
   }

   my_profiler.shutdown();


}
