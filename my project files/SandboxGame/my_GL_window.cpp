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
      vector2D(+0.0f, +0.1f, 1.0f),
      vector2D(-0.1f, -0.1f, 1.0f),
      vector2D(+0.1f, -0.1f, 1.0f),
   };
   const unsigned int NUM_VERTS = sizeof(g_verts) / sizeof(*g_verts);

   vector2D g_ship_position;

   // DO NOT MOVE THIS!!
   vector2D g_ship_rotation_point;

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
   int min_window_size = min(width(), height());

   vector2D viewport_location(
      (width() / 2) - (min_window_size / 2),
      (height() / 2) - (min_window_size / 2));
   glViewport(viewport_location.x, viewport_location.y, min_window_size, min_window_size);
   glClear(GL_COLOR_BUFFER_BIT);

   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,             // vertex attribute index
      3,             // number of items per vertex
      GL_FLOAT,      // type of item (dictates number of bytes per item)
      GL_FALSE,      // no normalization
      0,             // vertex position values are closely packed
      0              // position values start 0 bytes from the beginning of the vertex array
      );

   vector2D transformed_verts[NUM_VERTS];
   matrix2D rotation_matrix = matrix2D::rotate(g_ship_orientation_radians);
   matrix2D translation_matrix = matrix2D::translate(g_ship_position.x, g_ship_position.y);
   matrix2D transformation_matrix = translation_matrix * rotation_matrix;

   // make the new vector displacement for all the vertices that rotate around
   // the ship's rotation point
   vector2D displacement = matrix2D::get_displacement_vector_for_non_origin_rotation(g_ship_orientation_radians, g_ship_rotation_point);

   for (unsigned int i = 0; i < NUM_VERTS; i++)
   {
      transformed_verts[i] = (transformation_matrix * g_verts[i]) + displacement;
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

void my_GL_window::timer_update()
{
   // tell the timer to record its current counter value
   g_clock.new_frame();

   // do pre-render calculations
   
   // update ship status
   float delta_time_fractional_second = g_clock.time_elapsed_last_frame();
   rotate_ship(delta_time_fractional_second);
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
   
   // make rotation point the center of mass
   g_ship_rotation_point.x = (g_verts[0].x + g_verts[1].x + g_verts[2].x) / 3.0f;
   g_ship_rotation_point.y = (g_verts[0].y + g_verts[1].y + g_verts[2].y) / 3.0f;

   success = g_clock.initialize();
   if (!success){ return false; }

   return true;
}


// the "key is pressed" event handler
void my_GL_window::update_velocity(float delta_time)
{
   const float LINEAR_ACCEL = 0.2f;
   static float LINEAR_DELTA_V = LINEAR_ACCEL * delta_time;

   // the sine is negative because the ship orientation is relative to the veritcal
   // axis, NOT the horizontal axis
   //vector2D direction_to_accel(
   //   (-1) * sinf(g_ship_orientation_radians), 
   //   cosf(g_ship_orientation_radians));

   vector2D forward_for_my_ship(0, 1);
   matrix2D rotation_mat = matrix2D::rotate(g_ship_orientation_radians);
   vector2D direction_to_accel = rotation_mat * forward_for_my_ship;

   if (GetAsyncKeyState(VK_UP))
   {
      g_ship_velocity += direction_to_accel * LINEAR_DELTA_V;
   }
}


void my_GL_window::rotate_ship(float delta_time)
{
   const float ANGULAR_ACCEL = 2.0f;
   static float angular_delta_v = 0;

   if (GetAsyncKeyState(VK_LEFT))
   {
      // recall that positive rotation is counterclockwise
      angular_delta_v += (ANGULAR_ACCEL * delta_time);
   }
   if (GetAsyncKeyState(VK_RIGHT))
   {
      angular_delta_v -= (ANGULAR_ACCEL * delta_time);
   }

   float angular_delta_rotation = (angular_delta_v * delta_time);
   g_ship_orientation_radians += angular_delta_rotation;
}


