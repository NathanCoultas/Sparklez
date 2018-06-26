#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"

namespace sparklezEngine
{
  GameObject::GameObject()
  {
    SceneManager::GetSceneObjects().push_back(std::shared_ptr<GameObject>(this));
    addComponent<Transform>();
    m_IsActive = true;
    m_IsActive = false;
    m_Layer = 1;
    m_Awake = false;
	m_Name = "GameObject"+(SceneManager::GetSceneObjects().size());
  }

  GameObject::GameObject(std::string _name)
  {
    setName(_name);
    SceneManager::GetSceneObjects().push_back(std::shared_ptr<GameObject>(this));
    addComponent<Transform>();
    m_IsActive = true;
    m_Layer = 1;
    m_IsStatic = false;
    m_Awake = false;
  }

  //third constructer with option to load an object which isn't active yet?
  //possiblly could just let people do set.active in the awake function

  GameObject::~GameObject()
  {
    //SceneManager::RemoveObjectFromScene(std::shared_ptr<GameObject>(this));

      // Destroy();
    m_Components.clear();

  }

  void GameObject::Awake()
  {
    for (size_t i = 0; i < m_Components.size(); i++)
    {
      m_Components.at(i)->Awake();
    }
  }

  void GameObject::Start()
  {
    for (size_t i = 0; i < m_Components.size(); i++)
    {
      m_Components.at(i)->Start();
    }
  }

  void GameObject::Update()
  {
    if (m_Awake == false)
    {
      Start();
      m_Awake = true;
    }
    
    for (size_t i = 0; i < m_Components.size(); i++)
    {
      m_Components.at(i)->Update();
    }
  }

  void GameObject::FixedUpdate()
  {
    for (size_t i = 0; i < m_Components.size(); i++)
    {
      m_Components.at(i)->FixedUpdate();
    }
  }

  void GameObject::Render()
  {
    for (size_t i = 0; i < m_Components.size(); i++)
    {
      m_Components.at(i)->Render();
    }
  }

  void GameObject::Instantiate()
  {

  }

  void GameObject::SetActive(bool _ActiveState)
  {
    m_IsActive = _ActiveState;
  }

  void GameObject::SetStatic(bool _IsStaticState)
  {
    m_IsStatic = _IsStaticState;
  }

  bool GameObject::IsActive()
  {
    return m_IsActive;
  }

  bool GameObject::IsStatic()
  {
    return m_IsStatic;
  }

  std::weak_ptr<Transform> GameObject::GetTransform()
  {
    return getComponent<Transform>();
  }

  void GameObject::Destroy()
  {
    if (m_destroyed == false)
    {

      for (int l_i = 0; l_i < m_Components.size(); l_i++)
      {
        m_Components.at(l_i)->Destroy();
      }

      m_Components.clear();
    }
    m_destroyed = true;
    return;
  }
}