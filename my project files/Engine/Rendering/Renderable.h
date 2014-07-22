#ifndef ENGINE_RENDERABLE
#define ENGINE_RENDERABLE

// we need a Matrix2D object, so we can't forward declare it
#include "Math\Matrix2D.h"

namespace Rendering
{
   // forward declare the Geometry class
   class Geometry;

   // is composed of geometry
   class Renderable
   {
   public:
      // the Renderer_Component class will need to update this on every frame
      Math::Matrix2D where;

   private:
      // let the renderer, but no one else, have access to the geometry
      friend class Renderer;
      const Geometry *what;
   };
}

#endif
