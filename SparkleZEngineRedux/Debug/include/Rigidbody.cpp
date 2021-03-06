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
	if (getMyGameObject().lock()->IsStatic() == true)
	{
	  m_Mass = 0;
	  m_IsKimetic = true;
	}
	else
	{
	  m_Mass = 0.05f;
	}

	m_IsKimetic = false;

	if (getMyGameObject().lock()->getComponent<BoxCollider>().lock() != NULL || getMyGameObject().lock()->getComponent<SphereCollider>().lock() != NULL)
	{
	  std::shared_ptr<Transform> l_Trans = getMyGameObject().lock()->GetTransform().lock();

	  btTransform l_BtTrans;
	  btQuaternion l_btquat(l_Trans->GetRotation().y, l_Trans->GetRotation().x, l_Trans->GetRotation().z);
	  l_BtTrans.setOrigin(btVector3(l_Trans->GetPostion().x, l_Trans->GetPostion().y, l_Trans->GetPostion().z));
	  l_BtTrans.setRotation(l_btquat);

	  m_fallMotionState = std::shared_ptr<btDefaultMotionState>
		(new btDefaultMotionState(l_BtTrans));

	  btScalar l_mass = m_Mass;
	  btVector3 l_fallInertia(0, 0, 0);

	  if (getMyGameObject().lock()->getComponent<BoxCollider>().lock() == NULL)
	  {
		getMyGameObject().lock()->getComponent<SphereCollider>().lock()->GetCollider().lock()->calculateLocalInertia(l_mass, l_fallInertia);
		btRigidBody::btRigidBodyConstructionInfo l_fallRigidBodyCI(l_mass, m_fallMotionState.get(), getMyGameObject().lock()->getComponent<SphereCollider>().lock()->GetCollider().lock().get(), l_fallInertia);
		m_RigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(l_fallRigidBodyCI));
		//m_RigidBody.get()->saveKinematicState(getMyGameObject().lock()->getComponent<SphereCollider>().lock()->IsKimetic());
		m_IsKimetic = getMyGameObject().lock()->getComponent<SphereCollider>().lock()->IsKimetic();
	  }
	  else
	  {
		getMyGameObject().lock()->getComponent<BoxCollider>().lock()->GetCollider().lock()->calculateLocalInertia(l_mass, l_fallInertia);
		btRigidBody::btRigidBodyConstructionInfo l_fallRigidBodyCI(l_mass, m_fallMotionState.get(), getMyGameObject().lock()->getComponent<BoxCollider>().lock()->GetCollider().lock().get(), l_fallInertia);
		m_RigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(l_fallRigidBodyCI));
		//m_RigidBody.get()->saveKinematicState(getMyGameObject().lock()->getComponent<BoxCollider>().lock()->IsKimetic());
		m_IsKimetic = getMyGameObject().lock()->getComponent<BoxCollider>().lock()->IsKimetic();
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
	if (m_IsKimetic == false)
	{
	  btTransform l_Trans;
	  m_RigidBody.get()->getMotionState()->getWorldTransform(l_Trans);

	  
	  btScalar l_ScalRotX;
	  btScalar l_ScalRotY;
	  btScalar l_ScalRotZ;

	  float l_x = l_Trans.getOrigin().getX();
	  float l_y = l_Trans.getOrigin().getY();
	  float l_z = l_Trans.getOrigin().getZ();
	  l_Trans.getRotation().getEulerZYX(l_ScalRotX, l_ScalRotY, l_ScalRotZ);

	  getMyGameObject().lock()->GetTransform().lock()->SetPosition(l_x, l_y, l_z);
	  getMyGameObject().lock()->GetTransform().lock()->SetRotation(l_ScalRotX, l_ScalRotY, l_ScalRotZ);
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

  void Rigidbody::ForceUpdate()
  {
	std::shared_ptr<Transform> l_Trans = getMyGameObject().lock()->GetTransform().lock();

	btTransform l_BtTrans;
	l_BtTrans.setOrigin(btVector3(l_Trans->GetPostion().x, l_Trans->GetPostion().y, l_Trans->GetPostion().z));
	m_RigidBody->setWorldTransform(l_BtTrans);
  }
}