#ifndef SANDBOX_GAME_MY_GAME_H
#define SANDBOX_GAME_MY_GAME_H

// for the QObject macro
#include <QtCore\QObject>

// for the timer that will queue up "update()" events
#include <QtCore\qtimer>

// need an instance of the renderer
#include "Rendering/Renderer.h"

// only need a pointer
namespace Rendering { class Renderable; }

// need the vector class so the compiler can know how big the vector is
#include "Math\Vector2D.h"

// for the "ship" entity and its various parts
#include "Entities\Entity.h"
#include "Entities\Components\Renderer_Component.h"
#include "Entities\Components\Physics_Components.h"


class My_Game : public QObject
{
   // necessary declaration for the creation of a SLOT
   Q_OBJECT

public:
   // for copying data into the My_Game object's memory
   My_Game();

   // for setup
   bool initialize();

   // matching shutdown for initializer
   bool shutdown();

   // the primary game loop
   void go();


private:
   QTimer m_qt_timer;

   // keep the entities together for cache coherency
   Entities::Entity m_ship;
   Entities::Renderer_Component m_ship_renderer;
   Entities::Physics_Components m_ship_physics;


   Rendering::Renderer m_renderer;
   Rendering::Renderable* m_ship_renderable;
   Rendering::Renderable* m_lerp_instance;

   static const uint m_NUM_SHIP_VERTS = 3;
   static const uint m_NUM_SHIP_INDICES = 3;
   Math::Vector2D m_ship_verts[m_NUM_SHIP_VERTS];
   ushort m_ship_indices[m_NUM_SHIP_INDICES];

private slots:
   // call once every time you want everything to update and a frame to be 
   // rendered
   void timer_update();

};


#endif
