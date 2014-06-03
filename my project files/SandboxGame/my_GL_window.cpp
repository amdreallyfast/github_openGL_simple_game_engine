// MUST include before Qt's GL libraries
#include "glew-1.10.0\include\GL\glew.h"

// could do assertion or exception (??change to exception??)
#include <cassert>

#include "my_GL_window.h"


void my_GL_window::initializeGL()
{
   GLenum err_code = glewInit();
   assert(err_code == 0);

   glGenBuffers(1, &m_vertex_buffer_ID);
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);

   float verts[] =
   {
      +0.0f, +0.1f,
      -0.1f, -0.1f,
      +0.1f, -0.1f,
   };

   glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(verts),
      reinterpret_cast<void *>(verts),
      GL_STATIC_DRAW);
}


void my_GL_window::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,             // vertex attribute index
      2,             // number of items per vertex
      GL_FLOAT,      // type of item (dictates number of bytes per item)
      GL_FALSE,      // no normalization
      0,             // vertex position values are closely packed
      0              // position values start 0 bytes from the beginning of the vertex array
      );

   glDrawArrays(
      GL_TRIANGLES,     // drawing mode
      0,                // start drawing with the first vertex in each vertex attribute object 
      3);               // number of vertices to draw
}
