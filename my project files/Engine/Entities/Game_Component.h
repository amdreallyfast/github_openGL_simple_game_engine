#ifndef ENGINE_GAME_COMPONENT_H
#define ENGINE_GAME_COMPONENT_H


namespace Entities
{
   // the Game_Component class will need to access it's storing entity's data
   class Entity;

   // export this to dll because it's derived classes are exported to dll
   // (this is just good practice)
   class __declspec(dllexport) Game_Component
   {
   public:
      // a pure virtual function that does nothing unless a derived class 
      // defines it
      virtual void update() {}

   private:
      // the Entity class will need to be able to set "containing entity"
      friend class Entity;

   protected:
      // derived classes will need access to this pointer
      Entity *m_containing_entity;
   };
}

#endif
