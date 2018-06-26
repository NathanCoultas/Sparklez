#include "Light.h"
#include "SceneManager.h"
#include "GameObject.h"

namespace sparklezEngine
{
  PointLight::PointLight()
  {
    m_LightIntensity = 5.0f;
    m_Range = 30.0f;
    SceneManager::GetSceneLights().push_back(getMyGameObject());
  }

  PointLight::~PointLight()
  {
    Destroy();
  }

  void PointLight::Awake()
  {
    if (getMyGameObject().lock()->getComponent<PointLight>().lock() == std::shared_ptr<PointLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (getMyGameObject().lock()->getComponent<DirectionalLight>().lock() == std::shared_ptr<DirectionalLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (getMyGameObject().lock()->getComponent<SpotLight>().lock() == std::shared_ptr<SpotLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
  }

  void PointLight::Destroy()
  {
    SetDestroyed(true);
    SceneManager::RemoveLightFromScene(getMyGameObject());
  }

  void PointLight::SaveComponent()
  {

  }

  void PointLight::LoadComponent()
  {

  }

  DirectionalLight::DirectionalLight()
  {
    m_LightIntensity = 5.0f;
    SceneManager::GetSceneLights().push_back(getMyGameObject());
  }

  DirectionalLight::~DirectionalLight()
  {

  }

  void DirectionalLight::Awake()
  {
    if (getMyGameObject().lock()->getComponent<PointLight>().lock() == std::shared_ptr<PointLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (getMyGameObject().lock()->getComponent<DirectionalLight>().lock() == std::shared_ptr<DirectionalLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (getMyGameObject().lock()->getComponent<SpotLight>().lock() == std::shared_ptr<SpotLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
  }
  void DirectionalLight::Destroy()
  {
    SetDestroyed(true);
    SceneManager::RemoveLightFromScene(getMyGameObject());
  }
  void DirectionalLight::SaveComponent()
  {

  }
  void DirectionalLight::LoadComponent()
  {

  }
  SpotLight::SpotLight()
  {
    m_LightIntensity = 5.0f;
    m_Range = 30.0f;
    SceneManager::GetSceneLights().push_back(getMyGameObject());
  }
  SpotLight::~SpotLight()
  {

  }
  void SpotLight::Awake()
  {
    if (getMyGameObject().lock()->getComponent<PointLight>().lock() == std::shared_ptr<PointLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (getMyGameObject().lock()->getComponent<DirectionalLight>().lock() == std::shared_ptr<DirectionalLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (getMyGameObject().lock()->getComponent<SpotLight>().lock() == std::shared_ptr<SpotLight>())
    {
      Console::ErrorMessage(getMyGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
  }
  void SpotLight::Destroy()
  {
    SetDestroyed(true);
    SceneManager::RemoveLightFromScene(getMyGameObject());
  }
  void SpotLight::SaveComponent()
  {

  }
  void SpotLight::LoadComponent()
  {

  }
}