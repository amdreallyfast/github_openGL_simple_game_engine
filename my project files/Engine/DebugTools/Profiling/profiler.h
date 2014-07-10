#ifndef DEBUG_PROVILER
#define DEBUG_PROVILER


#include <string>
using std::string;

class __declspec(dllexport) profiler
{
public:
   static profiler& get_instance();

#ifdef PROFILER_ON
   void reset();
   void new_frame();
   void add_category(const char* new_category);
   void add_category_time_log(const char* category, float time);
   void flush_to_fresh_file(const char* filename_to_profiler_output);
#else
   // if the flag is off, make these functions empty so that the compiler
   // will ignore any calls to these functions, saving the program from 
   // spending unnecessary CPU time performing debugging features
   void reset() {}
   void new_frame() {}
   void add_category(const char* new_category) {}
   void add_category_time_log(const char* category, float time) {}
   void flush_to_fresh_file(const char* filename_to_profiler_output) {}
#endif

   static const unsigned int MAX_FRAME_SAMPLES = 500;
   static const unsigned int MAX_PROFILER_CATEGORIES = 20;
private:
   profiler();
   profiler(const profiler&);
   profiler& operator=(const profiler&);

   // maintain a static instance of this class internally
   // Note: As a static data member, it is not bound to any instance of the
   // class, but as a result, the declaration here is not considered a 
   // definition.  That is, the declaration here says that the static value
   // exists, but it doesn't say where.  We will define it (that is, bring 
   // it into existance) in the source file for this class.
   static profiler m_the_instance;

   int m_frame_index;

   struct m_profile_category
   {
      const char* category_name;
      float samples[MAX_FRAME_SAMPLES];
   } m_profiler_categories[MAX_PROFILER_CATEGORIES];
};

#endif // DEBUG_PROVILER