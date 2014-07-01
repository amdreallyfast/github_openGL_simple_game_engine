#include <gtest\gtest.h>

#include "DebugTools\Profiling\profiler.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;


#ifdef RUN_PROFILER_TESTS

// this is an empty namespace to force data to be local to this file
namespace
{
   // some convenient globals

   const char* const g_profiler_filename = "profiler_results.csv";
   const char* const g_category_strings[] =
   {
      "Category1",
      "Category2",
      "Category3",
   };

   // this calculation is useful only if all strings are the same lengths
   const int g_NUM_CATEGORY_STRINGS = sizeof(g_category_strings) / sizeof(*g_category_strings);

   const int g_NUM_NORMAL_ENTRIES = 15;
}

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

// called "write nice profile data" because it doesn't cover any corner 
// cases, which I would call "not nice" cases, so this is a nice and 
// clean function to write basic data for my tests
void write_nice_profile_data(profiler& my_profiler)
{
   // add the categories to the profiler
   for (int index = 0; index < g_NUM_CATEGORY_STRINGS; index++)
   {
      my_profiler.add_category(g_category_strings[index]);
   }

   // write whole number float values to the file
   // Note: The "add category time log" function requires a float, but for 
   // simplicity of testing, we want to read a C string and pass it to atoi(...),
   // so only write whole numbers.
   for (float float_value_counter = 0;
      float_value_counter < g_NUM_NORMAL_ENTRIES;
      float_value_counter += g_NUM_CATEGORY_STRINGS)
   {
      my_profiler.new_frame();
      for (int index = 0; index < g_NUM_CATEGORY_STRINGS; index++)
      {
         my_profiler.add_category_time_log(g_category_strings[index], float_value_counter + index);
      }
   }
}


TEST(Profiler, Profile_Samples_Nice_Data)
{
   profiler my_profiler(g_profiler_filename);
   write_nice_profile_data(my_profiler);
   
   // write the data to file
   my_profiler.shutdown();

   // open the output file and check the data
   ifstream input(g_profiler_filename);

   // check the titles
   for (int index = 0; index < g_NUM_CATEGORY_STRINGS; index++)
   {
      EXPECT_EQ(get_next_token(input), g_category_strings[index]);
   }

   // check the values
   for (int value_counter = 0; value_counter < g_NUM_NORMAL_ENTRIES; value_counter++)
   {
      string buf = get_next_token(input);
      EXPECT_EQ(atoi(buf.c_str()), value_counter);
   }

   input.close();
}


TEST(Profiler, Profile_Incomplete_Samples)
{
   profiler my_profiler(g_profiler_filename);
   write_nice_profile_data(my_profiler);

   // add one more frame and only add data to some of the categories
   my_profiler.new_frame();
   my_profiler.add_category_time_log(g_category_strings[0], 23);
   my_profiler.add_category_time_log(g_category_strings[2], 54);

   // write the data to file
   my_profiler.shutdown();

   // all the other data was checked in the "nice samples" test, so fast
   // forward to the end and check the extra data
   ifstream input(g_profiler_filename);
   for (int token_counter = 0; 
      token_counter < g_NUM_CATEGORY_STRINGS + g_NUM_NORMAL_ENTRIES; 
      token_counter++)
   {
      string temp = get_next_token(input);
   }

   // check the last frame
   string buf = get_next_token(input);
   EXPECT_EQ(atoi(buf.c_str()), 23);
   buf = get_next_token(input);
   EXPECT_EQ(atoi(buf.c_str()), 0);
   buf = get_next_token(input);
   EXPECT_EQ(atoi(buf.c_str()), 54);

}


#endif