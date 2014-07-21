// for the application that starts the Qt window stuff
#include <QtGui\QApplication>

// for my custom Qt window, to which openGL will draw
#include "my_GL_window.h"

#include "My_Game.h"

int main(int argc, char **argv)
{
   // must create the application before the custom QGLWidget
   QApplication app(argc, argv);

   My_Game my_game;
   if (!my_game.initialize()) { return -1; }
   my_game.go();

   // run the application
   int app_err_code = app.exec();

   if (!my_game.shutdown()) { app_err_code |= 1; }

   return app_err_code;
}