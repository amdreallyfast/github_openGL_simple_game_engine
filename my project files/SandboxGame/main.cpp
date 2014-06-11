// for the application that starts the Qt window stuff
#include <Qt\qapplication.h>

// for my custom Qt window, to which openGL will draw
#include "my_GL_window.h"

#include <Qt\qdebug.h>

int main(int argc, char **argv)
{
   // must create the application before the custom QGLWidget
   QApplication app(argc, argv);
   
   // make the custom QGLWidget
   my_GL_window window;
   window.initialize();
   window.show();

   // run the application
   int app_err_code = app.exec();

   // shut down my custom QGLWidget code
   if (!window.shutdown())
   {
      // put in a non-zero value (a bit hand-wavy here)
      app_err_code |= 1;
   }

   return app_err_code;
}