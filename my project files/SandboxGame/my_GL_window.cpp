// MUST include before Qt's GL libraries
#include "glew-1.10.0\include\GL\glew.h"
#include "my_GL_window.h"

// for printing errors to the console; use instead of cout (whim)
#include <QtCore\QDebug>

// could do assertion or exception (??change to exception??)
#include <cassert>

// for my custom vector structure
#include <math\vector2D.h>
using Math::vector2D;

// for my custom matrix structure
#include <math\matrix2D.h>
using Math::matrix2D;

// for our timer that allows for precise control of where things should be 
// within a frame independent of frame rendering time
#include <timing\clock.h>
using Timing::Clock;


// the unnamed namespace makes everything here private to this file, so we don't
// have to use the "static" keyword on all these globals
//??is this even a good idea??
namespace
{
   vector2D g_verts[] =
   {
      // as far as the compiler is concerned, these are adjacent pairs of floats
      // in memory, so your vertex attribute and buffer data specifications are 
      // the same as if you only entered float values here
      vector2D(+0.0f, +0.2f),
      vector2D(-0.05f, -0.1f),
      vector2D(+0.05f, -0.1f),
   };
   const unsigned int NUM_VERTS = sizeof(g_verts) / sizeof(*g_verts);

   // use the default values of 0 for the vectors
   vector2D g_ship_position;
   float g_ship_orientation_radians = 0;
   vector2D g_ship_velocity;

   Clock g_clock;
}


void my_GL_window::initializeGL()
{
   GLenum err_code = glewInit();
   assert(err_code == 0);

   glGenBuffers(1, &m_vertex_buffer_ID);
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
   glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(g_verts),
      NULL,
      GL_DYNAMIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // make the timer go as fast as it can
   connect(&m_qt_timer, SIGNAL(timeout()), this, SLOT(timer_update()));
   m_qt_timer.start(0);
}


void my_GL_window::paintGL()
{
   glViewport(0, 0, this->width(), this->height());
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,             // vertex attribute index
      2,             // number of items per vertex
      GL_FLOAT,      // type of item (dictates number of bytes per item)
      GL_FALSE,      // no normalization
      0,             // vertex position values are closely packed
      0              // position values start 0 bytes from the beginning of the vertex array
      );

   vector2D transformed_verts[NUM_VERTS];
   matrix2D rotation_matrix = matrix2D::rotate(g_ship_orientation_radians);
   for (unsigned int i = 0; i < NUM_VERTS; i++)
   {
      transformed_verts[i] = rotation_matrix * g_verts[i];
   }
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
   glBufferSubData(
      GL_ARRAY_BUFFER,
      0,                         // offset from start of data pointer is 0
      sizeof(transformed_verts),
      transformed_verts);

   glDrawArrays(
      GL_TRIANGLES,     // drawing mode
      0,                // start drawing with the first vertex in each vertex attribute object 
      3);               // number of vertices to draw

   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int debug_int = 1;
void my_GL_window::timer_update()
{
   // tell the timer to record its current counter value
   g_clock.new_frame();

   // do pre-render calculations
   
   // update ship status
   rotate_ship();

   float delta_time_fractional_second = g_clock.time_elapsed_last_frame();
   update_velocity(delta_time_fractional_second);
   g_ship_position += (g_ship_velocity * delta_time_fractional_second);

   this->repaint();
}


bool my_GL_window::shutdown()
{
   bool success;

   success = g_clock.shutdown();
   if (!success){ return false; }

   return true;
}


// initialize non-Qt and non-openGL code here
bool my_GL_window::initialize()
{
   bool success;
   
   success = g_clock.initialize();
   if (!success){ return false; }

   return true;
}


// the "key is pressed" event handler
void my_GL_window::update_velocity(float delta_time)
{

   const float ACCELERATION = 0.3f * delta_time;
   //if (GetAsyncKeyState(VK_UP))
   //{
   //   g_ship_velocity.y += ACCELERATION;
   //}
}

void my_GL_window::rotate_ship()
{
   const float ANGLULAR_ACCEL = 0.1f;

   if (GetAsyncKeyState(VK_LEFT))
   {
      // recall that positive rotation is counterclockwise
      g_ship_orientation_radians += ANGLULAR_ACCEL;
   }
   if (GetAsyncKeyState(VK_RIGHT))
   {
      g_ship_orientation_radians -= ANGLULAR_ACCEL;
   }
}


