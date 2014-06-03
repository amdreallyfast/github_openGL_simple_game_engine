#pragma once

#include <QtCore\qobject>
#include <QtOpenGL\qglwidget>
#include <QtCore\qtimer>


class my_GL_window : public QGLWidget
{
   Q_OBJECT

protected:
   // override the initialization
   void initializeGL();

   // override the "paint things" method
   void paintGL();
   
private:
   GLuint m_vertex_buffer_ID;
   QTimer m_qt_timer;

private slots:
   void timer_update();
};

