#include "profiler.h"

// this is where the static class member exists
profiler profiler::m_the_instance;

profiler::profiler()
{
   reset();
}

profiler& profiler::get_instance()
{
   return m_the_instance;
}

#ifdef PROFILER_ON
#include <cassert>

#include <fstream>
using std::ofstream;
using std::ios;

void profiler::reset()
{
   m_frame_index = -1;
   memset(m_profiler_categories, 0, sizeof(m_profiler_categories));
}

void profiler::new_frame()
{
   // move on to the next line
   m_frame_index += 1;
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

   // check that the frame index is valid
   assert(m_frame_index >= 0);

   pc_ptr->samples[m_frame_index % MAX_FRAME_SAMPLES] = time;
}

void profiler::flush_to_fresh_file(const char* filename_to_profiler_output)
{
   // open the file, and empty it out if it already exists
   ofstream out_stream(filename_to_profiler_output, ios::trunc);
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
   // Note: If we haven't wrapped around, start at 0 and go to the latest frame 
   // index.  If we have exceeded the max number of frame indexes (that is, 
   // wrapped around), then start at 0 and go until the max possible frame index.
   int max_frame_index = (m_frame_index < MAX_FRAME_SAMPLES) ? m_frame_index : (MAX_FRAME_SAMPLES - 1);

   // about the <= end condition
   // Note: To make things simple, I will simply record all the data.  The 
   // tutorial jumped through some hoops in an attempt to not record incomplete 
   // frames, and there were some particularly nasty hoops for wrap-around 
   // incomplete frames.  I am skipping that by simply recording all frames.
   for (int frame_index = 0; frame_index <= max_frame_index; frame_index++)
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

   // close the file 
   out_stream.close();
}

#endif