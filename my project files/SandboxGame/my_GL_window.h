#pragma once

#include <QtOpenGL\qglwidget>

class my_GL_window : public QGLWidget
{
protected:
   // override the initialization
   void initializeGL();
};

