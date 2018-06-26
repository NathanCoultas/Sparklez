#ifndef SPARKLEZ_ENGINE_COMPONENT_RIGIDBODY_H
#define SPARKLEZ_ENGINE_COMPONENT_RIGIDBODY_H
#include "Behaviour.h"
#include "Console.h"
#include "glm\glm.hpp"
#include "bullet\btBulletDynamicsCommon.h"

namespace sparklezEngine
{
  class GameObject;
  class Rigidbody : public Behaviour
  {
    friend class GameObject;
  public:

	void Awake();
	void FixedUpdate();
	
	float GetMass();
	void SetMass(float _mass);
	void ForceUpdate();
	void UpdateKimetic();

	bool IsKimetic();
  private:

	std::shared_ptr<btRigidBody> m_RigidBody;
	std::shared_ptr<btDefaultMotionState> m_fallMotionState;
	bool m_IsKimetic;
	float m_Mass;
  };
}
#endif