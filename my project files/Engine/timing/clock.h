#pragma once

namespace Timing
{
   // the "__declspec(dllexport)" is Microsoft's way of modifying the class
   // declaration so that it will be exported into a library that is external to
   // this dll project
   class __declspec(dllexport) Clock
   {
   public:
      bool initialize();
      bool shutdown();
      void new_frame();
      float time_elapsed_last_frame() const;
   };
}
