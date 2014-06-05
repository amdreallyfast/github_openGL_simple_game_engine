// MUST include before Qt's GL libraries
#include "glew-1.10.0\include\GL\glew.h"
#include "my_GL_window.h"

// could do assertion or exception (??change to exception??)
#include <cassert>

#include <math\vector2D.h>
using MATH::vector2D;

#include <Qt\qdebug.h>

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
   vector2D g_ship_position(0.0f, 0.0f);
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
   glClear(GL_COLOR_BUFFER_BIT);

   // MUST bind the buffer before specifying attributes because the attribute
   // data is stored in the buffer object, and the drawing functions access the
   // buffer object that is bound to the context for both the vertex data and 
   // the vertex attribute data
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

   vector2D translated_verts[NUM_VERTS];
   for (unsigned int i = 0; i < NUM_VERTS; i++)
   {
      translated_verts[i] = g_verts[i] + g_ship_position;
   }
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
   glBufferSubData(
      GL_ARRAY_BUFFER,
      0,                         // offset from start of data pointer is 0
      sizeof(translated_verts), 
      translated_verts);

   glDrawArrays(
      GL_TRIANGLES,     // drawing mode
      0,                // start drawing with the first vertex in each vertex attribute object 
      3);               // number of vertices to draw

   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int debug_int = 1;
void my_GL_window::timer_update()
{
   if (debug_int++ % 20 == 0)
   {
      // force a hiccup to show what happens if too much stuff happens between 
      // frames
      for (int i = 0; i < 10000; i++)
      {
         qDebug() << "hello: " << debug_int;
      }
   }

   vector2D velocity(0.01f, 0.01f);
   g_ship_position = g_ship_position + velocity;

   this->repaint();
}
