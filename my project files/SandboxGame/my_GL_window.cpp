// MUST include before Qt's GL libraries
#include "glew-1.10.0\include\GL\glew.h"
#include "my_GL_window.h"

// for key presses
// Note: I am able to declare the class QKeyEvent as a parameter without
// this include because it is declared somewhere in the Qt include 
// hierarchy, but it is not fully defined there.  This was to save space
// and prevent header files from getting bloated.  Bottom line to me though 
// is that I need to include this file to get the definition of the class.
#include <QtGui\QKeyEvent>

// for printing errors to the console; use instead of cout (whim)
#include <Qt\qdebug.h>

// could do assertion or exception (??change to exception??)
#include <cassert>

// for my custom vector structure
#include <math\vector2D.h>
using Math::vector2D;

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

   // use the default values of 0 for the chip position
   vector2D g_ship_position;

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
   // tell the timer to record its current counter value
   g_clock.new_frame();

   // begin pre-render calculations

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
void my_GL_window::keyPressEvent(QKeyEvent* e)
{
   // Note: Enums do not provide any level of scope except for the latest
   // version of C++, which Visual Studio 2013 Express does not support at
   // the time of this coding.  Because of the lack of scope, all the key
   // enumes are prefixed with "Key_" even though they are already in the
   // "Key" namespace.
   const float SHIP_VELOCITY = 0.02f;
   if (Qt::Key_Up == e->key())
   {
      g_ship_position.y += SHIP_VELOCITY;
   }
   if (Qt::Key_Down == e->key())
   {
      g_ship_position.y -= SHIP_VELOCITY;
   }
   if (Qt::Key_Left == e->key())
   {
      g_ship_position.x -= SHIP_VELOCITY;
   }
   if (Qt::Key_Right == e->key())
   {
      g_ship_position.x += SHIP_VELOCITY;
   }
}