#include "My_Game.h"

// unlike the header file, which will get included in who-knows-how-many 
// compilation units, we #include the "Renderable" header file here instead
// of forward declaring it so that we can access it's data members
#include "Rendering\Renderer.h"
using Rendering::Renderer;

#include "Rendering\Geometry.h"
using Rendering::Geometry;

#include <Input\Key_Input.h>
using Input::Key_Input;

#include <Key_Mapper.h>
using Input::Key_Mapper;
#include <Key_Action_Enums.h>

#include "Math\Vector2D.h"
using Math::Vector2D;

// for memcpy(...)
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
   { return false; }
   if (!Key_Input::get_instance().initialize(&m_key_mapper, Input::Key_Action_Enums::MAX)) 
   { return false; }

   // hook up the timer to the "timer update" event
   connect(&m_qt_timer, SIGNAL(timeout()), this, SLOT(timer_update()));

   Geometry* ship_geometry = m_renderer.add_geometry(
      m_ship_verts, m_NUM_SHIP_VERTS,
      m_ship_indices, m_NUM_SHIP_INDICES);
   m_ship_renderable = m_renderer.add_renderable(ship_geometry);
   m_ship_renderer.set_data(m_ship_renderable);

   // must add the components before initializing
   m_ship.add_component(&m_ship_renderer);
   m_ship.add_component(&m_ship_physics);
   m_ship.add_component(&m_ship_controller);
   if (!m_ship.initialize()) { return false; }

   return true;
}

bool My_Game::shutdown()
{
   bool good = true;

   good &= m_ship.shutdown();
   good &= Key_Input::get_instance().shutdown();
   good &= m_renderer.shutdown();

   return good;
}

void My_Game::go()
{
   // make the timer go as fast as it can
   // Note: Argument values to the qt timer are in milliseconds.
   m_qt_timer.start(0);
}

void My_Game::timer_update()
{
   // update the controls
   Key_Input::get_instance().update();

   // update the entity components
   m_ship.update();

   // render the scene with the new data
   m_renderer.render_scene();
}

