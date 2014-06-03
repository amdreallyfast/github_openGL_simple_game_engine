#include <Qt\qapplication.h>

#include "my_GL_window.h"

int main(int argc, char **argv)
{
   int app_ret_val = 0;
   QApplication app(argc, argv);
   my_GL_window window;

   window.show();

   app_ret_val = app.exec();

   return app_ret_val;
}