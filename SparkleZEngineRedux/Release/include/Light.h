#ifndef SPARKLEZ_ENGINE_COMPONENT_LIGHT_H
#define SPARKLEZ_ENGINE_COMPONENT_LIGHT_H
#include "Behaviour.h"
#include "Console.h"
#include "Colour.h"
#include <memory>

namespace sparklezEngine
{
  class GameObject;
  class Colour;
  class Light : public Behaviour
  {
    friend class GameObject;
	friend class Colour;
  public:

    Light();
    virtual ~Light();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void Destroy();
    virtual void SaveComponent();
    virtual void LoadComponent();

  private:
    Colour m_LightColour;
    float m_LightIntensity;
  };
}
#endif