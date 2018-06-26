#include "Component.h"

namespace sparklezEngine
{
	Component::~Component()
	{
      Destroy();
	}

	void Component::Awake()
	{
		//
	}

	void Component::Start()
	{

	}

	void Component::Update()
	{
	}

	void Component::FixedUpdate()
	{
	}

	void Component::Render()
	{
	}

	void Component::Destroy()
	{
		m_destroyed = true;
	}

	void Component::SaveComponent()
	{

	}

	void Component::loadComponent()
	{
	}

	void Component::Instantiate()
	{
	}

	void Component::SetActive(bool _ActiveState)
	{
		m_IsActive = _ActiveState;
	}

	bool Component::IsActive()
	{
		return m_IsActive;
	}

	std::weak_ptr<GameObject> Component::getMyGameObject()
	{
		return m_MyGameObject;
	}

}
