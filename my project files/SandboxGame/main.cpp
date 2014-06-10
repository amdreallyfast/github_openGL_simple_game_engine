// for the application that starts the Qt window stuff
#include <Qt\qapplication.h>

// for my custom Qt window, to which openGL will draw
#include "my_GL_window.h"

#include <Qt\qdebug.h>

int main(int argc, char **argv)
{
   // must create the application before the custom QGLWidget
   QApplication app(argc, argv);
   my_GL_window window;
   window.show();

   return app.exec();
}