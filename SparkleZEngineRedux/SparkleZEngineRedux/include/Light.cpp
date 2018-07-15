#include "Light.h"
#include "SceneManager.h"
#include "GameObject.h"

namespace sparklezEngine
{
  PointLight::PointLight()
  {
    m_LightIntensity = 5.0f;
    m_Range = 30.0f;
    SceneManager::GetSceneLights().push_back(GetGameObject());
  }

  PointLight::~PointLight()
  {
    Destroy();
  }

  void PointLight::Awake()
  {
    if (GetGameObject().lock()->getComponent<PointLight>().lock() == std::shared_ptr<PointLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (GetGameObject().lock()->getComponent<DirectionalLight>().lock() == std::shared_ptr<DirectionalLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (GetGameObject().lock()->getComponent<SpotLight>().lock() == std::shared_ptr<SpotLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
  }

  void PointLight::Destroy()
  {
    SetDestroyed(true);
    SceneManager::RemoveLightFromScene(GetGameObject());
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
    SceneManager::GetSceneLights().push_back(GetGameObject());
  }

  DirectionalLight::~DirectionalLight()
  {

  }

  void DirectionalLight::Awake()
  {
    if (GetGameObject().lock()->getComponent<PointLight>().lock() == std::shared_ptr<PointLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (GetGameObject().lock()->getComponent<DirectionalLight>().lock() == std::shared_ptr<DirectionalLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (GetGameObject().lock()->getComponent<SpotLight>().lock() == std::shared_ptr<SpotLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
  }
  void DirectionalLight::Destroy()
  {
    SetDestroyed(true);
    SceneManager::RemoveLightFromScene(GetGameObject());
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
    SceneManager::GetSceneLights().push_back(GetGameObject());
  }
  SpotLight::~SpotLight()
  {

  }
  void SpotLight::Awake()
  {
    if (GetGameObject().lock()->getComponent<PointLight>().lock() == std::shared_ptr<PointLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (GetGameObject().lock()->getComponent<DirectionalLight>().lock() == std::shared_ptr<DirectionalLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
    else if (GetGameObject().lock()->getComponent<SpotLight>().lock() == std::shared_ptr<SpotLight>())
    {
      Console::ErrorMessage(GetGameObject().lock()->getName() + " Has two or more lights attached, may not display light correctly.");
    }
  }
  void SpotLight::Destroy()
  {
    SetDestroyed(true);
    SceneManager::RemoveLightFromScene(GetGameObject());
  }
  void SpotLight::SaveComponent()
  {

  }
  void SpotLight::LoadComponent()
  {

  }
}