#include "profiler.h"

#include <cassert>

#include <fstream>
using std::ofstream;
using std::ios;

profiler::profiler(const char* filename_to_profiler_output) :
   m_filename(filename_to_profiler_output),

   // start this out at -1 so that the first "new frame" call will set it to 0
   m_frame_index(-1)
{
   memset(m_profiler_categories, 0, sizeof(m_profiler_categories));
}

void profiler::shutdown()
{
   // open the file, and empty it out if it already exists
   ofstream out_stream(m_filename, ios::trunc);
   m_profile_category* pc_ptr = 0;

   // write the category names to the top of the file
   for (int category_index = 0; category_index < MAX_PROFILER_CATEGORIES; category_index++)
   {
      pc_ptr = m_profiler_categories + category_index;

      // categories are added sequentially, and there is no method to remove them, 
      // so if the pointer to the category name is 0, then we have gone through 
      // all categories
      if (0 == pc_ptr->category_name)
      {
         break;
      }

      // category exists here, so write the name to file
      out_stream << pc_ptr->category_name << ",";
   }
   out_stream << "\n";

   // write the time data to the file column by column
   for (int frame_index = 0; frame_index < m_frame_index; frame_index++)
   {
      for (int category_index = 0; category_index < MAX_PROFILER_CATEGORIES; category_index++)
      {
         pc_ptr = m_profiler_categories + category_index;
         if (0 == pc_ptr->category_name)
         {
            break;
         }

         // category exists here, so write the sample data to file
         out_stream << pc_ptr->samples[frame_index] << ",";
      }

      // end the row with a new line
      out_stream << "\n";
   }
}

void profiler::new_frame()
{
   // move on to the next line
   m_frame_index += 1;
   assert(m_frame_index < MAX_FRAME_SAMPLES);
}

void profiler::add_category(const char* new_category)
{
   int index = 0;
   for (index = 0; index < MAX_PROFILER_CATEGORIES; index++)
   {
      m_profile_category* pc_ptr = m_profiler_categories + index;
      if (0 == pc_ptr->category_name)
      {
         // not assigned yet
         pc_ptr->category_name = new_category;
         break;
      }
   }

   // did we go through the list without finding one?
   // Note: Read, "check that "index" does not match "max profiler categories" ".
   assert(index != MAX_PROFILER_CATEGORIES);
}

void profiler::add_category_time_log(const char* category, float time)
{
   m_profile_category* pc_ptr = 0;

   int index = 0;
   for (index = 0; index < MAX_PROFILER_CATEGORIES; index++)
   {
      pc_ptr = m_profiler_categories + index;
      if (category == pc_ptr->category_name)
      {
         break;
      }
   }

   // did we go through the list without finding one?
   assert(index != MAX_PROFILER_CATEGORIES);

   pc_ptr->samples[m_frame_index] = time;
}

