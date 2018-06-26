#ifndef SPARKLEZ_ENGINE_COMPONENT_LIGHT_H
#define SPARKLEZ_ENGINE_COMPONENT_LIGHT_H
#include "Behaviour.h"
#include "Console.h"
#include "Colour.h"
#include <memory>

namespace sparklezEngine
{
  class GameObject;
  class PointLight : public Behaviour
  {
    friend class sparklezEngine::GameObject;
  public:

    PointLight();
    ~PointLight();

    void Awake();
    void Destroy();
    void SaveComponent();
    void LoadComponent();

  private:
    Colour m_LightColour;
    float m_Range;
    float m_LightIntensity;
  };

  class DirectionalLight : public Behaviour
  {
    friend class GameObject;
  public:

    DirectionalLight();
    ~DirectionalLight();

    void Awake();
    void Destroy();
    void SaveComponent();
    void LoadComponent();

  private:
    Colour m_LightColour;
    float m_LightIntensity;
  };

  class SpotLight : public Behaviour
  {
    friend class GameObject;
  public:

    SpotLight();
    ~SpotLight();

    void Awake();
    void Destroy();
    void SaveComponent();
    void LoadComponent();

  private:
    Colour m_LightColour;
    float m_Range;
    float m_LightIntensity;
  };
}
#endif