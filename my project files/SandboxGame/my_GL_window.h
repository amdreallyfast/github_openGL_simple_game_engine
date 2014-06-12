#pragma once

#include <QtCore\qobject>
#include <QtOpenGL\qglwidget>
#include <QtCore\qtimer>

class my_GL_window : public QGLWidget
{
   Q_OBJECT

public:
   bool shutdown();
   bool initialize();
   void update_velocity(float delta_time);

protected:
   // override QGLWidget functionality here
   void initializeGL();
   void paintGL();
   
private:
   GLuint m_vertex_buffer_ID;
   QTimer m_qt_timer;

private slots:
   void timer_update();
};

