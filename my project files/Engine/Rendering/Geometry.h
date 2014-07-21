#ifndef ENGINE_GEOMETRY
#define ENGINE_GEOMETRY

#include "Misc\Typedefs.h"

// forward declare the vectore class and let the linker hook it up
namespace Math { struct Vector2D; }

namespace Rendering
{
   // a data store helper for the renderer
   class Geometry
   {
      // let everything be private, but let the renderer access them
      friend class Renderer;

      const Math::Vector2D *verts;
      uint num_verts;
      const ushort *indices;
      uint num_indices;

      GLenum render_mode;
   };
}

#endif
