#include "SceneManager.h"
#include "GameObject.h"
#include "Console.h"
#include "bullet\btBulletDynamicsCommon.h"

namespace sparklezEngine
{
  bool SceneManager::m_SceneLoading;
  bool SceneManager::m_EditMode;
  bool SceneManager::m_Runtime;
  float SceneManager::m_deltaTime;

  btBroadphaseInterface* SceneManager::m_broadphase;
  btDefaultCollisionConfiguration* SceneManager::m_collisionConfiguration;
  btCollisionDispatcher* SceneManager::m_dispatcher;
  btSequentialImpulseConstraintSolver* SceneManager::m_solver;
  btDiscreteDynamicsWorld* SceneManager::m_dynamicsWorld;

  std::vector<std::shared_ptr<GameObject>> SceneManager::m_SceneObjects;
  std::vector<std::weak_ptr<GameObject>> SceneManager::m_SceneLights;

  void SceneManager::NewScene()
  {
    if (m_EditMode == false)
    {
      //error message to console saying the scene is currently playing and to stop it
      //or new scene whilst it's running?
      sparklezEngine::Console::ErrorMessage("The current scene is in runtime, end runtime to create a new scene.");
      return;
    }

    m_SceneLoading = true;
    m_EditMode = true;
    m_Runtime = false;

    for each (std::shared_ptr<GameObject> l_GameObj in m_SceneObjects)
    {
      l_GameObj->Destroy();
      //remove l_gameobj from m_sceneobjects

    }

    if (m_SceneObjects.empty() == false)
    {
      m_SceneObjects.clear();
    }

  }

  void SceneManager::PlayScene()
  {
    if (m_Runtime == true)
    {
      //throw console error saying scene is already running;
      return;
    }
    m_EditMode = false;

    //use savescene to save a temp scene of what the scene currently is.

    //call Application::Runtime();

    m_Runtime = true;
  }

  void SceneManager::StopRuntime()
  {
    m_Runtime = false;
    //use loadscene to load the temp saved scene
    //use deletescene to delete the temp scene
    //call Application::EditMode();
    m_EditMode = true;
  }

  btDiscreteDynamicsWorld * SceneManager::GetDynamicWorld()
  {
    return m_dynamicsWorld;
  }

  void SceneManager::LoadScene(std::string _SceneName)
  {
    m_SceneLoading = true;
    m_EditMode = true;
    m_Runtime = false;
  }

  void SceneManager::SaveScene(std::string _SceneName)
  {

  }

  void SceneManager::DeleteScene(std::string _SceneName)
  {

  }

  //move this into gameobject as it doesn't actually need to be in here an	
  std::weak_ptr<GameObject> SceneManager::FindGameObjectByName(std::string _name)
  {
    for each(std::shared_ptr<GameObject> l_GameObj in m_SceneObjects)
    {
      if (l_GameObj->getName() == _name)
      {
        return std::weak_ptr<GameObject>(l_GameObj);
      }
    }
    return std::weak_ptr<GameObject>();
  }

  void SceneManager::RemoveObjectFromScene(std::weak_ptr<GameObject> _GameObj)
  {
    for (int l_i = 0; l_i < m_SceneLights.size(); l_i++)
    {
      if (m_SceneLights.at(l_i).lock() == _GameObj.lock())
      {
        m_SceneLights.erase(m_SceneLights.begin() + l_i);
        l_i--;
      }
    }
  }

  void SceneManager::RemoveLightFromScene(std::weak_ptr<GameObject> _GameObj)
  {
    for (int l_i = 0; l_i < m_SceneObjects.size(); l_i++)
    {
      if (m_SceneObjects.at(l_i) == _GameObj.lock())
      {
        m_SceneObjects.erase(m_SceneObjects.begin() + l_i);
        l_i--;
      }
    }
  }

  std::vector<std::shared_ptr<GameObject>>& SceneManager::GetSceneObjects()
  {
    return m_SceneObjects;
  }

  std::vector<std::weak_ptr<GameObject>>& SceneManager::GetSceneLights()
  {
    return m_SceneLights;
  }

  void SceneManager::InitPhysicsWorld(float _XGrav, float _YGrav, float _ZGrav)
  {
    m_broadphase = new btDbvtBroadphase();
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_solver = new btSequentialImpulseConstraintSolver;
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    m_dynamicsWorld->setGravity(btVector3(_XGrav, _YGrav, _ZGrav));
  }

  float SceneManager::getDeltaTime()
  {
    if (m_deltaTime > 0.05f)
    {
      return 0.05f;
    }

    return m_deltaTime;
  }
}