// must be included first
#include <glew-1.10.0\include\GL\glew.h>

#include "Renderer.h"
#include <cassert>

#include "Math\Vector2D.h"
using Math::Vector2D;

#include <Math\matrix2D.h>
using Math::Matrix2D;


namespace Rendering
{
   bool Renderer::initialize()
   {
      // Note: These are unsigned ints, so "-1" == max unsigned int.
      m_vertex_buffer_ID = -1;
      m_index_buffer_ID = -1;

      m_num_current_geometries = 0;
      m_num_current_renderables = 0;

      
      // display the window
      this->show();

      return true;
   }


   bool Renderer::shutdown()
   {
      if (m_index_buffer_ID != -1)
      {
         glDeleteBuffers(1, &m_index_buffer_ID);
      }

      if (m_vertex_buffer_ID != 1)
      {
         glDeleteBuffers(1, &m_vertex_buffer_ID);
      }

      return true;
   }


   Geometry* Renderer::add_geometry(
      Vector2D* verts, uint num_verts,
      ushort* indices, uint num_indices,
      GLenum render_mode)
   {
      assert(m_num_current_geometries != m_MAX_GEOMETRIES);
      assert(num_verts <= m_MAX_VERTS);
      Geometry& g = m_geometries[m_num_current_geometries++];
      g.verts = verts;
      g.num_verts = num_verts;
      g.indices = indices;
      g.num_indices = num_indices;
      g.render_mode = render_mode;

      return &g;
   }


   Renderable* Renderer::add_renderable(Geometry* geometry)
   {
      assert(m_num_current_renderables != m_MAX_RENDERABLES);
      Renderable& r = m_renderables[m_num_current_renderables++];
      r.what = geometry;

      return &r;
   }

   
   void Renderer::render_scene()
   {
      // http://qt-project.org/doc/qt-4.8/qglwidget.html#glDraw
      // Executes the virtual function paintGL().
      glDraw();
   }


   // do nothing
   void Renderer::paintEvent()
   {
      // http://qt-project.org/doc/qt-4.8/qglwidget.html#paintEvent
      // Will cause the virtual paintGL() function to be called.

      // We don't want this event handler to call the painting function outside
      // of our own calls, so do nothing.
   }



   Matrix2D Renderer::get_aspect_correction_matrix() const
   {
      float aspect_ratio = static_cast<float>(width()) / height();
      if (aspect_ratio > 1.0f)
      {
         return Matrix2D::scale(1 / aspect_ratio, 1);
      }
      else
      {
         return Matrix2D::scale(1, aspect_ratio);
      }
   }

   void Renderer::paintGL()
   {
      // http://qt-project.org/doc/qt-4.8/qglwidget.html#paintGL
      // This virtual function is called whenever the widget needs to be 
      // repainted.  Reimplement it in a subclass.

      // only need to clear the color buffer when we are not redrawing every
      // pixel in the window (if we were, then clearing the buffer would be a
      // waste of time because the pixels are already getting overwritten)
      glClear(GL_COLOR_BUFFER_BIT);

      Vector2D transformed_verts[m_MAX_VERTS];

      for (uint index = 0; index < m_num_current_renderables; index++)
      {
         const Renderable& r = m_renderables[index];

         // indices
         glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 
            sizeof(ushort) * r.what->num_indices, r.what->indices);

         // vertices
         Matrix2D linear_transform = get_aspect_correction_matrix() * r.where;
         for (uint vert_index = 0; vert_index < r.what->num_verts; vert_index += 1)
         {
            // order of multiplication: matrix * vertex
            transformed_verts[vert_index] = linear_transform * r.what->verts[vert_index]; // transform positional data
            //transformed_verts[vert_index + 1] = r.what->verts[vert_index + 1];            // leave color data intact
         }

         glBufferSubData(GL_ARRAY_BUFFER, 0, 
            sizeof(Vector2D) * r.what->num_verts, transformed_verts);

         glDrawElements(r.what->render_mode, r.what->num_indices, 
            GL_UNSIGNED_SHORT, 0);
      }
   }


   void Renderer::initializeGL()
   {
      // http://qt-project.org/doc/qt-4.8/qglwidget.html#initializeGL
      // This function should set up any required OpenGL context rendering 
      // flags, defining display lists, etc.

      GLenum status = glewInit();
      assert(status == 0);

      // clear the color buffer to be opaque (alpha = 1) and black
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

      // we could have made 2 buffers in one call and passed in the address of
      // the vertex buffer ID, which comes right before the index buffer ID in
      // the class (and therefore in RAM as well), but this hurts the 
      // maintainability of the code, so make a single buffer for each
      glGenBuffers(1, &m_vertex_buffer_ID);
      glGenBuffers(1, &m_index_buffer_ID);

      glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);

      glBufferData(GL_ARRAY_BUFFER, m_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);   // position
      //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector2D), 0);   // position
      //glEnableVertexAttribArray(1);
      //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector2D), (void*)sizeof(Vector2D));
   }
}
