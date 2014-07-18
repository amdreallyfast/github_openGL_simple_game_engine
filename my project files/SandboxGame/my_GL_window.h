#ifndef SANDBOX_GAME_GL_WINDOW
#define SANDBOX_GAME_GL_WINDOW

#include <QtCore\qobject>
#include <QtOpenGL\qglwidget>
#include <QtCore\qtimer>

class my_GL_window : public QGLWidget
{
   Q_OBJECT

public:
   bool shutdown();
   bool initialize();
   void handle_borders();
   void lerp_the_lerper();
   void update_velocity(float delta_time);
   void rotate_ship(float delta_time);

protected:
   // override QGLWidget functionality here
   void initializeGL();
   void paintGL();
   
private:
   bool m_ok_to_draw;
   QTimer m_qt_timer;

private slots:
   void timer_update();
};

#endif