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

TEST(Profiler, File_Read_Write)
{
   const char* profiler_filename = "profiler_results.csv";
   profiler my_profiler(profiler_filename);

   const char* category_str_1 = "Category1";
   const char* category_str_2 = "Category2";
   const char* category_str_3 = "Category3";

   my_profiler.add_category(category_str_1);
   my_profiler.add_category(category_str_2);
   my_profiler.add_category(category_str_3);

   my_profiler.new_frame();

   const unsigned int NUM_ENTRIES = 15;
   for (float i = 0; i < NUM_ENTRIES; i++)
   {
      my_profiler.add_category_time_log(category_str_1, i);
      my_profiler.add_category_time_log(category_str_2, i);
      my_profiler.add_category_time_log(category_str_3, i);
      my_profiler.new_frame();
   }

   my_profiler.shutdown();

   ifstream input(profiler_filename);
   EXPECT_EQ(get_next_token(input), category_str_1);
   EXPECT_EQ(get_next_token(input), category_str_2);
   EXPECT_EQ(get_next_token(input), category_str_3);
   for (int i = 0; i < NUM_ENTRIES; i++)
   {
      // get an entire row once per loop because data was recorded 
      // identically for each category once per loop
      string buf = get_next_token(input).c_str();
      EXPECT_EQ(atoi(buf.c_str()), i);

      buf = get_next_token(input).c_str();
      EXPECT_EQ(atoi(buf.c_str()), i);

      buf = get_next_token(input).c_str();
      EXPECT_EQ(atoi(buf.c_str()), i);
   }

   input.close();
}


#endif