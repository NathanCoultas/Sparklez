#include "BoxCollider.h"
#include "MeshFilter.h"
#include "BoundsBox.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Transform.h"

namespace sparklezEngine
{
  void BoxCollider::Awake()
  {
	m_BoxSize = glm::vec3(0,0,0);
	m_IsKimetic = false;
  }

  void BoxCollider::Start()
  {
	if (GetGameObject().lock()->getComponent<MeshFilter>().lock() != NULL)
	{
	  if(GetGameObject().lock()->getComponent<MeshFilter>().lock()->GetBounds().lock() != NULL)
	  { 
		glm::vec3 l_boxbounds = GetGameObject().lock()->getComponent<MeshFilter>().lock()->GetBounds().lock()->l_MaxSize;
		if (l_boxbounds != glm::vec3(0, 0, 0))
		{
		  m_BoxSize = ((l_boxbounds / glm::vec3(2,2,2)) * GetTransform().lock()->GetTransformScale());
		}
		
	  }
	}
	if (m_BoxSize == glm::vec3(0, 0, 0))
	{
	  m_BoxSize = glm::vec3(1, 1, 1) * GetTransform().lock()->GetTransformScale();
	}
	
	m_Collider = std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(m_BoxSize.x,m_BoxSize.y,m_BoxSize.z)));

	if (GetGameObject().lock()->getComponent<Rigidbody>().lock() == NULL)
	{
	  GetGameObject().lock()->addComponent<Rigidbody>();
	}

  }

  //unused

  void BoxCollider::Update()
  {

  }

  void BoxCollider::FixedUpdate()
  {
	
  }

  void BoxCollider::SetKimetic(bool _state)
  {
	m_IsKimetic = _state;
  }

  bool BoxCollider::IsKimetic()
  {
	return m_IsKimetic;
  }

  std::weak_ptr<btCollisionShape> BoxCollider::GetCollider()
  {
	return m_Collider;
  }

}