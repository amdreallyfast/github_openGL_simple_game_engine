// for the application that starts the Qt window stuff
#include <Qt\qapplication.h>

// for my custom Qt window, to which openGL will draw
#include "my_GL_window.h"

#include <Qt\qdebug.h>

int main(int argc, char **argv)
{
   // check the number of times that the CPU increments some counter (??which one??) every
   // second
   // Note: The value will be ~1000 times lower than your actual CPU frequency.  
   // For example, my processor cores on this laptop are ~2GHz appiece, but the
   // value that "query performance frequency" dumps into the variable is only
   // about 1.9 million.
   // Even so, this is much more granularity than milliseconds.
   LARGE_INTEGER max_cpu_sample_frequency;
   QueryPerformanceFrequency(&max_cpu_sample_frequency);

   LARGE_INTEGER start_time;
   LARGE_INTEGER end_time;
   QueryPerformanceCounter(&start_time);
   qDebug() << "Hello";
   QueryPerformanceCounter(&end_time);

   LARGE_INTEGER delta;
   delta.QuadPart = end_time.QuadPart - start_time.QuadPart;
   qDebug() << delta.QuadPart;

   // must create the application before the custom QGLWidget
   QApplication app(argc, argv);
   my_GL_window window;
   window.show();

   return app.exec();
}