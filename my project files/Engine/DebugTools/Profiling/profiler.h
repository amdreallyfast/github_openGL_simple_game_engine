#ifndef DEBUG_PROVILER
#define DEBUG_PROVILER


class __declspec(dllexport) profiler
{
public:
   void add_entry(const char* category, float time);
   void new_frame();
   
   void initialize(const char* filename);
   void shutdown();
};

#endif // DEBUG_PROVILER