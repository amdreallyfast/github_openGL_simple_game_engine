#pragma once

#include <QtOpenGL\qglwidget>

class my_GL_window : public QGLWidget
{
protected:
   // override the initialization
   void initializeGL();

   // override the "paint things" method
   void paintGL();
   
private:
   GLuint m_vertex_buffer_ID;
};

