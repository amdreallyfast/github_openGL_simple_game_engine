#include "My_Game.h"

// for getting a geometry object pointer that we can pass into 
// the renderer
#include <Rendering\Geometry.h>
using Rendering::Geometry;

// for adding geometry to the renderer
#include <Rendering\Renderer.h>
using Rendering::Renderer;

// for initialization of the engine's Key_Input class
#include <Input\Key_Input.h>
using Input::Key_Input;

// for our game-specific key settings
#include <Key_Mapper.h>
using Input::Key_Mapper;
#include <Key_Action_Enums.h>

// for making ship vertices
#include "Math\Vector2D.h"
using Math::Vector2D;

// for memcpy(...)
#include <cstdlib>

// for initializing the singleton Game_Clock engine-clock-wrapper, 
// which our components may use
#include <Timing\Game_Clock.h>
using Timing::Game_Clock;


bool My_Game::initialize()
{
   if (!m_renderer.initialize()) 
   { return false; }
   if (!Key_Input::get_instance().initialize(&m_key_mapper, Input::Key_Action_Enums::MAX)) 
   { return false; }
   if (!Game_Clock::get_instance().initialize())
   { return false; }
   if (!initialize_ship()) 
   { return false; }

   // hook up the timer to the "timer update" event
   if (!connect(
      &m_qt_timer, SIGNAL(timeout()), 
      this, SLOT(timer_update())))
   { return false; }


   return true;
}


bool My_Game::initialize_ship()
{
   // make permanent copies of this stack data that will persist
   // throughout the game
   Vector2D local_ship_vert_data[] =
   {
      Vector2D(+0.0f, +0.1f, 1.0f),
      Vector2D(-0.1f, -0.1f, 1.0f),
      Vector2D(+0.1f, -0.1f, 1.0f),
   };
   memcpy(m_ship_verts, local_ship_vert_data, sizeof(m_ship_verts));

   ushort local_ship_index_data[] = 
   { 
      0, 1, 2,
   };
   memcpy(m_ship_indices, local_ship_index_data, sizeof(m_ship_indices));


   // add the components in the order that you want the simple update 
   // array loop to update each individual one
   m_ship.add_component(&m_ship_controller);
   m_ship.add_component(&m_ship_physics);

   Geometry* ship_geometry = m_renderer.add_geometry(
      m_ship_verts, m_NUM_SHIP_VERTS,
      m_ship_indices, m_NUM_SHIP_INDICES);
   m_ship_renderable = m_renderer.add_renderable(ship_geometry);
   m_ship_renderer.set_data(m_ship_renderable);
   m_ship.add_component(&m_ship_renderer);

   return m_ship.initialize();
}


bool My_Game::shutdown()
{
   bool good = true;

   // shut things down in the opposite order as initialization

   // shut down entities and their components
   good &= m_ship.shutdown();

   // shut down engine
   good &= Game_Clock::get_instance().shutdown();
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
   // record that a new frame started
   Game_Clock::get_instance().new_frame();

   // update the controls
   Key_Input::get_instance().update();

   // update the entity components
   m_ship.update();

   // render the scene with the new data
   m_renderer.render_scene();
}

