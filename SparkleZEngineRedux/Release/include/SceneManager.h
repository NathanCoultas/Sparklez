#ifndef SPARKLEZ_ENGINE_SCENEMANAGER_H
#define SPARKLEZ_ENGINE_SCENEMANAGER_H
#include <string>
#include <vector>
#include <memory>
#include "bullet\btBulletDynamicsCommon.h"


namespace sparklezEngine
{
  class Application;
  class Console;
  class GameObject;

  class SceneManager
  {

	friend class sparklezEngine::Application;
	friend class sparklezEngine::Console;

  public:
	//unload current scene objects and clear scene, load default scene			
	static void NewScene();

	//whilst in editor mode takes a string as input and then saves all current gameobjects into a file named as the scene name, will show a warning that it overwrites existing data
	static void SaveScene(std::string _SceneName);

	//whilst in editor mode takes a string as input and then clears the current scene and then searchs the scene directory for the string name and reads and loads the file
	static void LoadScene(std::string _SceneName);

	//deletes a file
	static void DeleteScene(std::string _SceneName);

	static std::weak_ptr<GameObject> FindGameObjectByName(std::string _name);
	static void RemoveObjectFromScene(std::weak_ptr<GameObject> _GameObj);
	//static std::weak_ptr<GameObject> GetGameObjectPointer(std::weak_ptr<GameObject> _gameobj);
	static std::vector<std::shared_ptr<GameObject>> &GetSceneObjects();

	static void InitPhysicsWorld(float _XGrav, float _YGrav, float _ZGrav);

	static float getDeltaTime();

	//plays the current scene
	static void PlayScene();
	static void StopRuntime();
	static btDiscreteDynamicsWorld* GetDynamicWorld();
	
  private:
	//bullet physics init
	
	static btBroadphaseInterface* m_broadphase;
	static btDefaultCollisionConfiguration* m_collisionConfiguration;
	static btCollisionDispatcher* m_dispatcher;
	static btSequentialImpulseConstraintSolver* m_solver;
	static btDiscreteDynamicsWorld* m_dynamicsWorld;
	

	//holds all the gameobjects in the scene
	static std::vector<std::shared_ptr<GameObject>> m_SceneObjects;
	//time between frames in ns
	static float m_deltaTime;
	//scene bools
	static bool m_SceneLoading;
	static bool m_EditMode;
	static bool m_Runtime;
  };

}
#endif