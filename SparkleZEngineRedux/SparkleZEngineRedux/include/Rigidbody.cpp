#include "Rigidbody.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

namespace sparklezEngine
{
  void Rigidbody::Awake()
  {
	if (GetGameObject().lock()->IsStatic() == true)
	{
	  m_IsKimetic = true;
	  m_Mass = 0.0f;
	}
	else
	{
	  m_IsKimetic = false;
	  m_Mass = 1.0f;
	}

	if (GetGameObject().lock()->getComponent<BoxCollider>().lock() != NULL || GetGameObject().lock()->getComponent<SphereCollider>().lock() != NULL)
	{
	  std::shared_ptr<Transform> l_Trans = GetTransform().lock();

	  btTransform l_BtTrans;
	  btQuaternion l_btquat(l_Trans->GetRotation().y, l_Trans->GetRotation().x, l_Trans->GetRotation().z);
	  l_BtTrans.setOrigin(btVector3(l_Trans->GetPostion().x, l_Trans->GetPostion().y, l_Trans->GetPostion().z));
	  l_BtTrans.setRotation(l_btquat);

	  m_fallMotionState = std::shared_ptr<btDefaultMotionState>(new btDefaultMotionState(l_BtTrans));

	  btScalar l_mass = m_Mass;
	  btVector3 l_fallInertia(0, 0, 0);

	  if (GetGameObject().lock()->getComponent<BoxCollider>().lock() == NULL)
	  {
		GetGameObject().lock()->getComponent<SphereCollider>().lock()->GetCollider().lock()->calculateLocalInertia(l_mass, l_fallInertia);
		btRigidBody::btRigidBodyConstructionInfo l_fallRigidBodyCI(l_mass, m_fallMotionState.get(), GetGameObject().lock()->getComponent<SphereCollider>().lock()->GetCollider().lock().get(), l_fallInertia);
		m_RigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(l_fallRigidBodyCI));
		m_IsKimetic = GetGameObject().lock()->getComponent<SphereCollider>().lock()->IsKimetic();

		//m_RigidBody.get()->isStaticObject		

		//m_RigidBody.get()->saveKinematicState(IsKimetic());
		//m_RigidBody.get()->setFlags(2);
	  }
	  else
	  {
		GetGameObject().lock()->getComponent<BoxCollider>().lock()->GetCollider().lock()->calculateLocalInertia(l_mass, l_fallInertia);
		btRigidBody::btRigidBodyConstructionInfo l_fallRigidBodyCI(l_mass, m_fallMotionState.get(), GetGameObject().lock()->getComponent<BoxCollider>().lock()->GetCollider().lock().get(), l_fallInertia);
		m_RigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(l_fallRigidBodyCI));
		m_IsKimetic = GetGameObject().lock()->getComponent<BoxCollider>().lock()->IsKimetic();

	  }
	  SceneManager::GetDynamicWorld()->addRigidBody(m_RigidBody.get());
	}
	else
	{
	  Console::ErrorMessage("CONSTRUCTING RIGIDBODY WITHOUT COLLIDER ON GAMEOBJECT: " + getName());
	}
  }
  void Rigidbody::FixedUpdate()
  {
	if (m_IsKimetic == false && GetGameObject().lock()->IsStatic() == false)
	{
	  btTransform l_Trans;
	  m_RigidBody.get()->getMotionState()->getWorldTransform(l_Trans);

	  btScalar l_ScalRotX;
	  btScalar l_ScalRotY;
	  btScalar l_ScalRotZ;

	  //fuck u rotation
	  float l_x = l_Trans.getOrigin().getX();
	  float l_y = l_Trans.getOrigin().getY();
	  float l_z = l_Trans.getOrigin().getZ();
	  l_Trans.getRotation().getEulerZYX(l_ScalRotZ, l_ScalRotY, l_ScalRotX);

	  GetTransform().lock()->SetPosition(l_x, l_y, l_z);
	  GetTransform().lock()->SetRotation(l_ScalRotX, l_ScalRotY, l_ScalRotZ);
	}
  }
  float Rigidbody::GetMass()
  {
	return m_Mass;
  }
  void Rigidbody::SetMass(float _mass)
  {
	m_Mass = _mass;
  }

  bool Rigidbody::IsKimetic()
  {
	return m_IsKimetic;
  }

  void Rigidbody::ForceUpdate()
  {
	std::shared_ptr<Transform> l_Trans = GetTransform().lock();

	btTransform l_BtTrans;
	l_BtTrans.setOrigin(btVector3(l_Trans->GetPostion().x, l_Trans->GetPostion().y, l_Trans->GetPostion().z));
	m_RigidBody->setWorldTransform(l_BtTrans);
  }

  void Rigidbody::UpdateKimetic()
  {
	if (GetGameObject().lock()->getComponent<BoxCollider>().lock() != NULL || GetGameObject().lock()->getComponent<SphereCollider>().lock() != NULL)
	{
	  if (GetGameObject().lock()->getComponent<BoxCollider>().lock() == NULL)
	  {
		m_IsKimetic = GetGameObject().lock()->getComponent<SphereCollider>().lock()->IsKimetic();
	  }
	  else
	  {
		m_IsKimetic = GetGameObject().lock()->getComponent<BoxCollider>().lock()->IsKimetic();
	  }
	}
	else
	{
	  sparklezEngine::Console::ErrorMessage("CANNOT UPDATE KIMETIC STATE ON: " + getName() + "Are you missing a collider?");
	}
  }
}