#ifndef SPARKLEZ_ENGINE_COMPONENT_CHARACTER_CONTROLLER_H
#define SPARKLEZ_ENGINE_COMPONENT_CHARACTER_CONTROLLER_H
#include "Behaviour.h"
#include "Console.h"

namespace sparklezEngine
{
  class GameObject;
  class CharacterController : public Behaviour
  {
    friend class GameObject;
  public:

    virtual ~CharacterController();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void Destroy();
  private:


    bool m_isGrounded;
  };
}
#endif