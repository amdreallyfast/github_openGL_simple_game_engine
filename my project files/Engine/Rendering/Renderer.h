#ifndef ENGINE_RENDERABLE_H
#define ENGINE_RENDERABLE_H

#include "QtOpenGL\qglwidget"

#include <Math\matrix2D.h>
namespace Math { struct Vector2D; }
#include "Misc\Typedefs.h"
#include <Rendering\shader_handler.h>

// include these because we need the size of the class for our pools
// Note: Don't use their namespaces here because we don't want whoever includes
// this file to be using them either.  The renderer is already in the same 
// namespace too, so we don't need explicit namespace qualifiers.
#include "Rendering\Geometry.h"
#include "Rendering\Renderable.h"

namespace Rendering
{
   class A
   {
      GLuint x;
   };
   class __declspec(dllexport) Renderer : public QGLWidget
   {
   public:
      // make an initialization function instead of your own constructor 
      // because we may want to initialize multiple times, and we don't want
      // to create multiple instances of the this class to do that
      bool initialize();

      // the counterpart to the initialization function
      bool shutdown();

      // add some geometry to be rendered
      // Note: A single geometry can be used in multiple renderables.
      Geometry* add_geometry(
         Math::Vector2D *verts, uint num_verts,
         ushort* indices, uint num_indices,
         GLenum render_mode = GL_TRIANGLES);

      // add a renderable to the collection using the provided geometry
      Renderable* add_renderable(Geometry* geometry);

      // call the drawing event yourself
      void render_scene();

   protected:
      // override QGLWidget's automated painting event to do nothing
      void paintEvent();

      // override QGLWidget's vitual paint function 
      void paintGL();

      // override QGLWidget's initializeGL to set up buffer variables
      void initializeGL();

   private:
      // is for internal use only, but must be a method of this class
      // in order to access width() and height() methods
      Math::Matrix2D get_aspect_correction_matrix() const;

      // each renderer will have its own shader program
      shader_handler m_shader_handler;

      // declare a pool of geometries
      static const uint m_MAX_GEOMETRIES = 10;
      uint m_num_current_geometries;
      Geometry m_geometries[m_MAX_GEOMETRIES];

      // declare a pool of renderables
      static const uint m_MAX_RENDERABLES = 10;
      uint m_num_current_renderables;
      Renderable m_renderables[m_MAX_RENDERABLES];

      // variables to keep track of buffer things for rendering
      static const uint m_MAX_BUFFER_SIZE = 1024;
      GLuint m_vertex_buffer_ID;
      GLuint m_index_buffer_ID;
      static const uint m_MAX_VERTS = 10;
   };
}

#endif
