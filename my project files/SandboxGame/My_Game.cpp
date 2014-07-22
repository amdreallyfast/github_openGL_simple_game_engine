#include "My_Game.h"

// unlike the header file, which will get included in who-knows-how-many 
// compilation units, we #include the "Renderable" header file here instead
// of forward declaring it so that we can access it's data members
#include "Rendering\Renderer.h"
using Rendering::Renderer;

#include "Rendering\Geometry.h"
using Rendering::Geometry;

#include "Math\Vector2D.h"
using Math::Vector2D;

#include <cstdlib>

My_Game::My_Game()
{
   Vector2D local_ship_vert_data[] =
   {
      // as far as the compiler is concerned, these are adjacent pairs of floats
      // in memory, so your vertex attribute and buffer data specifications are 
      // the same as if you only entered float values here
      Vector2D(+0.0f, +0.1f, 1.0f),
      Vector2D(-0.1f, -0.1f, 1.0f),
      Vector2D(+0.1f, -0.1f, 1.0f),
   };
   memcpy(m_ship_verts, local_ship_vert_data, sizeof(m_ship_verts));

   ushort local_ship_index_data[] = { 0, 1, 2 };
   memcpy(m_ship_indices, local_ship_index_data, sizeof(m_ship_indices));
}

bool My_Game::initialize()
{
   if (!m_renderer.initialize())
   {
      return false;
   }

   // hook up the timer to the "timer update" event
   connect(&m_qt_timer, SIGNAL(timeout()), this, SLOT(timer_update()));

   Geometry* ship_geometry = m_renderer.add_geometry(
      m_ship_verts, m_NUM_SHIP_VERTS,
      m_ship_indices, m_NUM_SHIP_INDICES);

   m_ship_renderable = m_renderer.add_renderable(ship_geometry);
   m_ship_renderer.set_data(m_ship_renderable);
   m_ship.add_component(&m_ship_renderer);

   return true;
}

bool My_Game::shutdown()
{
   return m_renderer.shutdown();
}

void My_Game::go()
{
   // make the timer go as fast as it can
   // Note: Argument values to the qt timer are in milliseconds.
   m_qt_timer.start(0);
}

void My_Game::timer_update()
{
   m_ship.update();
   m_renderer.render_scene();
}

