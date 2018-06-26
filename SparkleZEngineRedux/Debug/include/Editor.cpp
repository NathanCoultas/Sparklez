#include "Behaviour.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Input.h"
#include "Transform.h"
#include "Console.h"
#include "Editor.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "SphereCollider.h"


#include <string>
namespace sparklezEngine
{
  //This function is called as soon as possible after the object has been made both in edit time and play time.
  void Editor::Awake()
  {
    setName("Editor");
  
    SDL_SetRelativeMouseMode(SDL_TRUE);
  }
  void Editor::Start()
  {

  }
  void Editor::Update()
  {
	float l_speed = 0.1f;
    float l_RotX = Input::GetMouseMotion().x * l_speed;
    float l_RotY = Input::GetMouseMotion().y * l_speed;

    getMyGameObject().lock()->GetTransform().lock()->ModifyRotation(-l_RotY, l_RotX, 0);


    std::weak_ptr<Transform>  l_CamTrans = SceneManager::FindGameObjectByName("MainCamera").lock()->GetTransform();
    float l_Speed = 5.0f * SceneManager::getDeltaTime();
	if (Input::getKeyState("1"))
	{

	  GameObject* l_obj = new GameObject();
	  std::string objl_name = l_obj->getName();
	  SceneManager::FindGameObjectByName(objl_name).lock()->addComponent<MeshRenderer>().lock()->SetMeshRef("meshs/cube.obj");
	  SceneManager::FindGameObjectByName(objl_name).lock()->addComponent<BoxCollider>();
	  SceneManager::FindGameObjectByName(objl_name).lock()->GetTransform().lock()->SetPosition(0,30,0);
	}
	if (Input::getKeyState("2"))
	{
	  GameObject* l_obj = new GameObject();
	  std::string objl_name = l_obj->getName();
	  SceneManager::FindGameObjectByName(objl_name).lock()->addComponent<MeshRenderer>().lock()->SetMeshRef("meshs/sphere.obj");
	  SceneManager::FindGameObjectByName(objl_name).lock()->addComponent<SphereCollider>();
	  SceneManager::FindGameObjectByName(objl_name).lock()->GetTransform().lock()->SetPosition(0, 30, 0);
	}
    if (Input::getKeyState("W"))
    {
      l_CamTrans.lock()->ModifyPosition(l_CamTrans.lock()->GetForwardVector() * l_Speed);
    }
    if (Input::getKeyState("S"))
    {
      l_CamTrans.lock()->ModifyPosition(-l_CamTrans.lock()->GetForwardVector()* l_Speed);
    }
    if (Input::getKeyState("A"))
    {
      l_CamTrans.lock()->ModifyPosition(-l_CamTrans.lock()->GetRightVector()* l_Speed);
    }
    if (Input::getKeyState("D"))
    {
      l_CamTrans.lock()->ModifyPosition(l_CamTrans.lock()->GetRightVector()* l_Speed);
    }
    if (Input::getKeyState("E"))
    {
      l_CamTrans.lock()->ModifyPosition(l_CamTrans.lock()->GetUpVector() * l_Speed);
    }
    if (Input::getKeyState("Q"))
    {
      l_CamTrans.lock()->ModifyPosition(-l_CamTrans.lock()->GetUpVector()* l_Speed);
    }

	//getMyGameObject().lock()->getComponent<Rigidbody>().lock()->ForceUpdate();

  }
  void Editor::FixedUpdate()
  {

  }

  void Editor::Destroy()
  {
    SetDestroyed(true);
  }
}