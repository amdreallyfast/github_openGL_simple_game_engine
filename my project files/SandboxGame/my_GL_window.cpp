// MUST include before Qt's GL libraries
#include "glew-1.10.0\include\GL\glew.h"
#include "my_GL_window.h"

// for printing errors to the console; use instead of cout (whim)
#include <QtCore\QDebug>

// could do assertion or exception (??change to exception??)
#include <cassert>

// for my custom vector structure
#include <math\Vector2D.h>
using Math::Vector2D;

// for my custom matrix structure
#include <math\Matrix2D.h>
using Math::Matrix2D;

// for our timer that allows for precise control of where things should be 
// within a frame independent of frame rendering time
#include "timing\clock.h"
using Timing::Clock;

// for our profiler
#include "DebugTools\Profiling\profiler.h"
using Profiling::Profiler;


// the unnamed namespace makes everything here private to this file, so we don't
// have to use the "static" keyword on all these globals
//??is this even a good idea??
namespace
{
   Vector2D g_ship_verts[] =
   {
      // as far as the compiler is concerned, these are adjacent pairs of floats
      // in memory, so your vertex attribute and buffer data specifications are 
      // the same as if you only entered float values here
      Vector2D(+0.0f, +0.1f, 1.0f),
      Vector2D(-0.1f, -0.1f, 1.0f),
      Vector2D(+0.1f, -0.1f, 1.0f),
   };
   const unsigned int g_NUM_SHIP_VERTS = sizeof(g_ship_verts) / sizeof(*g_ship_verts);
   GLuint g_ship_vertex_buffer_ID;

   Vector2D g_ship_position;
   float g_ship_orientation_radians = 0;
   Vector2D g_ship_rotation_point;     // DO NOT TRANSLATE THIS!!
   Vector2D g_ship_velocity;


   Vector2D g_border_verts[] = 
   {
      // build a diamond shape
      Vector2D(+0.0f, +1.0f),    // center of top
      Vector2D(-1.0f, -0.0f),    // center of left
      Vector2D(+0.0f, -1.0f),    // center of bottom
      Vector2D(+1.0f, +0.0f),    // center of right
   };
   const unsigned int g_NUM_BORDER_VERTS = sizeof(g_border_verts) / sizeof(*g_border_verts);
   GLuint g_border_vertex_buffer_ID;

   Vector2D g_lerp_verts[] =
   {
      Vector2D(+0.5f, +0.5f),
      Vector2D(-0.5f, +0.5f),
      Vector2D(-0.5f, -0.5f),
      Vector2D(+0.5f, -0.5f),
   };
   const unsigned int g_NUM_LERP_POINTS = sizeof(g_lerp_verts) / sizeof(*g_lerp_verts);


   Clock g_clock;

   Profiler& g_profiler = Profiler::get_instance();
}


void my_GL_window::initializeGL()
{
   GLenum err_code = glewInit();
   assert(err_code == 0);

   glGenBuffers(1, &g_ship_vertex_buffer_ID);
   glBindBuffer(GL_ARRAY_BUFFER, g_ship_vertex_buffer_ID);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_ship_verts), NULL, GL_DYNAMIC_DRAW);

   glGenBuffers(1, &g_border_vertex_buffer_ID);
   glBindBuffer(GL_ARRAY_BUFFER, g_border_vertex_buffer_ID);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_border_verts), g_border_verts, GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // make the timer go as fast as it can
   // Note: Argument values to the qt timer are in milliseconds.
   connect(&m_qt_timer, SIGNAL(timeout()), this, SLOT(timer_update()));
   m_qt_timer.start(0);
}


void my_GL_window::paintGL()
{
   if (!m_ok_to_draw)
   {
      return;
   }

   int min_window_size = min(width(), height());

   //Vector2D viewport_location(
   //   (width() / 2) - (min_window_size / 2),
   //   (height() / 2) - (min_window_size / 2));
   //glViewport(viewport_location.x, viewport_location.y, min_window_size, min_window_size);
   glViewport(0, 0, width(), height());
   glClear(GL_COLOR_BUFFER_BIT);

   glBindBuffer(GL_ARRAY_BUFFER, g_ship_vertex_buffer_ID);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,             // vertex attribute index
      3,             // number of items per vertex
      GL_FLOAT,      // type of item (dictates number of bytes per item)
      GL_FALSE,      // no normalization
      0,             // vertex position values are closely packed
      0              // position values start 0 bytes from the beginning of the vertex array
      );

   g_clock.stopwatch_start();

   Vector2D transformed_verts[g_NUM_SHIP_VERTS];
   Matrix2D rotation_matrix = Matrix2D::rotate(g_ship_orientation_radians);
   Matrix2D translation_matrix = Matrix2D::translate(g_ship_position.x, g_ship_position.y);

   float aspect_ratio = static_cast<float>(width()) / height();
   Matrix2D scale_matrix;
   if (aspect_ratio > 1.0f)
   {
      scale_matrix = Matrix2D::scale(1 / aspect_ratio, 1);
   }
   else
   {
      scale_matrix = Matrix2D::scale(1, aspect_ratio);
   }

   Matrix2D transformation_matrix = translation_matrix * scale_matrix * rotation_matrix;

   // make the new vector displacement for all the vertices that rotate around
   // the ship's rotation point
   Vector2D displacement = Matrix2D::get_displacement_vector_for_non_origin_rotation(g_ship_orientation_radians, g_ship_rotation_point);

   for (unsigned int i = 0; i < g_NUM_SHIP_VERTS; i++)
   {
      transformed_verts[i] = (transformation_matrix * g_ship_verts[i]) + displacement;
   }

   float vertex_transformation_time = g_clock.stopwatch_stop_and_return_delta_time();
   g_profiler.add_category_time_log("Ship Vertex Transformation", vertex_transformation_time);


   g_clock.stopwatch_start();
   glBufferSubData(
      GL_ARRAY_BUFFER,
      0,                         // offset from start of data pointer is 0
      sizeof(transformed_verts),
      transformed_verts);

   glDrawArrays(
      GL_TRIANGLES,     // drawing mode
      0,                // start drawing with the first vertex in each vertex attribute object 
      g_NUM_SHIP_VERTS);// number of vertices to draw

   float ship_draw_time = g_clock.stopwatch_stop_and_return_delta_time();
   g_profiler.add_category_time_log("Ship Drawing", ship_draw_time);


   g_clock.stopwatch_start();
   glBindBuffer(GL_ARRAY_BUFFER, g_border_vertex_buffer_ID);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,             // vertex attribute index
      3,             // number of items per vertex
      GL_FLOAT,      // type of item (dictates number of bytes per item)
      GL_FALSE,      // no normalization
      0,             // vertex position values are closely packed
      0              // position values start 0 bytes from the beginning of the vertex array
      );
   glDrawArrays(GL_LINE_LOOP, 0, g_NUM_BORDER_VERTS);
   float border_draw_time = g_clock.stopwatch_stop_and_return_delta_time();
   g_profiler.add_category_time_log("Border Drawing", ship_draw_time);


   // don't draw again until the next timer update
   m_ok_to_draw = false;
}

void my_GL_window::timer_update()
{
   // tell the timer to record its current counter value
   g_clock.new_frame();

   // tell the profiler that it's next data will be for a new frame
   g_profiler.new_frame();

   // do pre-render calculations
   
   // update ship status
   float delta_time_fractional_second = g_clock.delta_time_last_frame();
   rotate_ship(delta_time_fractional_second);
   update_velocity(delta_time_fractional_second);
   g_ship_position += (g_ship_velocity * delta_time_fractional_second);
   
   // do borders after the velocity update due to time because the borders may
   // reverse of arrest the velocity
   handle_borders();

   //lerp_the_lerper();

   m_ok_to_draw = true;
   this->repaint();
}


bool my_GL_window::shutdown()
{
   bool success;

   success = g_clock.shutdown();
   if (!success){ return false; }

   g_profiler.flush_to_file("profiler_log.csv");

   return true;
}


// initialize non-Qt and non-openGL code here
bool my_GL_window::initialize()
{
   bool success;
   
   // make rotation point the center of mass
   g_ship_rotation_point.x = (g_ship_verts[0].x + g_ship_verts[1].x + g_ship_verts[2].x) / 3.0f;
   g_ship_rotation_point.y = (g_ship_verts[0].y + g_ship_verts[1].y + g_ship_verts[2].y) / 3.0f;

   success = g_clock.initialize();
   if (!success){ return false; }

   g_profiler.add_category("Ship Vertex Transformation");
   g_profiler.add_category("Ship Drawing");
   g_profiler.add_category("Border Drawing");
   g_profiler.new_frame();

   m_ok_to_draw = false;

   return true;
}


void my_GL_window::handle_borders()
{
   for (int index = 0; index < g_NUM_BORDER_VERTS; index++)
   {
      const Vector2D& first = g_border_verts[index];
      const Vector2D& second = g_border_verts[(index + 1) % g_NUM_BORDER_VERTS];
      Vector2D border = second - first;
      Vector2D respective_position = g_ship_position - first;

      Vector2D border_normal = border.get_ccw_perpendicular_vector();
      float dot_result = border_normal.dot(respective_position);
      if (dot_result < 0)
      {
         g_ship_velocity += (-2) * g_ship_velocity.project_onto(border_normal);
      }
   }
}


void my_GL_window::lerp_the_lerper()
{
   static int source_lerp_index = 0;
   static int dest_lerp_index = 1;
   static float alpha = 0;

   alpha += g_clock.delta_time_last_frame();
   if (alpha >= 1.0f)
   {
      alpha = 0.0f;
      source_lerp_index = dest_lerp_index;
      dest_lerp_index = (dest_lerp_index + 1) % g_NUM_LERP_POINTS;
   }

   const Vector2D& source = g_lerp_verts[source_lerp_index];
   const Vector2D& dest = g_lerp_verts[dest_lerp_index];
   Vector2D current_lerp_position = lerp(source, dest, alpha);
   g_ship_position = current_lerp_position;
}


void my_GL_window::update_velocity(float delta_time)
{
   const float LINEAR_ACCEL = 0.2f;
   static float LINEAR_DELTA_V = LINEAR_ACCEL * delta_time;

   // the sine is negative because the ship orientation is relative to the veritcal
   // axis, NOT the horizontal axis
   //Vector2D direction_to_accel(
   //   (-1) * sinf(g_ship_orientation_radians), 
   //   cosf(g_ship_orientation_radians));

   Vector2D forward_for_my_ship(0, 1);
   Matrix2D rotation_mat = Matrix2D::rotate(g_ship_orientation_radians);
   Vector2D direction_to_accel = rotation_mat * forward_for_my_ship;

   if (GetAsyncKeyState(VK_UP))
   {
      g_ship_velocity += direction_to_accel * LINEAR_DELTA_V;
   }
}


void my_GL_window::rotate_ship(float delta_time)
{
   const float ANGULAR_ACCEL = 3.0f;
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


