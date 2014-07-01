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

   const char* category_strings[] =
   {
      "Category1",
      "Category2",
      "Category3",
   };

   // this calculation is useful only if all strings are the same lengths
   const int NUM_CATEGORY_STRINGS = sizeof(category_strings) / sizeof(*category_strings);

   // add the categories to the profiler
   for (int index = 0; index < NUM_CATEGORY_STRINGS; index++)
   {
      my_profiler.add_category(category_strings[index]);
   }

   // start the first frame
   my_profiler.new_frame();

   // write whole number float values to the file
   // Note: The "add category time log" function requires a float, but for 
   // simplicity of testing, we want to read a C string and pass it to atoi(...),
   // so only write whole numbers.
   const int NUM_TEST_ENTRIES = 15;
   for (float float_value_counter = 0; 
      float_value_counter < NUM_TEST_ENTRIES; 
      float_value_counter += NUM_CATEGORY_STRINGS)
   {
      for (int index = 0; index < NUM_CATEGORY_STRINGS; index++)
      {
         my_profiler.add_category_time_log(category_strings[index], float_value_counter + index);
      }
      
      my_profiler.new_frame();
   }

   my_profiler.shutdown();

   ifstream input(profiler_filename);

   // check the titles
   for (int index = 0; index < NUM_CATEGORY_STRINGS; index++)
   {
      EXPECT_EQ(get_next_token(input), category_strings[index]);
   }

   // check the values
   for (int value_counter = 0; value_counter < NUM_TEST_ENTRIES; value_counter++)
   {
      string buf = get_next_token(input).c_str();
      EXPECT_EQ(atoi(buf.c_str()), value_counter);
   }

   input.close();
}


#endif