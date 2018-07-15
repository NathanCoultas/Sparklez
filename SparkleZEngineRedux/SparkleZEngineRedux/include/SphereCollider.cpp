#include "SphereCollider.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "BoundsBox.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Transform.h"

namespace sparklezEngine
{
  void SphereCollider::Awake()
  {
	m_Radius = 0;
	m_IsKimetic = false;
  }
  void SphereCollider::Start()
  {
	if (GetGameObject().lock()->getComponent<MeshFilter>().lock() != NULL)
	{
	  if (GetGameObject().lock()->getComponent<MeshFilter>().lock()->GetBounds().lock() != NULL)
	  {
		glm::vec3 l_boxbounds = GetGameObject().lock()->getComponent<MeshFilter>().lock()->GetBounds().lock()->l_MaxSize;
		if (l_boxbounds != glm::vec3(0, 0, 0))
		{
		  m_Radius = (l_boxbounds.x) / 2;
		}

	  }
	}
	if (m_Radius == 0)
	{
	  m_Radius = 1;
	}

	m_Collider = std::shared_ptr<btCollisionShape>(new btSphereShape(m_Radius));

	if (GetGameObject().lock()->getComponent<Rigidbody>().lock() == NULL)
	{
	  GetGameObject().lock()->addComponent<Rigidbody>();
	}
  }
  void SphereCollider::Update()
  {

  }
  void SphereCollider::FixedUpdate()
  {

  }
  void SphereCollider::SetKimetic(bool _state)
  {
	m_IsKimetic = _state;
  }
  bool SphereCollider::IsKimetic()
  {
	return m_IsKimetic;
  }
  std::weak_ptr<btCollisionShape> SphereCollider::GetCollider()
  {
	return m_Collider;
  }
}