#ifndef DEBUG_PROVILER
#define DEBUG_PROVILER


class profiler
{
public:
   void add_entry(const char* category, float time);
   void new_frame();
   
   void initialize();
   void shutdown();
};

#endif // DEBUG_PROVILER