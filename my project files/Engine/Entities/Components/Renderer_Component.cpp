#include "Renderer_Component.h"

#include "Rendering\Renderable.h"
using Rendering::Renderable;

#include "Math\Matrix2D.h"
using Math::Matrix2D;

#include "Entities\Entity.h"

namespace Entities
{
   void Renderer_Component::set_data(Renderable *renderable_ptr)
   {
      this->m_renderable_ptr = renderable_ptr;
   }

   void Renderer_Component::update()
   {
      m_renderable_ptr->where = Matrix2D::translate(m_containing_entity->position);
   }
}