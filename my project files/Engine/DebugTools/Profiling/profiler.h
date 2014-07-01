#ifndef DEBUG_PROVILER
#define DEBUG_PROVILER


#include <string>
using std::string;

class __declspec(dllexport) profiler
{
public:
   profiler(const char* filename_to_profiler_output);

   void shutdown();

   void new_frame();

   void add_category(const char* new_category);
   void add_category_time_log(const char* category, float time);

private:
   const char* m_filename;
   unsigned int m_frame_index;

   static const unsigned int MAX_FRAME_SAMPLES = 500;
   static const unsigned int MAX_PROFILER_CATEGORIES = 20;
   struct m_profile_category
   {
      const char* category_name;
      float samples[MAX_FRAME_SAMPLES];
   } m_profiler_categories[MAX_PROFILER_CATEGORIES];
};

#endif // DEBUG_PROVILER