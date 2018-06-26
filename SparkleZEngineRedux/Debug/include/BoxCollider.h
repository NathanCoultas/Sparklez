#ifndef SPARKLEZ_ENGINE_COMPONENT_BOX_COLLIDER_H
#define SPARKLEZ_ENGINE_COMPONENT_BOX_COLLIDER_H
#include "Behaviour.h"
#include "Console.h"
#include "glm\glm.hpp"
#include "bullet\btBulletDynamicsCommon.h"


namespace sparklezEngine
{
  class GameObject;
  class BoxCollider : public Behaviour
  {
	friend class GameObject;
  public:

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();

	void SetKimetic(bool _state);
	bool IsKimetic();
	
	std::weak_ptr<btCollisionShape> GetCollider();

	glm::vec3 m_BoxSize;
  private:
	std::shared_ptr<btCollisionShape> m_Collider;
	bool m_IsTrigger;
	bool m_IsKimetic;
  };
}
#endif