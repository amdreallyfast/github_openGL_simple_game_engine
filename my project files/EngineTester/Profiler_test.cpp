#include <gtest\gtest.h>

#include "DebugTools\Profiling\profiler.h"
using Profiling::Profiler;

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
   const int g_FULL_SAMPLE_COUNT = g_NUM_CATEGORY_STRINGS * Profiler::MAX_FRAME_SAMPLES;

   Profiler& g_profiler_for_all_tests = Profiler::get_instance();
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


// writes sequential data to the profiler for all categories up to the number
// of requested samples
void write_samples(int num_samples)
{
   g_profiler_for_all_tests.reset();

   // write whole number float values to the file
   // Note: The "add category time log" function requires a float, but for 
   // simplicity of testing, we want to read a C string and pass it to atoi(...),
   // so only write whole numbers.
   float value_counter = 0.0;
   int category_index = 0;

   // add the categories to the profiler
   for (category_index = 0; category_index < g_NUM_CATEGORY_STRINGS; category_index++)
   {
      g_profiler_for_all_tests.add_category(g_category_strings[category_index]);
   }

   // add a new value to every category up until the number of requested samples
   for (value_counter = 0, category_index = 0;
      value_counter < num_samples;
      value_counter++, category_index++)
   {
      if (0 == (category_index % g_NUM_CATEGORY_STRINGS))
      {
         g_profiler_for_all_tests.new_frame();
      }

      g_profiler_for_all_tests.add_category_time_log(
         g_category_strings[category_index % g_NUM_CATEGORY_STRINGS],
         value_counter);
   }

   // write the data to file
   g_profiler_for_all_tests.flush_to_fresh_file(g_profiler_filename);
}


// check for sequential data in the file for all categories up to the number
// of requested samples
// Note: The in-file-stream must be at the beginning of the file, or else 
// this check won't work
void check_samples(int num_samples)
{
   ifstream in_file_stream(g_profiler_filename);

   // check the titles
   for (int index = 0; index < g_NUM_CATEGORY_STRINGS; index++)
   {
      EXPECT_EQ(get_next_token(in_file_stream), g_category_strings[index]);
   }

   // check the values
   // Note: If there is any wrap around (that is, the number of samples 
   // written exceeds the max number of available frame samples), account 
   // for it.

   // if the sample frames for all categories are full, then there is no
   // wrap around, but if it is 1 beyond that, there is a wrap around
   int num_wrap_arounds = (num_samples - 1) / g_FULL_SAMPLE_COUNT;

   if (0 == num_wrap_arounds)
   {
      // simple case
      for (int value_counter = 0; value_counter < num_samples; value_counter++)
      {
         string buf = get_next_token(in_file_stream);
         EXPECT_EQ(atoi(buf.c_str()), value_counter);
      }
   }
   else
   {
      // number of wrap arounds > 0, so pick off the first set of values up
      // until the max sample count, then check the remainder that were left
      // over from the previous set of recordings

      int min_value = num_wrap_arounds * g_FULL_SAMPLE_COUNT;
      int max_value = num_samples - 1;
      for (int value_counter = min_value; value_counter <= max_value; value_counter++)
      {
         string buf = get_next_token(in_file_stream);
         EXPECT_EQ(atoi(buf.c_str()), value_counter);
      }

      // now pick off the remaining values
      // Ex: MAX_FRAME_SAMPLES is 10, and there are 13 samples, so the max 
      // sample value will be 12, and there will be 1 wrap around.  The min value
      // after the 13 will be 3 (0, 1, and 2 were overwritten by 10, 11, and 12).  I
      // won't try to explain the following equations because it will take too long, 
      // but they work.
      min_value = (num_wrap_arounds - 1) * g_FULL_SAMPLE_COUNT
         + (num_samples % g_FULL_SAMPLE_COUNT);
      max_value = num_wrap_arounds * g_FULL_SAMPLE_COUNT;
      for (int value_counter = min_value; value_counter < max_value; value_counter++)
      {
         string buf = get_next_token(in_file_stream);
         EXPECT_EQ(atoi(buf.c_str()), value_counter);
      }
   }

   in_file_stream.close();
}


TEST(Profiler, Small_Sample_Count_Nice_Data)
{
   // test samples such that they are evenly divisible by the number of
   // categories (that is, all completed frames)
   int num_samples_to_use = g_NUM_CATEGORY_STRINGS * 5;

   write_samples(num_samples_to_use);
   check_samples(num_samples_to_use);
}


TEST(Profiler, Incomplete_Frame)
{
   // test samples that is 1 more than the number of categories so
   // that you will have an incomplete frame
   int num_samples_to_use = g_NUM_CATEGORY_STRINGS * 5;
   num_samples_to_use += 1;

   write_samples(num_samples_to_use);
   check_samples(num_samples_to_use);
}


TEST(Profiler, Large_Sample_Count_Boundaries)
{
   // go right up to a before edge of the 
   // sample limit
   int num_samples_to_use = g_NUM_CATEGORY_STRINGS * Profiler::MAX_FRAME_SAMPLES;

   // check just before the boundary of a full sample set
   write_samples(num_samples_to_use - 1);
   check_samples(num_samples_to_use - 1);

   // check the exact boundary for a full sample set
   write_samples(num_samples_to_use);
   check_samples(num_samples_to_use);

   // the just beyond the boundary
   write_samples(num_samples_to_use + 1);
   check_samples(num_samples_to_use + 1);
}

TEST(Profiler, Large_Sample_Count_Circulating_Once_Plus_Some)
{
   // go past the edge of the sample limit and go a bit beyond
   int num_samples_to_use = g_NUM_CATEGORY_STRINGS * Profiler::MAX_FRAME_SAMPLES;
   num_samples_to_use += (g_NUM_CATEGORY_STRINGS * Profiler::MAX_FRAME_SAMPLES) / 2;

   write_samples(num_samples_to_use);
   check_samples(num_samples_to_use);
}

TEST(Profiler, Large_Sample_Count_Go_Around_Several_Times)
{
   // go around the sample limit more than once
   int num_samples_to_use = 3 * g_NUM_CATEGORY_STRINGS * Profiler::MAX_FRAME_SAMPLES;

   write_samples(num_samples_to_use + 1);
   check_samples(num_samples_to_use + 1);
}


#endif