#include <gtest\gtest.h>

#include "DebugTools\Profiling\profiler.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;


#ifdef RUN_PROFILER_TESTS

string get_next_token(ifstream& the_file)
{
   char c;
   string return_val;

   // read while you are not at the end of file
   while (the_file.good())
   {
      the_file >> c;
      if (',' == c || '\n' == c)
      {
         break;
      }
      return_val += c;
   }

   return return_val;
}

TEST(Profiler, asdfasdf)
{
   profiler my_profiler;

   const char* profiler_filename = "profiler_results.csv";
   my_profiler.initialize(profiler_filename);

   my_profiler.new_frame();

   const unsigned int NUM_ENTRIES = 15;
   for (float i = 0; i < NUM_ENTRIES; i++)
   {
      my_profiler.add_entry("Category1", i);
      my_profiler.add_entry("Category2", i);
      my_profiler.add_entry("Category3", i);
   }

   my_profiler.shutdown();

   ifstream input(profiler_filename);
   EXPECT_EQ(get_next_token(input), "Category1");
   EXPECT_EQ(get_next_token(input), "Category2");
   EXPECT_EQ(get_next_token(input), "Category3");
   for (int i = 0; i < NUM_ENTRIES; i++)
   {
      string buf = get_next_token(input).c_str();
      EXPECT_EQ(atoi(buf.c_str()), i);
   }

   input.close();
}


#endif